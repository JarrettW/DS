#ifndef MYBINTREE_H_
#define MYBINTREE_H_
//二叉树的数据结构
//借助MyStack和MyQueue实现各遍历方法
#include "../MyStack/MyStack.cpp"
#include "../MyQueue/MyQueue.cpp"

//二叉树节点位置
using BinNodePosi(T) = BinNode<T>*;
//如果p节点存在返回其高度,否则这里规定空树为-1
#define stature(p) ((p) ? (p->height) : -1)
//节点颜色,红黑树使用
typedef enum{ RB_RED, RB_BLACK } RBColor;

//二叉树节点模板类
template <typename T>
class BinNode{
public:
    //数据
    T data;
    //父节点
    BinNodePosi(T) parent;
    //左孩子
    BinNodePosi(T) lc;
    //右孩子
    BinNodePosi(T) rc;
    //树高度
    int height;
    //Null Path Length(左式堆,可使用height代替)
    int npl;
    //红黑树颜色
    RBColor color;
    
    //默认构造函数
    BinNode():parent(NULL), lc(NULL), rc(NULL), height(0), npl(0), color(RB_RED) {}
    //构造函数
    BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED)
                    :data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
    //以当前节点为根的子树规模,即当前节点后代总数
    int size()const;
    //将元素作为当前节点的左孩子插入
    BinNodePosi(T) insertAsLC(const T&);
    //将元素作为当前节点的右孩子插入
    BinNodePosi(T) insertAsRC(const T&);
    //取当前节点的后继
    BinNodePosi(T) succ();
    
    //层次遍历,借助队列数据结构
    template <typename VST>
    void travLevel(VST &);
    
    //先序遍历---迭代版
    template <typename VST>
    void travPre_I(BinNodePosi(T), VST &);
    //中序遍历---迭代版
    template <typename VST>
    void travIn_I(BinNodePosi(T), VST &);
    //后序遍历---迭代版
    template <typename VST>
    void travPost_I(BinNodePosi(T), VST &);
      
    //先序遍历---递归版
    template <typename VST>
    void travPre_R(BinNodePosi(T), VST &);
    //中序遍历---递归版
    template <typename VST>
    void travIn_R(BinNodePosi(T), VST &);
    //后序遍历---递归版
    template <typename VST>
    void travPost_R(BinNodePosi(T), VST &);
    
    //先序遍历统一接口,随机选取递归版或迭代版
    template <typename VST>
    void travPre(VST &visit);
    //中序遍历统一接口,随机选取递归版或迭代版
    template <typename VST>
    void travPre(VST &visit);
    //后序遍历统一接口,随机选取递归版或迭代版
    template <typename VST>
    void travPost(VST &visit);
    
    
};

//二叉树模板类
template <typename T>
class MyBinTree: public MyList<T>{
public:
    //默认构造函数
    MyBinTree() { _root = NULL; }
    //将节点作为左孩子插入
    
    //将节点作为右孩子插入
    
    //删除当前节点的左孩子
    
    //删除当前节点的右孩子
    
    //将一棵树作为左孩子接入
    
    //将一棵数作为右孩子接入
    
    //摘除左子树,并取出
    
    //摘除右子树,并取出
    
    //函数对象
    //先序遍历---递归版
    
    //中序遍历---递归版
    
    //后序遍历---递归版
    
    //先序遍历---迭代版
    
    //中序遍历---迭代版
    
    //后序遍历---迭代版
    
private:
    //根节点
    BinNodePosi(T) _root;
    //规模
    unsigned int _size;
};
#endif