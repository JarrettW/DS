#ifndef MYSKIPLIST_H_
#define MYSKIPLIST_H_
#include "..\MyList\MyList.cpp"
#include "MyEntry.h"
#include "MyQuadlist.cpp"
#include "MyDictionary.h"
//跳表模板类
template <typename K, typename V>
class MySkiplist: public MyDictionary<K, V>, public MyList< MyQuadlist< MyEntry<K, V> >*> {
protected:
    //跳表查找
    bool skipSearch(ListNode< MyQuadlist<MyEntry<K, V>>*>* &qlist, MyQuadlistNode<MyEntry<K, V>>* &p, K &k);
public:
    //底层MyQuadlist的规模
    int size()const { return empty() ? 0 : last()->data->size(); }
    //层高
    int level() { return MyList::size(); }
    //插入
    bool put(K , V);
    //读取
    V* get(K );
    //删除
    bool remove(K );
};
#endif