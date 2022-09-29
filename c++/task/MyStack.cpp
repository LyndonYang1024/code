#include "MyStack.h"

#include <iostream>

int main() {
    MyStack<int> stack(5);
    stack.push(1);
    std::cout << "test push, should print 1" << std::endl;
    stack.printStack();
    
    std::cout << "test pop, should print 1: " << stack.pop() << ", size should be 0: " << stack.getSize() << std::endl;
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    std::cout << "test stack overflow, should print 2-6" << std::endl;
    stack.printStack();

    stack.push(7);
    std::cout << "test push after overflow, should print 3-7" << std::endl;
    stack.printStack();

    std::cout << "test pop after overflow, should print 7" << std::endl;
    std::cout << "pop:" << stack.pop() << std::endl;

    std::cout << "test copy constructor" << std::endl;
    MyStack<int> stack1(stack);
    stack1.printStack();
    
    std::cout << "test move constructor" << std::endl;
    MyStack<int> stack2(std::move(stack1));
    stack2.printStack();
    
    return 0;
}
