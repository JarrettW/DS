#include "MyBinTree.h"
/************************BinNode method***********************/
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
        x = S.pop();
        visit(x->data);
    }
}
//辅助方法---最高左侧可见叶节点HLVFL(highest leaf visiable from left)
template <typename T>
template <typename VST>
void BinNode<T>::gotoHLVFL(MyStack<BinNodePosi(T)> & S){
    while(BinNodePosi(T) x = S.top()){
        if(HasLChild(*x)){
            if(HasRChild(*X))
                S.push(x->rc);  //右孩子先入栈
            S.push(x->lc);  //左孩子入栈
        }else
            S.push(x->rc);
    }
    S.pop();  //弹出栈顶的NULL
}
//先序遍历统一接口,随机选取递归版或迭代版
template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST &visit){
    switch(rand() % 2){
        case 0: travPre_I(this, visit); break;  //迭代版
        case 1: travPre_R(this, visit); break;  //递归版 
    }
}
//中序遍历统一接口,随机选取递归版或迭代版
template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST &visit){
    switch(rand() % 3){
        case 0: travIn_I(this, visit); break;  //迭代版
        case 1: travIn_I2(this, visit); break; //迭代版
        default: travIn_R(this, visit); break; //递归版
    }
}
//后序遍历统一接口,随机选取递归版或迭代版
template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST &visit){
    switch(rand() % 2){
        case 0: travPost_I(this, visit); break; //迭代版
        case 1: travPost_R(this, visit); break; //递归版
    }
}

/*************************MyBinTree method********************/
//插入根节点
template <typename T>
BinNodePosi(T) MyBinTree<T>::insertRoot(const T &e){
    _size = 1;
    return _root = new BinNode<T>(e);
}
//将元素e作为节点x的左孩子(原无)插入
template <typename T>
BinNodePosi(T) MyBinTree<T>::insertAsLC(BinNodePosi(T) x, const T &e){
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);  //更新x的树高
    return x->lc;    
}
//将元素e作为节点x的右孩子(原无)插入
template <typename T>
BinNodePosi(T) MyBinTree<T>::insertAsRC(BinNodePosi(T) x, const T &e){
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}
//将树T作为左子树接入, 返回接入的节点
template <typename T>
BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T){
    x->lc = T->_root;  //将T的根节点当做左孩子与x链接
    x->lc->parent = x;
    _size += T->_size;  //更新规模
    updateHeightAbove(x); //更新高度
    T->_root = NULL;
    T->_size = 0;
    release(T);
    T = NULL;
    return x;
}
//将树T作为右子树接入, 返回接入的节点
template <typename T>
BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T){
    x->rc = T->_root;
    x->rc->parent = x;
    _size += T->_size;
    updateHeightAbove(x);
    T->_root = NULL:
    T->_size = 0;
    release(T);
    T = NULL;
    return x;
}
//删除以位置x处节点为根的子树, 返回该子树原先的规模
template <typename T>
int MyBinTree<T>::remove(BinNodePosi(T) x){
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    int n = 1 + removeAt(x);
    _size -= n;
    return n;
}
//递归地删除左右子树
template <typename T>
int MyBinTree<T>::removeAt(BinNodePosi(T) x){
    if(!x)
        return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x);
    return n;
}
//将子树x从当前树中摘除,并将其转换为一棵独立子树
template <typename T>
BinTree<T>* MyBinTree<T>::secede(BinNodePosi(T) x){
    BinTree<T> *T = new BinTree<T>;
    FromParentTo(*x) = NULL;
    updateHeightAbove(x->parent);
    T->_root = x;
    x->parent = NULL;
    T->_size = x->size();
    _size -= T->size();
    return T;
}
//函数对象,遍历
//先序遍历
template <typename T>
template <typename VST>
void MyBinTree<T>::travPre(VST &visit){
    if(_root)
        _root->travPre(visit);
}
//中序遍历
template <typename T>
template <typename VST>
void MyBinTree<T>::travIn(VST &visit){
    if(_root)
        _root->travIn(visit);
}
//后序遍历
template <typename T>
template <typename VST>
void MyBinTree<T>::travPost(VST &visit){
    if(_root)
        _root->travPost(visit);
}
//层次遍历
template <typename T>
template <typename VST>
void MyBinTree<T>::travLevel(VST &visit){
    if(_root)
        _root->travLevel(visit);
}
//比较操作符
template <typename T>
bool operator==(const BinTree<T> &lhs, const BinTree<T> &rhs){
    return lhs._root && rhs._root && lhs._root->data ==  rhs._root->data;
}
template <typename T>
bool operator!=(const BinTree<T> &lhs, const BinTree<T> &rhs){
    return !(lhs == rhs);
}
template <typename T>
bool operator <(const BinTree<T> &lhs, const BinTree<T> &rhs){
    return lhs._root && rhs._root && lhs._root->data < rhs._root->data;
}
template <typename T>
bool operator<=(const BinTree<T> &lhs, const BinTree<T> &rhs){
    return !(lhs > rhs);
}
template <typename T>
bool operator >(const BinTree<T> &lhs, const BinTree<T> &rhs){
    return !(lhs < rhs) && !(lhs == rhs);
}
template <typename T>
bool operator>=(const BinTree<T> &lhs, const BinTree<T> &rhs){
    return !(lhs < rhs);
}
//更新节点的高度
template <typename T>
int MyBinTree<T>::updateHeight(BinNodePosi(T) x){
    
}