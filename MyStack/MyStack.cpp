#include "MyStack.h"
// 1.入栈
template <typename T>
void MyStack<T>::push(const T &e){
    insertAsLast(e);
} 
// 2.出栈
template <typename T>
T MyStack<T>::pop(){
    return remove(last());
}
// 3.取顶
template <typename T>
T MyStack<T>::top()const {
    return lastElem();
}