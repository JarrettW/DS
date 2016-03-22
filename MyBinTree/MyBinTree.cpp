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
    MyStack<BinNodePosi(T)> S; //辅助栈
    while(true){
        visitAlongLeftBranch(x, visit, S);
        if(S.empty())
            break;
        x = S.pop();
    }
}
//沿最左侧通路
template <typename T>
template <typename VST>
static void BinNode<T>::visitAlongLeftBranch(BinNodePosi(T) x, VST &visit, MyStack<BinNodePosi(T)> &S){
    while(x){
        visit(x->data);  //访问当前节点
        if(HasRChild(*x))
            S.push(x->rc);  //若有右孩子,入栈暂存
        x = x->lc;  //沿左分支深入一层
    }
}
//中序遍历--迭代版1,无序栈辅助,借助中序遍历之直接后继 LVR
template <typename T>
template <typename VST>
void BinNode<T>::travIn_I(BinNodePosi(T) x, VST &visit){
    bool backtrack = false; //前一步是否刚从右子树回溯-省去栈,仅O(1)
    while(true)
        if( !backtrack && HasLChild(*x))
            x = x->lc;
        else{
            visit(x->data);
            if( HasRChild(*x) ){
                x = x->rc;
                backtrack = false;//关闭回溯标志,继续循环查看rc的左右情况
            }else{
                if( !(x = x->succ()))
                    break;
                backtrack = true;
            }
        }
}
//中序遍历---迭代版2 LVR
template <typename T>
template <typename VST>
void BinNode<T>::travIn_I2(BinNodePosi(T) x, VST &visit){
    //辅助栈
    MyStack<BinNodePosi(T)> S;
    while(true){
        //沿左侧通路,直至没有左侧分支节点
        if(x){
            S.push(x);
            x = x->lc;
        }else( !S.empty()){
            x = S.pop(); //第一次出栈的是最左侧叶节点
            visit(x->data);  //访问之
            x = x->rc;  //然后先访问最左侧的节点, 检查是否有右兄弟,继续循环检查访问
        }else
            break;
    }
}
//后序遍历---迭代版 LRV
template <typename T>
template <typename VST>
void BinNode<T>::travPost_I(BinNodePosi(T) x, VST &visit){
    MyStack<BinNodePosi(T)> S;
    if(x)
        S.push(x);
    while(!S.empty()){
        if( S.top() != x->parent)//若栈顶非当前节点之父则必为其右兄
            gotoHLVFL(S);
        
    }
}
//辅助方法---最高左侧可见叶节点HLVFL(highest leaf visiable from left)
template <typename T>
template <typename VST>
void BinNode<T>::gotoHLVFL(MyStack<BinNodePosi(T)> & S){
    
}