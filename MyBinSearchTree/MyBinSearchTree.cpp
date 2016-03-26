#include "MyBinSearchTree.h"
//二叉搜索树查找接口
template <typename T>
BinNodePosi(T)& MyBinSearchTree<T>::search(const T &e){
    //返回目标节点位置的引用,以便后序插入、删除使用
    return searchIn(_root, e, _hot = NULL);
}
//实际上是二分的递归搜索
template <typename T>
BinNodePosi(T)& MyBinSearchTree<T>::searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot){
    if( !v || (e == v->data))
        return v;
    hot = v;
    //hot作用, 指向"命中节点"的父亲,退化时初始值为NULL
    return searchIn( ((e < v->data) ? v->lc : v->rc), e, hot);
}

//二叉搜索树的插入接口
template <typename T>
BinNodePosi(T) MyBinSearchTree<T>::insert(const T &e){
    BinNodePosi(T) &x = search(e);
    if(x)
        return x;  //若存在节点, 则直接返回.此处规定无重复节点    
    //确认目标不存在, 创建新节点
    x = new BinNode<T>(e, _hot); //_hot为父,search中对hot的设置发挥作用
    ++_size;
    updateHeightAbove(x);
    return x;  //新插入节点,必为叶节点
}

//删除
template <typename T>
bool MyBinSearchTree<T>::remove(const T &e){
    BinNodePosi(T) &x = search(e);
    if(!x)
        return false;
    removeAt(x, _hot);
    _size--;
    updateHeightAbove(_hot);
    return true;
}
template <typename T>
BinNodePosi(T) MyBinSearchTree<T>::removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot){
    BinNodePosi(T) w = x; //实际被摘除的节点,初值同x
    BinNodePosi(T) succ = NULL; //实际被删除节点的接替者
    if( !HasLChild(x))  //若x的左子树为空,则可
        succ = x = x->rc;  //直接将x替换为其右子树
    else if( !HasRChild(x)) //若x的右子树为空, 则可
        succ = x = x->lc;  //对称处理
    else{ //若左右子树均存在, 则直接选择x的直接后继作为实际被摘除节点
        w = w->succ(); //(在右子树中)找到x的直接后继w,
        swap(x->data, w->data);  //交换数据
        BinNodePosi(T) u = w->parent;
        ( (u == x) ? u->rc : u->lc) = succ = w->rc;  //隔离节点w
    }
    hot = w->parent; //记录实际被删除节点的父亲
    if(succ)
        succ->parent = hot; //并将被删除节点的接替者与hot相联
    w = NULL;
    return succ;
}