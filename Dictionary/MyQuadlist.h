#ifndef MYQUADLIST_H_
#define MYQUADLIST_H_
#include "MyQuadlistNode.h"  //引入四联表节点类
//四联表模板类
template <typename T>
class MyQuadlist{
private:
    //规模
    int _size;
    //头哨兵
    MyQuadlistNode(T) header;
    //尾哨兵
    MyQuadlistNode(T) trailer;
protected:
    //MyQuadlist创建时初始化
    void init();
    //清除所有节点, 返回被清除的节点数
    int clear();
public:
    //默认构造函数
    MyQuadlist() { init(); }
    //析构函数
    ~MyQuadlist(){
        clear();
        delete header;
        delete trailer;
    }
//只读访问接口
    //规模
    int size()const { return _size; }
    //判空
    bool empty()const { return _size <= 0; }
    //首节点位置
    MyQuadlistNode(T) first()const { return header->succ; }
    //末节点位置
    MyQuadlistNode(T) last()const { return trailer->pred; }
    //判断位置p是否对外合法
    bool valid(MyQuadlistNode(T) p){
        return p && ( trailer != p) && ( header != p);
    }
//可写访问接口
    //删除(合法)位置p处的节点, 返回被删除节点的数值
    T remove(MyQlistNodePosi(T) p);
    //将*e作为p的后继、b的上邻插入
    MyQlistNodePosi(T) insertAfterAbove(const T &e, MyQlistNodePosi(T) p, MyQlistNodePosi(T) b = NULL);
//遍历
    // 遍历各节点,一次实施指定操作(函数指针, 只读或局部修改)
    void traverse(void (*) (T &));
    //函数对象(可全局性修改节点)
    template <typename VST>
    void traverse(VST &);
};
#endif