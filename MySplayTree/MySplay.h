#ifndef MYSPLAY_H_
#define MYSPLAY_H_
//高级搜索树---伸展树, 基于二叉搜索树; 将查找、插入、删除的节点伸展至根节点
#include "../MyBinSearchTree/MyBinSearchTree.cpp"
template <typename T>
class MySplay: public MyBinSearchTree<T>{
public:
    BinNodePosi(T)& search(const T &e);  //查找
    BinNodePosi(T) insert(const T &e);   //插入
    bool remove(const T &e);    //删除
protected:
    //将节点v伸展至树根
    BinNodePosi(T) splay(BinNodePosi(T) &v);
    //在节点"p于lc"之间建立父(左)子关系
    template <typename NodePosi>
    inline void attachAsLChild(NodePosi p, NodePosi lc){
        p->lc = lc;
        if(lc)
            lc->parent = p;
    }
    //在节点"p与rc"之间建立父(右)子关系 
    template <typename NodePosi>
    inline void attachAsRChild(NodePosi p, NodePosi rc){
        p->rc = rc;
        if(rc)
            rc->parent = p;
    } 
};
#endif