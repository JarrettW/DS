#include <iostream>
#include "MyStack.cpp"

int main(){
    MyStack<char> S1;
    //入栈
    S1.push('a');
    std::cout << S1.top() << std::endl;
    //入栈
    S1.push('b');
    std::cout << S1.top() << std::endl;
    //堆顶出栈
    S1.pop(); 
    
    std::cout << S1.top();
    return 0;
}