#include "MyBTree.h"
//查找
template <typename T>
BNodePosi(T) MyBTree<T>::search(const T &e){
    //B树的查找从根节点开始
    BNodePosi(T) v = _root; _hot = NULL;
    //逐层查找
    while(v){
        //首先在第一层关键码中查找.r有两种可能,1.命中 2.不大于e的最大关键码
        int r = v->key.search(e);
        //若命中,则成功返回
        if( (0 <= r) && (e == v->key[r]) )
            return v;
        //否则,转入对应子树继续查找
        _hot = v; v = v->child[r + 1];
    }
    //至此,查找失败
    return NULL;
}

//插入
template <typename T>
bool MyBTree<T>::insert(const T &e){
    //检查e是否已经存在
    BNodePosi(T) v = search(e);
    //若存在,插入失败,返回false
    if(v)
        return false;
    //若不存在,在_hot关键码中搜索(必定失败)e,找到合适的插入位置r
    int r = _hot->key.search(e);
    //插入关键码
    _hot->key.insert(r + 1, e);
    //创建一个空子树指针
    _hot->child.insert(r + 2, NULL);
    //增加规模
    _size++;
    //检查是否上溢,需做分裂
    solveOverflow(_hot);
    //成功返回
    return NULL;
}

//上溢处理, 分裂
template <typename T>
void MyBTree<T>::solveOverflow(BNodePosi(T) v){
    //递归基,当前节点并未上溢
    if( _order >= v->child.size()) return;
    //轴点(此时应有_order = key.size() = child.size() -1)
    int r = _order / 2;
    //创建一个新节点, 注意新节点已有一个空孩子
    BNodePosi(T) u = new BNode<T>();
    //v右侧_order-s-1个孩子及关键码分裂为右侧节点u
    for(int j = 0; j < _order-s-1; j++){
        u->child.insert(j, v->child.remove(r + 1));
        u->key.insert(j, v->key.remove(r + 1));
    }
    //移动v最靠右的孩子
    u->child[_order-r-1] = v->child.remove(r+1);
    //若u的孩子们非空, 则---令他们的父节点统一指向u
    if(u->child[0])
        for(int j = 0; j < _order-s; j++)
            u->child[i]->parent = u;
    //v当前的父节点p
    BNodePosi(T) p = v->parent;
    //若p空则创建之
    if(!p){
        _root = p = new BNode<T>();
        p->child[0] = v;
        v->parent = p;
    }
    //p中指向u的指针的秩
    int r = 1 + p->key.search(v->key[0]);
    //轴点关键码上升
    p->key.insert(r, v->key.remove(s));
    //新节点u与父亲节点p互联
    p->child.insert(r + 1, u); u->parent = p;
    //上升一层,如有必要则继续分裂
    solveOverflow(p);
}