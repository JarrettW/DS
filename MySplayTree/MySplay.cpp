#include "MySplay.h"
template <typename T>
BinNodePosi(T) MySplay<T>::splay(BinNodePosi(T) &v){
    //如果v不存在
    if(!v)
        return NULL;
    //v的父亲和祖父
    BinNodePosi(T) p; BinNodePosi(T) g;
    //while双层伸展
    while( (p = v->parent) && (g = p->parent) ){//自下而上,反复对v做双层伸展
        BinNodePosi(T) gg = g->parent; //每轮之后v都以原曾祖父为父
        //1.判断左、右孩子。 2.相应的交换移位(先孩子,后v/p/g)，即旋转
        if(IsLChild(v))
            if(IsLChild(p)){ //zig-zig, v和p是左孩子
                attachAsLChild(g, p->rc); attachAsLChild(p, v->rc);
                attachAsRChild(p, g); attachAsRChild(v, p);
            }else{ //zig-zag, v是左孩子, p是右孩子
                attachAsLChild(p, v->rc); attachAsRChild(g, v->lc);
                attachAsLChild(v, g); attachAsRChild(v, p);
            }
        else if(IsRChild(p)){ //zag-zag, v和p是右孩子 
            attachAsRChild(g, p->lc); attachAsLChild(p, v->lc);
            attachAsLChild(v, p); attachAsRChild(p, g);
        }else{ //zag-zig, v是右孩子,p是左孩子
            attachAsRChild(p, v->lc); attachAsLChild(g, v->rc);
            attachAsLChild(v, p); attachAsRChild(v, g);
        }
        if(!gg)
            v->parent = NULL; //若v原先的祖父gg不存在,则v为树根
        else //否则, gg此后应该以v作为左或右孩子
            (g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
        updateHeight(g); updateHeight(p); updateHeight(v);
    }//双层伸展结束, 必有g==NULL, 但p可能非空
    //while结束,若p不为空,额外再做一次单旋
    if(p = v->parent){
        if( IsLChild(v)){
            attachAsLChild(p, v->rc); attachAsRChild(v, p);
        }else{
            attachAsRChild(p, v->lc); attachAsLChild(v, p);
        }
        updateHeight(p); updateHeight(v);
    }
    v->parent = NULL;  //v已到达根节点,其父为NULL
    return v;
}

//伸展树查找
template <typename T>
BinNodePosi(T)& MySplay<T>::search(const T &e){
    BinNodePosi(T) p = searchIn(_root, e, _hot = NULL);
    _root = splay(p ? p : _hot); //将最后一个被访问的节点伸展至根
    return _root; //如果为_hot则是父位置, _hot的设置利于插入和删除
}

//伸展树的插入
template <typename T>
BinNodePosi(T) MySplay<T>::insert(const T &e){
    //如果树为空,则更新规模,创建根节点
    if(!_root){
        _size++;
        return _root = new BinNode<T>(e);
    }
    //查找e是否已存在, 若不存在,返回的节点即是应该插入位置的父节点
    if( e == search(e)->data)
        return _root; //若已存在, e所在的节点位置已被伸展至树根
    _size++;
    BinNodePosi(T) t = _root; //若e不存在,合适的插入位置的父亲已被伸展至树根
    //只需比较e的大小, 插入为左孩子还是右孩子
    if( _root->data < e){ //插入新根,小于e,t(_root)为e左孩子,t->rc为e的右孩子
        t->parent = _root = new BinNode<T>(e, NULL, t, t->rc);
        if(HasRChild(t)){  //若有右孩子,重新联接其父亲
            t->rc->parent = _root;
            t->rc = NULL;
        }
    }else{ //相反
        t->parent = _root = new BinNode<T>(e, NULL, t->lc, t);
        if(HasLChild(t)){
            t->lc->parent = _root;
            t->lc = NULL;
        }
    }
    updateHeightAbove(t);
    return _root;
}

//伸展树的删除
template <typename T>
bool MySplay<T>::remove(const T &e){
    if( !_root || (e != search(e)->data) )
        return false;
    //至此,所删节点已被伸展至树根
    BinNodePosi(T) w = _root;
    if( !HasLChild(_root)){ //若无左子树, 则直接删除
        _root = _root->rc;
        if(_root)
            _root->parent = NULL;
    }else if(!HasRChild(_root)){ //若无右子树,则直接删除
        _root = _root->lc;
        if(_root)
            _root->parent = NULL;
    }else{ //若左右子树皆存在
        BinNodePosi(T) lTree = _root->lc;
        lTree->parent = NULL; _root->lc = NULL; //暂时将左子树切除
        _root = _root->rc; _root->parent = NULL;//只保留右子树
        search(w->data);//以原树为目标,做一次(必定失败)的查找
        //至此,右子树中最小节点必伸展至根,且(因无雷同节点)其左子树必空,于是只
        //需将原左子树接回原位置即可
        _root->lc = lTree; lTree->parent = _root;
    }
    _size--;
    if(_root)
        updateHeight(_root);
    return true;
}