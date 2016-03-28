#ifndef MYBTREE_H_
#define MYBTREE_H_
//m阶B树, 多路搜索树. 减少内存与外存的访问次数
//使用向量存储关键码及B树节点
#include "../MyVector/MyVector.cpp"
//B-树节点位置
#define BNodePosi(T) BNode<T>*

//B-树节点
template <typename T>
class BNode{
public:
    //父节点
    BNodePosi(T) parent;
    //关键码向量
    MyVector<T> key;
    //孩子向量(总比key多1)
    MyVector<BNodePosi(T)> child;
    //构造函数; BNode只能作为根节点,而且初始时有0个关键码和1个空孩子指针
    BNode(){
        parent = NULL;
        child.insert(0, NULL);  //初始化下标0的位置为孩子NULL
    }
    BNode(T e, BNodePosi(T) lc = NULL, BNodePosi(T) rc = NULL){
        parent = NULL:
        key.insert(0, e);  //只有一个关键码
        child.insert(0, lc); child.insert(1, rc); //以及两个孩子
        if(lc)
            lc->parent = this;
        if(rc)
            rc->parent = this;
    } 
};

//B-树
template <typename T>
class BTree{
public:
    
};
#endif