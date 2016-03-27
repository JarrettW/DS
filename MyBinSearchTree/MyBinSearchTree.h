#ifndef MYBINSEARCHTREE_H_
#define MYBINSEARCHTREE_H_
//由MyBinTree派生的二叉搜索树模板类MyBinSearchTree(BST)
#include "../MyBinTree/MyBinTree.cpp"

template <typename T>
class MyBinSearchTree: public MyBinTree<T>{
public:
    //基本接口: 以virtual修饰,强制要求所有派生类(BST变种)根据各自规则对其重写
    //查找
    virtual BinNodePosi(T)& search(const T &e);
    //插入
    virtual BinNodePosi(T) insert(const T &e);
    //删除
    virtual bool remove(const T &e);
protected:
    //命中节点的父亲
    BinNodePosi(T) _hot;
    //按照"3+4"结构,联接3个节点及四棵子树
    BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
    //对x及其父亲、祖父做统一旋转调整
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);
    //查找辅助方法
    static BinNodePosi(T)& searchIn(BinNodePosi(T) &v, const T &e, BinNodePosi(T) &hot);
    //删除辅助方法
    static BinNodePosi(T) removeAt(BinNodePosi(T) &x, BinNodePosi(T) &hot);
    static void swap(T &d1, T &d2){
        T temp = d2;
        d2 = d1;
        d1 = temp;
    }
};
#endif