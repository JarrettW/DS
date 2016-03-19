#include <iostream>
#include "MyQueue.cpp"

int main(){
    MyQueue<int> Q1;
    Q1.enqueue(10);
    Q1.enqueue(21);
    std::cout << "Q1 size: " << Q1.size() << std::endl;
    std::cout << "Q1 top: " << Q1.front() << std::endl;
    std::cout << "Q1 pop: " << Q1.dequeue() << std::endl;
    std::cout << "Q1 size: " << Q1.size() << std::endl;
    
    return 0;
}