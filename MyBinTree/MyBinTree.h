#ifndef __MYBINTREE_H__
#define __MYBINTREE_H__
//二叉树的数据结构

#include "../MyList/MyList.cpp"

//借助MyStack和MyQueue实现各遍历方法
template <typename T>
class MyStack: public MyList<T>{
public:
    //默认构造函数
    MyStack(){}
    //入栈,仅支持在尾元素插入
    void push(const T &e);
    //出栈,仅支持删除尾元素
    T pop();
    //取顶,返回最顶端元素,不删除
    T top()const;
};
template <typename T>
class MyQueue: public MyList<T>{
public:
  //入队,插入队尾
  void enqueue(const T&e);
  //出队
  T dequeue();
  //引用队首元素
  T& front()const;
};

//二叉树节点位置
#define BinNodePosi(T) BinNode<T>*
//如果p节点存在返回其高度,否则这里规定空树为-1
#define stature(p) ((p) ? (p->height) : -1)
//节点颜色,红黑树使用
typedef enum{ RB_RED, RB_BLACK } RBColor;

/************************************以宏的形式对基于BinNode的操作归纳整理*************************************/
//是否为根节点
#define IsRoot(x) (!(x->parent)) //根节点的父亲为NULL
//是否为左孩子
#define IsLChild(x) ( !IsRoot(x) && ( x == x->parent->lc ))
//是否为右孩子
#define IsRChild(x) ( !IsRoot(x) && ( x == x->parent->rc ))
//是否有父节点
#define HasParent(x) ( !IsRoot(x) ) //不为根节点,就有父节点
//是否有左孩子
#define HasLChild(x) ( x->lc )
//是否有右孩子
#define HasRChild(x) ( x->rc )
//至少有一个孩子
#define HasOneChild(x) ( HasLChild(x) || HasRChild(x) )
//同时拥有两个孩子
#define HasBothChild(x) ( HasRChild(x) && HasLChild(x) )
//是否为叶节点
#define IsLeaf(x) ( !HasOneChild(x) )
//兄弟关系的节点和指针
#define sibling(p) ( IsLChild( *(p) ) ? (p)->parent->rc : (p)->parent-lc )
//叔叔关系的节点和指针
#define uncle(p) ( IsLChild( *( (p)->parent ) ) ? (p)->parent->parent->rc : (p)->parent->parent->lc )
//来自父亲的引用
#define FromParentTo(x) ( IsRoot(x) ? _root : (IsLChild(x) ? x->parent->lc : x->parent->rc ))
/***************************************************************************************************************/

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
    int size();
    //将元素作为当前节点的左孩子插入
    BinNodePosi(T) insertAsLC(const T&);
    //将元素作为当前节点的右孩子插入
    BinNodePosi(T) insertAsRC(const T&);
    //取当前节点的后继---取决于那种遍历,此处应用于中序遍历
    BinNodePosi(T) succ();
    
    //层次遍历,借助队列数据结构
    template <typename VST>
    void travLevel(VST &);
    
    //先序遍历---递归版
    template <typename VST>
    void travPre_R(BinNodePosi(T), VST &);
    //中序遍历---递归版
    template <typename VST>
    void travIn_R(BinNodePosi(T), VST &);
    //后序遍历---递归版
    template <typename VST>
    void travPost_R(BinNodePosi(T), VST &);
    
    //先序遍历---迭代版 VLR
    template <typename VST>
    void travPre_I(BinNodePosi(T), VST &);
    //辅助方法---沿最左侧通路
    template <typename VST>
    static void visitAlongLeftBranch(BinNodePosi(T), VST& , MyStack<BinNodePosi(T)> &); 
    
    //中序遍历---迭代版1,无需栈辅助,借助直接后继 LVR
    template <typename VST>
    void travIn_I(BinNodePosi(T), VST &);
    //中序遍历---迭代版2 LVR
    template <typename VST>
    void travIn_I2(BinNodePosi(T), VST &);
    
    //后序遍历---迭代版 LRV
    template <typename VST>
    void travPost_I(BinNodePosi(T), VST &);
    //辅助方法---最高左侧可见叶节点(highest left visiable from left)
    static void gotoHLVFL(MyStack<BinNodePosi(T)> &);
    
    //先序遍历统一接口,随机选取递归版或迭代版
    template <typename VST>
    void travPre(VST &visit);
    //中序遍历统一接口,随机选取递归版或迭代版
    template <typename VST>
    void travIn(VST &visit);
    //后序遍历统一接口,随机选取递归版或迭代版
    template <typename VST>
    void travPost(VST &visit);
};

//二叉树模板类
template <typename T>
class MyBinTree{
public:
    //默认构造函数
    MyBinTree():_size(0), _root(NULL) {}
    //析构函数
    ~MyBinTree(){
        if(_root)
            remove(_root);
    }
    //返回规模
    int size()const { return _size; }
    //判空
    bool empty()const { return !_size; }
    //返回根节点
    BinNodePosi(T) root()const { return _root; }
    //插入根节点
    BinNodePosi(T) insertRoot(const T &);
    //更新节点的高度
    int updateHeight(BinNodePosi(T) );
    //更新节点高度及其祖先的高度
    void updateHeightAbove(BinNodePosi(T) );
    //将元素e作为节点x的左孩子(原无)插入
    BinNodePosi(T) insertAsLC(BinNodePosi(T), const T &);
    //将元素e作为节点x的右孩子(原无)插入
    BinNodePosi(T) insertAsRC(BinNodePosi(T), const T &);
    //将树T作为左子树接入
    BinNodePosi(T) attachAsLC(BinNodePosi(T), MyBinTree<T>* &);
    //将树T作为右子树接入
    BinNodePosi(T) attachAsRC(BinNodePosi(T), MyBinTree<T>* &);
    //删除以位置x处节点为根的子树, 返回该子树原先的规模
    int remove(BinNodePosi(T)) ;
    //递归删除左右子树
    int removeAt(BinNodePosi(T));
    //将子树x从当前树中摘除,并将其转换为一棵独立子树
    MyBinTree<T>* secede(BinNodePosi(T) );
    
    //函数对象, 遍历
    //先序遍历
    template <typename VST>
    void travPre(VST &);
    //中序遍历
    template <typename VST>
    void travIn(VST &);
    //后序遍历
    template <typename VST>
    void travPost(VST &);
    //层次遍历
    template <typename VST>
    void travLevel(VST &);
    
    //比较操作符
    template <typename T>
    friend bool operator==(const MyBinTree<T> &, const MyBinTree<T> &);
    template <typename T>
    friend bool operator!=(const MyBinTree<T> &, const MyBinTree<T> &);
    template <typename T>
    friend bool operator <(const MyBinTree<T> &, const MyBinTree<T> &);
    template <typename T>
    friend bool operator<=(const MyBinTree<T> &, const MyBinTree<T> &);
    template <typename T>
    friend bool operator >(const MyBinTree<T> &, const MyBinTree<T> &);
    template <typename T>
    friend bool operator>=(const MyBinTree<T> &, const MyBinTree<T> &);
protected:
    //规模
    int _size;
    //根节点
    BinNodePosi(T) _root;
    //在两个元素中选取较大者
    int max(const int, const int);
};
#endif