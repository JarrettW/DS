#include "MyDeque.h"
//自队首入队
template <typename T>
void MyDeque<T>::insertFront(const T&e){
    insertAsFirst(e);
}
//自队尾入队
template <typename T>
void MyDeque<T>::insertRear(const T &e){
    insertAsLast(e);
} 
//删除队首元素
template <typename T>
T MyDeque<T>::removeFront(){
    return remove(first());
}
//删除队尾元素
template <typename T>
T MyDeque<T>::removeRear(){
    return remove(last());
}
//引用队首元素
template <typename T>
T& MyDeque<T>::front()const{
    return first()->data;
}
//引用队尾元素
template <typename T>
T& MyDeque<T>::rear()const{
    return last()->data;
}