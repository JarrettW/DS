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

//删除
template <typename T>
bool MyBTree<T>::remove(const T &e){
    //1.查找根节点及元素e是否存在,若不存在,直接返回false
    BNodePosi(T) v = search(e);
    if(!v)
        return false;
    //至此,确定目标关键码在节点v中的秩
    int  r = v->key.search(e);
    //若v非叶子,则e的后继必属于某叶节点. 2.与后继交换
    if(v->child[0]){
        BNodePosi(T) u = v->child[r+1];//在右子树中一直向左
        while(u->child[0]) u = u->child[0]; //(u的最终结果为v的直接后继)找出e的后继
        v->key[r] = u->key[0]; v = u; r = 0; //并与之交换位置
    }//至此,v必然位于最底层,且其中第r个关键码就是待删除者
    //删除e,以及其下两个外外部节点之一
    v->key.remove(r); v->child.remove(r+1); _size--;
    //如有必要,需做旋转或合并
    solveUnderflow(v);
    return true;
}

//因删除而下溢之后的合并处理
template <typename T>
void MyBTree<T>::solveUnderflow(BNodePosi(T) v){
    //递归基: v为发生下溢
    if( (_order+1) / 2 <= v->child.size())
        return;
    //定位v的父亲节点
    BNodePosi(T) p = v->parent;
    //递归基: 已经到根节点,没有孩子的下限
    if(!p){
        //但倘若作为树根的v已不含关键码,却有(唯一的)非空孩子,则
        if( !v->key.size() && v->child[0]){
            //这个节点可被跳过
            _root = v->child[0]; _root->parent = NULL;
            //并因不再有用而被销毁
            v->child[0] = NULL; v = NULL;
        }
        return;
    }
    //确定v是p的第r个孩子; 此时v可能不含关键码,故不能通过关键码查找
    int r = 0; while(p->child[r] != v) r++;
    //情况1: 向左兄弟借关键码
    if(0 < r){ //若v不是p的第一个孩子,则
        BNodePosi(T) ls = p->child[r-1]; //左兄弟必存在
        if( (_order + 1) / 2 < ls->child.size()){//若该兄弟足够胖
            //p先借出一个关键码给v(作为最小关键码)
            v->key.insert(0, p->key[r-1]);
            //ls(左兄弟)的最大关键码再转给p
            p->key[r-1] = ls->key.remove(ls->key.size() - 1);
            //同时ls的最右侧孩子过继给v
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            //作为v的最左侧孩子
            if(v->child[0])
                v->child[0]->parent = v;
            return; //至此, 通过右旋已完成当前层(以及所有层)的下溢处理
        }
    }
    //至此,左兄弟要么为空, 要么太"瘦"
    //情况2: 向右兄弟借关键码
    if( p->chlid.size() - 1 > r){
        BNodePosi(T) rs = p->child[r+1]; //右兄弟必存在
        if( (_order + 1) / 2 < rs->child.size()){//若该兄弟足够"胖"
            //p先借出一个关键码给v(作为最大关键码)
            v->key.insert( v->key.size(), p->key[r]);
            //rs(右兄弟)的最小关键码转入p
            p->key[r] = rs->key.remove(0);
            //同时rs的最左侧孩子过继给v
            v->child.insert( v->child.size(), rs->child.remove(0));
            //作为v的最右侧孩子
            if(v->child[v->child.size() - 1] )
                v->child[v->child.size() -1]->parent = v;
            return; 
        }
    }
    //情况3:左右兄弟都太瘦或一者为空, 合并
    if( 0 < r){ //与左兄弟合并
        //左兄弟必存在
        BNodePosi(T) ls = p->child[r-1];
        //p的第r-1个关键码转入ls, v不再是p的第r个孩子
        ls>key.insert(ls->key.size(), p->key.remove(r-1));
        p->child.remove(r);
        ls>child.insert(ls->child.size(), v->child.remove(0));
        //v的最左侧孩子过继给ls做最右侧孩子
        if(ls->child[ls->child.size() - 1])
            ls->child[ls->child.size - 1]->parent = ls;
        while( !v->key.empty() ){ //V剩余的关键码和孩子,依次传入ls
            ls->key.insert( ls->key.size(), v->key.remove(0));
            ls->child.insert( ls->child.size(), v->child.remove(0));
            if(ls->child[ls->child.size() -1])
                ls->child[ls->child.size() -1]->parent = ls;
        }
        v = NULL;
    }else{//与右兄弟合并
    
        //v的最左侧孩子过继给ls做最右侧孩子
    
    }
    //上升一层, 如有必要则继续分裂.
}