#ifndef MYQUADLISTNODE_H_
#define MYQUADLISTNODE_H_
//四联表节点模板类
#include "MyEntry.h"
//跳转表节点位置
#define MyQlistNodePosi(T) MyQuadlistNode<T>*

template <typename T>
struct MyQuadlistNode{
   //所存词条
   T entry;
   //前驱
   MyQlistNodePosi(T) pred;
   //后继
   MyQlistNodePosi(T) succ;
   //上邻
   MyQlistNodePosi(T) above;
   // 下邻
   MyQlistNodePosi(T) below;
   //构造
   MyQuadlistNode(T e = T(), MyQlistNodePosi(T) p = NULL, MyQlistNodePosi(T) s = NULL,
                             MyQlistNodePosi(T) a = NULL, MyQlistNodePosi(T) b = NULL):
                             entry(e), pred(p), succ(s), above(a), below(b) {}
   //插入新节点(后继,上邻), 以当前节点为前驱, 以节点b为下邻
   MyQlistNodePosi(T) insertAsSuccAbove(const T &e, MyQlistNodePosi(T) b = NULL);
} ;
#endif