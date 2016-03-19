#include "MyQueue.h"
//入队,插入队尾
template <typename T>
void MyQueue<T>::enqueue(const T &e){
    insertAsLast(e);
}

//出队
template <typename T>
T MyQueue<T>::dequeue(){
    return remove(first());;
}

//引用队首元素
template <typename T>
T& MyQueue<T>::front()const{
    return first()->data;
}