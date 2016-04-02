#include "MyQuadlist.h"

//MyQuadlistNode
//插入新节点,以当前节点为前驱, 以节点b为下邻
template <typename T>
MyQlistNodePosi(T) MyQuadlistNode<T>::insertAsSuccAbove(const T &e, MyQlistNodePosi(T) b = NULL){
    MyQlistNodePosi(T) p = new MyQuadlistNode(e, this, succ, NULL, b);
    //设置水平链接
    succ->pred = p; succ = p;
    //设置垂直逆向链接
    if(b)
        b->above = p;
    return p;
}

//MyQuadlist
//四联表创建时初始化
template <typename T>
void MyQuadlist<T>::init(){
    //创建头尾哨兵
    header = new MyQuadlistNode<T>;
    trailer = new MyQuadlistNode<T>;
    //沿横向联接哨兵
    header->succ = trailer; header->pred = NULL;
    trailer->pred = header; trailer->succ = NULL;
    //纵向的后继置空
    header->above = trailer->above = NULL;
    //纵向的前驱置空
    header->below = trailer->below = NULL;
    _size = 0;
}

//清除所有节点, 返回被清除的节点数
template <typename T>
int MyQuadlist<T>::clear(){
    int oldSize = _size;
    while(0 < _size)
        remove(header->succ);
    return oldSize;
}

//将*e作为p的后继、b的上邻插入
template <typename T>
MyQlistNodePosi(T) MyQuadlist<T>::insertAfterAbove(const T &e, MyQlistNodePosi(T) p, MyQlistNodePosi(T) b = NULL){
    _size++;
    return p->insertAsSuccAbove(e, b);
}

//删除(合法)位置p处的节点, 返回被删除节点的数值
template <typename T>
T MyQuadlist<T>::remove(MyQlistNodePosi(T) p){
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    _size--;
    T e = p->entry; delete p;
    return e;
}

//函数指针遍历
template <typename T>
void MyQuadlist<T>::traverse(void (*visit) (T &e)){
    MyQlistNodePosi(T) p = header->succ;
    for( ; p != trailer; ){
        visit(p->entry);
        for(MyQlistNodePosi(T) q = p; q != NULL; q = q->above)
            visit(q->entry);
        p = p->succ;
    }   
}

//函数对象遍历
template <typename T>
template <typename VST>
void MyQuadlist<T>::traverse(VST &visit){
    MyQlistNodePosi(T) p = header->succ;
    for(; p != trailer; ){
        visit(p->entry);
        for(MyQlistNodePosi(T) q = p; q != NULL; q = q->above)
            visit(q->entry);
        p = p->succ;
    }
}