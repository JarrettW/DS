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
        insertAsLast(p->data); //把e当作末节点插入
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
MyList<T>::MyList(const MyList<T>& ml){
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
    while(p != trailer){
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
T MyList<T>::selecMax()const{
    return selecMax(first(), _size);
}
//有序去重
template <typename T>
int MyList<T>::uniquify(){
    if(_szie < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    ListNodePosi(T) q = header;
    while( (p = p->succ) && (q = p->succ) && (trailer != p)){
        if(p->data == q->data)
            remove(q);
    }
    return oldSize - _size;
}
//有序区间查找,自后向前查找
template <typename T>
ListNodePosi(T) MyList<T>::search(const T &e, ListNodePosi(T) p, int n)const{
    while(0 <= n--){
        if( (p = p->pred)->data <= e)
            break;
    }
    return p; //因为是有序的,所以自后向前返回的应该是等于e或不大于e的最大元素
}
//有序整体查找,自后向前查找
template <typename T>
ListNodePosi(T) MyList<T>::search(const T &e)const{
    return search(e, last(), _size);
}
//删除位置p的元素,返回被删除的元素
template <typename T>
T MyList<T>::remove(ListNodePosi(T) p){
    T oldElem = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;   //经过两步链接,将p隔离,并
    delete p;   //删除
    _size--;
    return oldElem;
}
//protected,归并排序,二路归并算法(输入为两个已排序的列表,对它们归并)
template <typename T>
void MyList<T>::merge(ListNodePosi(T) p, int n, MyList<T> &L, ListNodePosi(T) q, int m){
    ListNodePosi(T) pp = p->pred;
    while(0 < m)
        if( (0 < n) && (p->data <= q->data)){
            if(q == (p = p->succ))
                break;
            n--;
        }else{
            insertB(p, L.remove(( q = q->succ)->pred));
            m--;
        }
    p = pp->succ;
}
//public, 归并排序
template <typename T>
void MyList<T>::mergeSort(ListNodePosi(T) p, int n){
    if(n < 2) return;
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for(int i = 0; i < m; i++)
        q = q->succ;  //q为后半段
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m); //二路归并
}
//选择排序, 前缀无序,后缀有序
template <typename T>
void MyList<T>::selectionSort(ListNodePosi(T) p, int n){
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) trail = p;
    //定位到最后的节点位置
    for(auto i = 0; i != n; ++i)
        trail = trail->succ;
    while(1 < n){
        ListNodePosi(T) max = selecMaxPosi(p, n);
        if(trail->pred != max)
            insertB(trail, remove(max));
        trail = trail->pred;
        n--;
    }
}
//返回最大值的节点
template <typename T>
ListNodePosi(T) MyList<T>::selecMaxPosi(ListNodePosi(T) p, int n){
    ListNodePosi(T) max = p;
    //自前向后
    while(0 < n--){
        if((p = p->succ)->data >= max->data)
            max = p;
    }
    return max;
}
//插入排序,前缀有序,后缀无序
template <typename T>
void MyList<T>::insertionSort(ListNodePosi(T) p, int n){
    for(auto r = 0; r < n; r++){
        //搜索不大于p->data的节点,将p->data插入其前驱
        insertA( search(p->data, p, r), p->data);
        p = p->succ;
        remove(p->pred);
    }
}
//列表区间排序
template <typename T>
void MyList<T>::sort(ListNodePosi(T) p, int n){
    switch(rand() %3){
        case 1: mergeSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: insertionSort(p, n); break;
    }
}
//列表整体排序
template <typename T>
void MyList<T>::sort(){
    sort(first(), _size);
}
//整体倒置
template <typename T>
void MyList<T>::reverse(){
    ListNodePosi(T) p = header;
    ListNodePosi(T) q = trailer;
    for(auto i = 0; i != _size; i += 2)//从首末节点开始,由内而外捉对的
        std::swap( (p = p->succ)->data, (q = q->pred)->data) ;//交换对称节点的数据项, 指针节点并不需要改变,指示交换T类型数据
}
//遍历,函数指针
template <typename T>
void MyList<T>::traverse(void (*visit) (T &)){
	for(ListNodePosi(T) p = header->succ; p != trailer; p=p->succ)
		visit(p->data);
}
//函数对象
template <typename T>
template <typename VST>
void MyList<T>::traverse(VST& visit){
	for(auto p = header->succ; p != trailer; p=p->succ)
		visit(p->data);
}
//MyList重载输出操作符,友元函数
template <typename T>
std::ostream& operator<<(std::ostream & os, const MyList<T> &obj){
    ListNodePosi(T) p = obj.first();
    while(p != obj.last()->succ){
            os << p->data << " ";
            p = p->succ;
        }
    return os;
}
//ListNode重载输出操作符,友元函数,为配合*解引用操作符输出
template <typename T>
std::ostream& operator<<(std::ostream & os, const ListNode<T> &p){
    const ListNodePosi(T) q = &p; //传地址,转换为指针
    os << q->data;  //取值并输出
    return os;
}