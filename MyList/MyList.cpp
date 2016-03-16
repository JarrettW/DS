#include "MyList.h"
#include <initializer_list>
template <typename T>
//返回删除元素的总数
int MyList<T>::clear(){
    int oldSize = _size;
    while(0 < _size){ //逐一删除节点
        remove(header->succ);
    }
    return oldSize;
}
//初始化节点函数
template <typename T>
void MyList<T>::init(){
    _size = 0;
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = NULL;
    header->succ = trailer;
    trailer->succ = NULL;
    trailer->pred = header;
}
//拷贝区间节点
template <typename T>
void MyList<T>::copyNode(ListNodePosi(T) p, int n){
    init();
    while(n--){
        insertAsLast(p->data);
        p = p->succ;
    }
}
//列表初始化
template <typename T>
MyList<T>::MyList(std::initializer_list<T> li){
    init();
    auto beg = li.begin();
    auto size = li.size();
    while(size--){
        trailer->insertAsPred(*beg++);
        ++_size;
    }
}
//拷贝构造函数
template <typename T>
MyList<T>::MyList(const MyList<T> &ml){
    //如果列表本身不为空呢?应该需要clear()
    //clear();
    copyNode(ml.first(), ml.size());
}
//复制列表中自位置p起的n项
template <typename T>
MyList<T>::MyList(ListNodePosi(T) p, int n){
    copyNode(p, n);
}
//下标重载,支持循秩访问(效率低)
template <typename T>
T& MyList<T>::operator[](int r)const{
    ListNodePosi(T) p = first();
    while(r--){
        p = p->succ;
    }
    return p->data;
}
//判断列表是否排序,返回未排序的个数
template <typename T>
int MyList<T>::disorder()const{
    int count = 0;
    ListNodePosi(T) p = first();
    while(p){
        if(p->succ->data < p->data)
            ++count;
        p = p->succ;
    }
    return count;
}
//把e当做首节点插入,返回插入的节点
template <typename T>
ListNodePosi(T) MyList<T>::insertAsFirst(const T &e){
    _size++;
    return header->insertAsSucc(e);
}
//把e当做末节点插入
template <typename T>
ListNodePosi(T) MyList<T>::insertAsLast(const T &e){
    _size++;
    return trailer->insertAsPred(e);
}
//把e当做p的后继插入
template <typename T>
ListNodePosi(T) MyList<T>::insertA(ListNodePosi(T) p, const T &e){
    _size++;
    return p->insertAsSucc(e);
}
//把e当做p的前驱插入
template <typename T>
ListNodePosi(T) MyList<T>::insertB(ListNodePosi(T) p, const T &e){
    _size++;
    return p->insertAsPred(e);
}
//无序去重
template <typename T>
int MyList<T>::deduplicate(){
    if(_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    int count = 0;
    while(trailer != (p = p->succ)){
        ListNodePosi(T) q = find(p->data, p, count);
        q ? remove(q) : count++;
    }
}
//无序区间查找,默认从后向前查找
template <typename T>
ListNodePosi(T) MyList<T>::find(const T &e, ListNodePosi(T) p, int n)const{
    while( 0 < n-- ){
        if( e == (p = p->pred)->data)
            return p;
    }
    return NULL;
}
//无序整体查找
template <typename T>
ListNodePosi(T) MyList<T>::find(const T &e)const{
    return find(e, last(), _size);
}
//在p及其n-1个后继中选出最大者
template <typename T>
T MyList<T>::selecMax(ListNodePosi(T) p, int n)const{
    T max = p->data;
    while( 0 < n--){
        if( max < (p = p->succ)->data)
            max = p->data;
    }
    return max;
}
//列表整体最大者
template <typename T>
T MyList<T>::seleMax()const{
    return selecMax(first(), _size);
}
//有序去重
template <typename T>
int MyList<T>::uniquify(){
    if(_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    ListNodePosi(T) q = header;
    while( (p = p->succ) && (q = p->succ) && (trailer ! = p)){
        if(p->data == q->data)
            remove(q);
    }
    return oldSize - _size;
}