#ifndef MYAVL_H_
#define MYAVL_H_
#include "MyBinSearchTree.cpp"
//AVL, 平衡二叉搜索树, 执行插入或删除操作之后, 高度差的绝对值不超过1 
template <typename T>
class MyAVL: public MyBinSearchTree<T>{
protected:
    //恢复平衡的调整方案, 决定于失衡节点的更高孩子、更高孙子节点的方向
    //在左、右孩子中取更高者, 在AVL平衡调整前, 借此确定重构方案
    BinNodePosi(T)& tallerChild(BinNodePosi(T) &);
public:
    BinNodePosi(T) insert(const T &e);
    bool remove(const T &e);  
};
#endif