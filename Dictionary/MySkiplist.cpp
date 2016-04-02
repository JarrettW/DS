#include "MySkiplist.h"
//跳表查找
//qlist为顶层列表, p为qlist的首节点
//若成功,p为命中关键码所属塔的顶部节点, qlist为p所属列表
//否则,p为所属塔的基座, 该塔对应于不大于k的最大且最靠右关键码,qlist为空
//约定: 多个词条命中时, 沿四联表取最靠后者
template <typename T>
bool MySkiplist<K, V>::skipSearch(ListNode< MyQuadlist<MyEntry<K, V>>*>* &qlist, MyQuadlistNode<MyEntry<K, V>>* &p, K &k){
    
}