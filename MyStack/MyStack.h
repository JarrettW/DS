#ifndef MYSTACK_H_
#define MYSTACK_H_
//基于MyList实现堆栈,利用MyList在尾元素操作效率高的优势,常数时间
//堆栈是一个后进先出(LIFO)的数据结构
#include "../MyList/MyList.cpp"
template <typename T>
class MyStack: public MyList<T>{
public:
    //默认构造函数
    MyStack(){}
    //入栈,仅支持在尾元素插入
    void push(const T &e);
    //出栈,仅支持删除尾元素
    T pop();
    //取顶,返回最顶端元素,不删除
    T top()const;
};
#endif