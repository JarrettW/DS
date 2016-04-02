#include "MySkiplist.h"
//跳表查找
//qlist为顶层列表, p为qlist的首节点
//若成功,p为命中关键码所属塔的顶部节点, qlist为p所属列表
//否则,p为所属塔的基座, 该塔对应于不大于k的最大且最靠右关键码,qlist为空
//约定: 多个词条命中时, 沿四联表取最靠后者
template <typename K, typename V>
bool MySkiplist<K, V>::skipSearch(ListNode< MyQuadlist<MyEntry<K, V>>*>* &qlist, MyQuadlistNode<MyEntry<K, V>>* &p, K &k){
    //在每一层
    while(true){
        //从前向后查找
        while( p->succ && (p->entry.key <= k))
            //直到出现更大的Key或溢出至trailer
            p = p->succ;
        //此时倒回一步, 即可判断是否
        p = p->pred;
        //命中
        if( p->pred && ( k == p->entry.key))
            return true;
        //否则转入下一层
        qlist = qlist->succ;
        //若已穿透到底层,则意味着失败
        if(!qlist->succ) return false;
        //否则转至当前塔的下一节点
        p = (p->pred) ? p->below : qlist->data->first();
    }
}

//插入
template <typename K, typename V>
bool MySkiplist<K, V>::put(K k, V v){
    //待插入的词条,初始化
    MyEntry<K, V> e = MyEntry<K, V>(k, v);
    //如果原味空,便插入首个词条
    if(empty())
        insertAsFirst( new MyQuadlist<MyEntry<K, V>>);
    //从顶层四联表的
    ListNode<MyQuadlist<MyEntry<K, V>>*> *qlist = first();
    //首节点出发
    MyQuadlistNode<MyEntry<K, V>> *p = qlist->data->first();
    //查找适当的插入位置(不大于关键码k的最后一个节点p)
    if( skipSearch(qlist, p, k))
        while(p->below)
            p = p->below;  //若有雷同词条, 则需强制转到塔底
    //以下,紧邻于p的右侧, 一座新塔将自底而上逐层生长
    qlist = last();
    //新节点b即新塔基座
    MyQuadlistNode<MyEntry<K, V>>* b = qlist->data->insertAfterAbove(e, p);
    //经投掷硬币, 若确定新塔需要再长高一层,则
    while( rand() & 1){
        //找出不低于此高度的最近前驱
        while(qlist->data->valid(p) && !p->above)
            p = p->pred;
        //若该前驱是header
        if( !qlist->data->valid(p)){
            //且当前已是最顶层,则意味着必须
            if(qlist == first())
                insertAsFirst(new MyQuadlist<MyEntry<K, V>>);//首先创建新的一层, 然后
            //将p转至上一层MySkiplist的header
            p = qlist->pred->data->first()->pred;
        }else //否则, 可径自
            p = p->above; //将p提升至该高度
        //上升一层, 并在该层
        qlist = qlist->pred;
        //将新节点插入p之后、b之上
        b = qlist->data->insertAfterAbove(e, p, b);
    }
    return true;
}

//读取
template <typename K, typename V>
V* MySkiplist<K, V>::get(K k){
    if(empty())
        return NULL;
    //从顶层MyQuadlist的
    ListNode< MyQuadlist<MyEntry<K, V>>*> * qlist = first();
    //首节点开始
    MyQuadlistNode<MyEntry<K, V>>* p = qlist->data->first();
    //查找并报告
    if(skipSearch( qlist, p, k))
        return &p->entry.value;
    return NULL;
}

//删除
template <typename K, typename V>
bool MySkiplist<K, V>::remove(K k){
    //空表
    if(empty())
        return false;
    //从顶层MyQuadlist的
    ListNode< MyQuadlist<MyEntry<K, V>>* > *qlist = first();
    //首节点开始
    MyQuadlistNode<MyEntry<K, V>>* p = qlist->data->first();
    //目标节点不存在, 直接返回
    if(!skipSearch(qlist, p, k))
        return false;
    do{ //若目标词条存在, 则逐层拆除与之对应的塔
        //记住下一层节点,并
        MyQuadlistNode<MyEntry<K, V>> *lower = p->below;
        //删除当前节点再
        qlist->data->remove(p);
        //转入下一层
        p = lower; qlist = qlist->succ;
    }while( qlist->succ); //如上下不断重复,直到塔基
    while( !empty() && first()->data->empty() )//逐一地
        MyList::remove(first()); //清除已可能不含词条的顶层MyQuadlist
    return true;
}