#include "MyBinTree.h"
//当前节点规模
template <typename T>
int BinNode<T>::size()const{
    if(!this)  //当前节点为NULL,则规模为0
        return 0;
    static int count = 0;  //计数器
    MyQueue<BinNodePosi(T)> Q;  //辅助队列
    Q.enqueue(this); //当前节点入队
    while( !Q.empty() ){  //队列不为空时,循环出队入队并计数
        BinNodePosi(T) x = Q.dequeue();  //出队,并赋值临时变量x
        if(x)
            count++;  //如果x不为空,计数
        if(HasLChild(*x))
            Q.enqueue(x->lc);  //若存在左孩子,将其入队
        if(HasRChild(*x))
            Q.enqueue(x->rc);  //多存在右孩子,也将其入队
    }
    return count - 1;  //返回此即为规模
}
//将元素作为当前节点的左孩子插入
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T &e){
    return lc = new BinNode(e, this);
}
//将元素作为当前节点的右孩子插入
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T &e){
    return lc = new BinNode(e, this);
}
//中序遍历(LVR),取当前节点的后继
template <typename T>
BinNodePosi(T) BinNode<T>::succ(){
    BinNodePosi(T) x = this;
    if(rc){ //若有右孩子,则直接后继在右子树中
        s = rc;
        while(HasLChild(*x))
            x = x->lc;  //即右子树中最靠左(最小)的节点
    }else{//否则,succ应该是"将当前节点包含于其左子树中的最低祖先"
        while(IsRChild(*x))
            x = x->parent;//逆向地沿右向分支,不断朝左上方移动
        x = x->parent;//最后再朝左上方移动一步,即抵达直接后继(若存在)
    }
    return x;
}
//层次遍历,借助队列数据结构
template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST &visit){
    MyQueue<BinNodePosi(T)> Q;
    Q.enqueue(this);  //当前节点入队
    while( !Q.empty() ){  //只要队列不为空
        BinNodePosi(T) x = Q.dequeue();  //出队
        visit(x->data);  //访问刚出队元素
        if(HasLChild(*x))
            Q.enqueue(x->lc);  //若有,左孩子入队
        if(HasRChild(*x))
            Q.enqueue(x->rc);  //若有,右孩子入队
    }
}
//先序遍历---递归版 VLR
template <typename T>
template <typename VST>
void BinNode<T>::travPre_R(BinNodePosi(T) x, VST &visit){
    if(!x)  //递归基
        return;
    visit(x->data);  //访问当前节点数据
    travPre_R(x->lc, visit);  //访问左孩子
    travPre_R(x->rc, visit);  //访问右孩子
}
//中序遍历---递归版 LVR
template <typename T>
template <typename VST>
void BinNode<T>::travIn_R(BinNodePosi(T) x, VST &visit){
    if(!x)
        return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}
//后序遍历---递归版 LRV
template <typename T>
template <typename VST>
void BinNode<T>::travPost_R(BinNodePosi(T) x, VST &visit){
    if(!x)
        return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}
//先序遍历---迭代版 VLR
template <typename T>
template <typename VST>
void BinNode<T>::travPre_I(BinNodePosi(T) x, VST &visit){
    
}