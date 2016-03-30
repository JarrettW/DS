#ifndef MYLEFTHEAP_H_
#define MYLEFTHEAP_H_
//基于二叉树, 以左式堆形式实现的优先级队列
#include "..\MyBinTree\MyBinTree.cpp"
#include "MyPQ.h"

template <typename T>
class MyLeftHeap: public MyPQ<T>, public MyBinTree<T>{
public:
    //默认构造
    MyLeftHeap() {}
    //批量构造
    MyLeftHeap(T *E, int n){
        for(int i = 0; i != n; ++i)
            insert(E[i]);
    }
    //按照比较器确定的优先级次序插入元素
    void insert(T );
    //取出优先级最高的元素
    T getMax();
    //删除优先级最高的元素
    T delMax();
    //左式堆合并接口
    static BinNodePosi(T) merge(BinNodePosi(T) , BinNodePosi(T) );
    static bool lt(T d1, T d2){
        return d1 < d2 ? true : false;
    }
    static void swap(BinNodePosi(T) l, BinNodePosi(T) r){
        BinNodePosi(T) temp = l;
        l = r;
        r = temp;
    }
};
#endif