#include "MyVector.h"
template <typename T>
bool operator< (const MyVector<T> &lhs, const MyVector<T> &rhs){
    for(size_t i = 0; i != lhs.size() && i != rhs.size(); ++i){
        //对两个vector相同下标元素的比较
        if(lhs._elem[i] < rhs._elem[i])
            return true;
    }
    //基于以上比较,元素均相等.仍存在两种可能.若前者规模小于后者,则
    if(lhs.size() < rhs.size())
        return true;  //为真
    //否则后者规模小,返回假
    return false;
}
// 不考虑规模、元素相等,但下标位置不同的情况,否则需将两者分别排序,再对比。
template <typename T>
bool operator==(const Vec<T>& lhs, const Vec<T>& rhs){
	bool flag = false;
    //条件1.规模相等
	if(lhs.size() == rhs.size()){
		flag = true;
        //条件2.两者对应位置的元素相同
		for(auto i = 0; i != lhs.size(); ++i)
			if(lhs._elem[i] != rhs._elem[i])
				return false;
	}
	return flag;
}
template <typename T>
bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs){
	return !(lhs == rhs);
}
template <typename T>
bool operator>=(const MyVector<T> &lhs, const MyVector<T> &rhs){
    return !(lhs < rhs);
}
template <typename T>
bool operator> (const MyVector<T> &lhs, const MyVector<T> &rhs){
    return !(lhs < rhs) && !(lhs != rhs);
}
template <typename T>
bool operator<= (const MyVector<T> &lhs, const MyVector<T> &rhs){
    return !(lhs > rhs);
}
template <typename T>
void MyVector<T>::copyFrom(int * A, int lo, int hi){
    //分配空间,两倍规模的容量
    _elem = new T[(hi-lo) << 1];
    //规模清零
    _size = 0;
    //逐元素复制
    while(lo < hi)
        _elem[_size++] = A[lo++];
}
template <typename T>
void MyVector<T>::expand(){
    //1.重新配置,2.元素移动,3.原空间释放
    //未满员时,不必扩容
    if(_size < _capacity)
        return;
    //不低于原始最小容量
    if(_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    //扩容2倍容量,并将旧元素复制到新的空间
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for(size_t i = 0; i != _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}
template <typename T>
void MyVector<T>::shrink(){
    //不致缩容到原始容量以下
    if(_capacity < DEFAULT_CAPACITY >> 1)
        return;
    //以25%为界
    if(_size << 2 > _capacity)
        return;
    //否则进行缩容操作
    T *oldElem = _elem;
    //重新分配内存空间,容量减半
    _elem = new T[_capacity >>= 1];
    for(size_t i = 0; i != _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}
//将向量初始化为n个0
template <typename T>
MyVector<T>::MyVector(int n){
    _elem = new T[_capacity = n << 1];
    _size = 0;
    while(_size != n)
        _elem[_size++] = 0; //当循环最后退出时_size仍递增了一个数,由于是后置++操作符,所以并没有赋值,而更新为实际规模
}
//向量初始化为n个e
template <typename T>
MyVector<T>::MyVector(int n, T e){
    _elem = new T[_capacity = n << 1];
    _size = 0;
    while(_size != n)
        _elem[_size++] = e;
}
//constructor,将向量初始化为1个e
template <typename T>
MyVector<T>::MyVector(T e){
    _elem[_size++] = e;
    _capacity = DEFAULT_CAPACITY;
}
//initialization_list,列表初始化
template <typename T>
MyVector<T>::MyVector(std::initialization_list<T> li){
    _size = 0;
    auto begin = li.begin(), end = li.end();
    _elem = new T[_capacity = li.size() << 1];
    while(begin != end){
        _elem[_size++] = *begin++;
    }
}
//destructor
template <typename T>
MyVector<T>::~MyVector(){
    delete []_elem;
    //_size = 0;
    //_capacity = DEFAULT_CAPACITY;
}
//copy constructor
template <typename T>
MyVector<T>::MyVector(const MyVector<T> &mv){
    copyFrom(mv._elem, 0, mv.size());
}
//assignment operator
template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T> &mv){
    if(_elem)
        delete []_elem;
    clear();
    _size = mv.size();
    _capacity = mv.capacity();
    copyForm(mv._elem, 0, mv.size());
    return *this;
}
//move constructor
template <typename T>
MyVector<T>::MyVector(MyVector<T> &&mv)noexcept{
    copyForm(std::move(mv._elem), 0, std::move(mv.size())); 
}
//move assignment operator
template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T> &&mv)noexcept{
    if(_elem)
        delete[] _elem;
    clear();
    _size = mv.size();
    _capacity = mv.capacity();
    copyForm(std::move(mv._elem), 0, std::move(mv.size()));
}
