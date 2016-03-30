#include "MyLeftHeap.h"
//左式堆合并接口, 根据相对优先级确定适宜的方式, 合并以a和b为根节点的两个左式堆
template <typename T>
BinNodePosi(T) MyLeftHeap<T>::merge(BinNodePosi(T) a, BinNodePosi(T) b){
    if( !a ) return b;
    if( !b ) return a;
    //一般情况, 首先确保b不大
    if( lt(a->data, b->data))
        swap( a, b);
    //将a的右子堆与b合并
    a->rc = merge(a->rc, b);
    //并更新父子关系
    a->rc->parent = a;
    //左右必要,交换a的左、右子堆, 确保右子堆的npl不大
    if( !a->lc || a->lc->npl < a->rc->npl)
        swap(a->lc, a->rc);
    //更新npl
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    //返回合并后的堆顶
    return a;
}

//按照比较器确定的优先级次序插入元素
template <typename T>
void MyLeftHeap<T>::insert(T e){
    //创建一个新二叉树节点
    BinNodePosi(T) v = new BinNode<T>(e);
    //通过与根节点的合并完成新节点的插入
    _root = merge(_root, v);
    _root->parent = NULL;
    _size++;
}

//取出左式堆节点优先级最高的元素
template <typename T>
T MyLeftHeap<T>::getMax(){
    return _root->data;
}

//删除左式堆节点优先级最高的元素
template <typename T>
T MyLeftHeap<T>::delMax(){
    //备份优先级最高的元素
    T oldElem = _root->data;
    //备份左子堆、右子堆
    BinNodePosi(T) lHeap = _root->lc;
    BinNodePosi(T) rHeap = _root->rc;
    //_root = NULL;
    delete _root; _size--;
    _root = merge(lHeap, rHeap);
    if(_root)
        _root->parent = NULL;
    return oldElem;
}