#include <iostream>

template<typename T>
class MyStack {
  public:
    // Default constructor
    explicit MyStack(int size) : count(0), top(-1), capacity(size) {
        elements = new T[size];
    }
    
    // copy constructor
    explicit MyStack(const MyStack<T> &stack) {
        elements = new T[stack.capacity];
        capacity = stack.capacity;
        count = stack.count;
        top = stack.top;

        int loop = 0;
        int begin = top;
        while (loop != count)
        {
            elements[begin] = stack.elements[begin];
            begin = (begin - 1  < 0) ? capacity - 1 : begin - 1;
            ++loop;
        }
    }
    
    // move constructor
    explicit MyStack(MyStack<T> &&stack) {
        count = stack.count;
        capacity = stack.capacity;
        top = stack.top;
        elements = stack.elements;
        stack.elements = NULL;
        stack.capacity = 0;
        stack.count = 0;
        stack.top = -1;
    }

    // destructor
    ~MyStack() {
        if (elements) {
            delete [] elements;
            elements = NULL;
        }
    }

    void push(T data) {
        top = ((top + 1) >= capacity) ? 0 : top + 1;
        elements[top] = data;
        count = (count == capacity) ? count : ++count;
    }

    T pop() {
        if (-1 == count) {
            std::cout << "stack is empty!" << std::endl;
            exit(-1);
        }
        int result = elements[top];
        top = (top - 1  < 0) ? capacity - 1 : top - 1;
        --count;
        return result;
    }

    int getSize() {
        return count;
    }

     void printStack() {
         int loop = 0;
         int begin = top;
         while (loop != count)
         {
             std::cout << elements[begin] << std::endl;
             begin = (begin - 1  < 0) ? capacity - 1 : begin - 1;
             ++loop;
         }
     }

  private:
    int capacity = 0;
    int count = 0;  // the number of elements in the stack
    int top = -1;
    T* elements;
};

