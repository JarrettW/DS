#ifndef MYDEQUE_H_
#define MYDEQUE_H_
//双端队列,基于MyList实现.
//在前端和后端插入、删除元素效率高
#include "../MyList/MyList.cpp"
template <typename T>
class MyDeque: public MyList<T>{
public:
 //在队首插入元素
 void insertFront(const T &);
 //在队尾插入元素
 void insertRear(const T &);
 //队首元素出队
 T removeFront();
 //队尾元素出队
 T removeRear();
 //引用队首元素
 T& front()const;
 //引用队尾元素
 T& rear()const; 
}; 
#endif