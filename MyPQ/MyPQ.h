#ifndef MYPQ_H_
#define MYPQ_H_
//优先级队列ADT
template <typename T>
class MyPQ{
public:
    //按照比较器确定的优先级次序插入词条
    virtual void insert(T ) = 0;
    //取出优先级最高的词条
    virtual T getMax() = 0;
    //删除优先级最高的词条
    virtual T delMax() = 0;
};
#endif