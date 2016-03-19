#include <iostream>
#include "MyDeque.cpp"

int main(){
    MyDeque<int> D1;
    std::cout << "D1 size: " << D1.size() << std::endl;
    std::cout << "D1 empty: " << D1.empty() << std::endl;
    //队首插入2
    D1.insertFront(2);
    //队首插入1
    D1.insertFront(1);
    //队尾插入3
    D1.insertRear(3);
    //队尾插入4
    D1.insertRear(4);
    std::cout << "D1:  ";
    //显示D1内的元素
    D1.show(D1.first());
    std::cout << "D1 size: " << D1.size() << std::endl;
    std::cout << "D1 empty: " << D1.empty() << std::endl;
    //引用队首元素
    std::cout << "D1 front: " << D1.front() << std::endl;
    //引用队尾元素
    std::cout << "D1 rear: " << D1.rear() << std::endl;
    //队首元素出队
    D1.removeFront();
    //队尾元素出队
    D1.removeRear();
    //显示D1内的元素
    std::cout << "Elemente deleted: ";
    D1.show(D1.first());
    std::cout << "D1 size: " << D1.size() << std::endl;
    std::cout << "D1 empty: " << D1.empty() << std::endl;   
    
    return 0;
}