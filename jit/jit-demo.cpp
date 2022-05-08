#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JITSymbol.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/ExecutionEngine/Orc/CompileUtils.h>
//#include <llvm/ExecutionEngine/Orc/IRCompileLayer.h>
//#include <llvm/ExecutionEngine/Orc/LambdaResolver.h>
//#include <llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h>

#include <memory>
#include <vector>

using namespace llvm;
using namespace std;

static Module* jit_module = NULL;
static LLVMContext context;
static IRBuilder<> builder(context);

using LinkLayer = orc::RTDyldObjectLinkingLayer;
using Compiler = orc::SimpleCompiler;
using CompileLayer = orc::IRCompileLayer<LinkLayer, Compiler>;

JITSymbol dummy_lookup(const string& name)
{
	return JITSymbol(NULL);
}

void code_gen()
{
	jit_module = new Module("Test JIT Compiler", context);
	// (double, double, double)
	std::vector<Type*> param_type(3, Type::getDoubleTy(context));
	// double (*)(double, double, double)
	FunctionType* prototype = FunctionType::get(Type::getDoubleTy(context), param_type, false);

	Function *func = Function::Create(prototype, Function::ExternalLinkage, "test_func", jit_module);
	BasicBlock *body = BasicBlock::Create(context, "body", func);
	builder.SetInsertPoint(body);

	std::vector<Value*> args;
	for(auto& arg : func->args())
		args.push_back(&arg);

	Value* temp = builder.CreateFMul(args[0], args[1], "temp");
	Value* ret = builder.CreateFMul(args[2], temp, "result");
	builder.CreateRet(ret);
}

int main()
{
	// Initialization
	LLVMInitializeNativeTarget();
	InitializeNativeTargetAsmPrinter();
	TargetMachine* target = EngineBuilder().selectTarget();

	// Emit the LLVM IR to the Module
	code_gen();

	// Compile the IR to Machine Code 
	const DataLayout dl = target->createDataLayout();
	LinkLayer link_layer([]() { return std::make_shared<SectionMemoryManager>(); });
	CompileLayer compile_layer(link_layer, Compiler(*target));
	auto jit_module_handle = cantFail(compile_layer.addModule(std::shared_ptr<Module>(jit_module), 
			                  orc::createLambdaResolver(dummy_lookup, dummy_lookup)));
	
	// Run the compiled function !
	JITSymbol symbol = compile_layer.findSymbolIn(jit_module_handle, "test_func", false);
	double (*native_func)(double, double, double) = (decltype(native_func))cantFail(symbol.getAddress());
	printf("%lf\n", native_func(3,4,5));
	printf("%lf\n", native_func(1,2,3));

	delete target;
	return 0;
}
