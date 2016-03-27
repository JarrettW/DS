#include "MyAVL.h"
//理想平衡条件
#define Balanced(x) ( stature(x->lc) == stature(x->rc) )
//平衡因子
#define BalFac(x) ( stature(x->lc) - stature(x->rc) )
//AVL平衡条件
#define AclBalanced(x) ( (-2 < BalFac(x)) && (BalFac(x) < 2) )

//恢复平衡的调整方案,决定于失衡节点的更高孩子、更高孙子节点的方向
//在左、右孩子中取更高者， 在AVL平衡调整前，借此重构方案
template <typename T>
BinNodePosi(T)& MyAVL<T>::tallerChild(BinNodePosi(T) &x){
    if(stature(x->lc) > stature(x->rc) )
        return x->lc;
    else if(stature(x->lc) < stature(x->rc))
        return x->rc;
    else if(IsLChild(x))
        return x->lc;
    else
        return x->rc; 
}

//AVL树的节点插入
template <typename T>
BinNodePosi(T) MyAVL<T>::insert(const T &e){
    BinNodePosi(T) &x = search(e);
    if(x)
        return x;
    BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
    _size++;
    //此时, x的父亲_hot若增高, 则其祖父有可能失衡
    for(BinNodePosi(T) g = _hot; g; g = g->parent){
        if( !AvlBalanced(g)){//一旦发现失衡,则采用"3+4"算法)使之复衡,并将子树
            FromParentTo(g) = rotateAt( tallerChild(tallerChild(g)));  //重新接入原树
        break;//g恢复平衡后,局部子树高度必然复原,其祖先亦必如此,调整随即结束
        }else //否则依然平衡
            updateHeight(g); //更新高度
    }//至多只需一次调整; 若果真做过调整,则全树必然高度复原
    return xx;  //返回新节点位置
}

//AVL树的删除
template <typename T>
bool MyAVL<T>::remove(const T &e){
    BinNodePosi(T) &x = search(e);
    if(!x)
        return false;
    removeAt(x, _hot);
    --_size;
    //原节点之父_hot及其祖先均可能失衡
    for(BinNodePosi(T) g = _hot; g; g = g->parent){
        if(!AclBalanced(g))
            g = FromParentTo(g) = rotateAt(tallerChild(tallerChild(g)));
        updateHeight(g);
    }
    return true;
}

//按照"3+4"结构,联接3个节点及四棵子树
template <typename T>
BinNodePosi(T) MyBinSearchTree<T>::connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
                                             BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3, BinNodePosi(T) T4){
    a->lc = T1; if(T1) T1->parent = a;
    a->rc = T2, if(T2) T2->parent = a;
    updateHeight(a);
    
    c->lc = T3, if(T3) T3->parent = c;
    c->rc = T4, if(T4) T4->parent = c;
    updateHeight(c);
    
    b->lc = a; if(a) a->parent = b;
    b->rc = c; if(c) c->parent = b;
    updateHeight(b);
    
    return b;
}
//AVL树的统一重平衡, zig,zag图上一目了然
template <typename T>
BinNodePosi(T) MyBinSearchTree<T>::rotateAt(BinNodePosi(T) v){
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    if(IsLChild(p) ) //zig
        if(IsLChild(v)){ //zig-zig
            p->parent = g->parent; //向上联接
            return connect34( v, p, g, v->lc, v->rc, p->rc, g->rc);
        }else{ //zig-zig
            v->parent = g->parent; //向上联接
            return connect34( p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    else //zag
        if(IsRChild(v)){ //zag-zag
            p->parent = g->parent; //向上联接
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }else{ //zag-zig
            v->parent = g->parent; //向上联接
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
}