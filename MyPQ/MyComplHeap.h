#ifndef MYCOMPLHEAP_H_
#define MYCOMPLHEAP_H_
//完全二叉堆, 基于向量实现的堆结构
#include "..\MyVector\MyVector.cpp"
#include "MyPQ.h"
//为简化完全二叉堆算法的描述及实现而定义的宏
//判断PQ[i]是否合法
#define InHeap(n ,i) ( ( (-1) < (i) ) && ( (i) < (n) ) )
//PQ[i]的父节点 (floor(i-1)/2), i无论正负), 取下整
#define Parent(i) ( (i - 1) >> 1)
//最后一个内部节点(即末节点的父亲)
#define LastInternal(n) Parent(n -1)
//PQ[i]的左孩子
#define LChild(i) ( 1 + ( (i) << 1) )
//PQ[i]的右孩子
#define RChild(i) ( (1 + (i)) << 1)
//判断PQ[i]是否有父亲
#define ParentValid(i) ( 0 < i)
//判断PQ[i]是否有一个(左)孩子
#define LChildValid(n, i) InHeap(n, LChild(i))
//判断PQ[i]是否有两个孩子
#define RChildValid(n, i) InHeap(n, RChild(i))
//取大者(等时前者优先)
#define Bigger(PQ, i, j) (lt(PQ[i], PQ[j]) ? j : i )
//父子(至多)三者中的大者, 相等时父节点优先, 如此可避免不必要的交换
#define ProperParent(PQ, n, i) (RChildValid(n, i) ? Bigger(PQ, Bigger(PQ, i, LChild(i)), RChild(i)) : (LChildValid(n, i) ? Bigger(PQ, i, LChild(i)) : i))

//完全二叉堆接口
template <typename T>
class MyComplHeap: public MyPQ<T>, public MyVector<T>{
public:
    //默认构造
    MyComplHeap() {}
    //批量构造
    MyComplHeap(T *A, int n){
        copyFrom(A, 0, n);
        heapify(n);  //建堆
    }
    //按照比较器确定的优先级次序, 插入词条
    void insert(T );
    //读取优先级最高的词条
    T getMax();
    //删除优先级最高的词条
    T delMax();
    //堆排序
    void heapSort(int lo, int hi);
    //显示堆内容
    void show(){
        for(auto i = 0; i != _size; i++)
            std::cout << _elem[i] << ' ';
    }
protected:
    //上滤
    int percolateUp(int i);
    //下滤
    int percolateDown(int n, int i);
    //Floyd建堆算法, 给定一组词条, 组织为一个堆
    void heapify(int n);
    //less than
    bool lt(T d1, T d2){
        return d1 < d2 ? true : false;
    }
};
#endif