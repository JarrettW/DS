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
    _elem = new T[2*(hi-lo)];
    //规模清零
    _size = 0;
    //逐元素复制
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>
void MyVector<T>::expand(){
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
    _elem = new T[_capacity = n >> 2];
    _size = n;
    for(size_t i = 0; i != _size; ++i)
        _elem[i] = 0;
}