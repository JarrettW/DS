#include "MyComplHeap.h"
//按照比较器确定的优先级次序,插入词条
template <typename T>
void MyComplHeap<T>::insert(T e){
    //将词条插入向量末尾
    MyVector<T>::insert(e);
    //上滤调整
    percolateUp(_size - 1);
}

//读取优先级最高的词条
template <typename T>
T MyComplHeap<T>::getMax(){
    return _elem[0];
}

//删除优先级最高的词条
template <typename T>
T MyComplHeap<T>::delMax(){
    //备份优先级最高的词条
    T maxElem = _elem[0];
    //将堆顶代之以末词条, 即移除了原堆顶词条
    _elem[0] = _elem[--_size];
    //下滤
    percolateDown(_size, 0);
    return maxElem;
}

//Floyd建堆算法, 给定一组词条, 组织为一个堆
template <typename T>
void MyComplHeap<T>::heapify(int n){
    //初始化为末节点的父亲(即最后一个内部节点)
    for(int i = LastInternal(n); InHeap(n, i); i--)
        percolateDown(n, i);
}

//堆排序
template <typename T>
void MyComplHeap<T>::heapSort(int lo, int hi){
    //将待排序区间建成一个完全二叉堆
    MyComplHeap<T> H(_elem + lo, hi - lo);
    while( !H.empty())
        _elem[--hi] = H.delMax();
}

//上滤调整
template <typename T>
int MyComplHeap<T>::percolateUp(int i){
    //i存在父亲,才能上滤
    while(ParentValid(i)){
        //j记作i的父亲
        int j = Parent(i);
        //当前父子不再逆序, 上旋即完成
        if( lt(_elem[i], _elem[j])) break;
        swap(_elem[i], _elem[j] );
        i = j;
    }
    return i; //返回上滤最终抵达的位置
}

//下滤调整
template <typename T>
int MyComplHeap<T>::percolateDown(int n, int i){
    //i及其孩子中的父亲
    int j;
    while( i != ( j = ProperParent(_elem, n, i))){
        swap(_elem[i], _elem[j]);//与(最多)三者中最大者交换
        i = j;
    }
    return i;
}