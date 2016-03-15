#include "MyVector.h"
#include <initializer_list>
//重载比较操作符
template <typename T>
bool operator< (const MyVector<T> &lhs, const MyVector<T> &rhs){
    for(size_t i = 0; i != lhs.size() && i != rhs.size(); ++i){
        //对两个MyVector相同下标元素的比较
        if(lhs._elem[i] < rhs._elem[i])
            return true;
        //若后者大于前者,直接返回假
        if(lhs._elem[i] > rhs._elem[i])
            return false;
    }
    //基于以上比较,元素均相等.仍存在两种可能.若前者规模小于后者,则
    if(lhs.size() < rhs.size())
        return true;  //为真
    //否则后者规模小,返回假
    return false;
}
// 不考虑规模、元素相等,但下标位置不同的情况,否则需将两者分别排序,再对比。
template <typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs){
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
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs){
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
//数组整体复制
template <typename T>
void MyVector<T>::copyFrom(T * A, int lo, int hi){
    //分配空间,两倍规模的容量
    _elem = new T[_capacity = (hi-lo) << 1];
    //规模清零
    _size = 0;
    //逐元素复制
    while(lo < hi)
        _elem[_size++] = A[lo++];
}
//扩容
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
//缩容
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
//initialization_list,列表初始化
template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> li){
    _size = 0;
    auto begin = li.begin(), end = li.end();
    _elem = new T[_capacity = li.size() << 1];
    while(begin != end){
        _elem[_size++] = *begin++;
    }
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
    copyFrom(std::move(mv._elem), 0, std::move(mv.size())); 
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
template <typename T>
//将元素e插入秩r,原后继元素依次后移
int MyVector<T>::insert(int r, const T &e){
    if(_size == 0){
        _size++;
        _elem = new T[DEFAULT_CAPACITY];
        _elem[0] = e;
        _capacity = DEFAULT_CAPACITY;
        return _size;
    }
    //检查是否需要扩容
    expand();
    int i = _size;
    while(i-- != r){
        _elem[i] = _elem[i-1];
    }
    _elem[r] = e;
    ++_size;
    return r;
}
template <typename T>
//默认作为末元素插入,返回元素插入位置
int MyVector<T>::insert(const T &e){
    return insert(_size, e);
}
//删除秩在区间[lo,hi)之内的元素, 返回删除元素的个数
template <typename T>
int MyVector<T>::remove(int lo, int hi){
    //退化情况
    if(lo == hi)
        return 0;
    while( hi != _size){  //确保hi不大于规模
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}
template <typename T>
//无序区间查找
int MyVector<T>::find(int lo, int hi, const T &e)const{
    //自后向前依次查找
    while(lo < hi--){
        if(_elem[hi] == e)
            return hi;
    }
    //至此肯定未查找到给定元素
    return -1;
}
template <typename T>
//sort, 整体排序
void MyVector<T>::sort(){
    //调用保护成员方法
    sort(0, _size);
}
template <typename T>
//区间排序,统一排序接口,随机选择排序方法
void MyVector<T>::sort(int lo, int hi){
    switch(rand() % 4){
        case 1:bubbleSort(lo, hi); break;
        case 2:selectionSort(lo, hi); break;
        case 3:mergeSort(lo, hi); break;
        default: quickSort(lo, hi); break;
    }
}  
template <typename T>
//bubbleSort
void MyVector<T>::bubbleSort(int lo, int hi){
    //排序区间
    int n = hi - lo;
    //排序标记,初始化假设未排序
    bool flag = false;
    //外层循环,整体扫描
    while(!flag){
        //假设已排序
        flag = true;
        //内层循环,单趟扫描交换
        for(auto i = 1; i != n; ++i){
            if(_elem[i] < _elem[i-1])
                swap(_elem[i], _elem[i-1]);
             //排序未完成
             flag = false;
        }
        --n;
    }
}
//返回最大值的秩
template <typename T>
int MyVector<T>::max(int lo, int hi){
    int mx = hi;
    while(lo < hi--)
        if(_elem[hi] > _elem[mx])
            mx = hi;
    return mx;
}
//selection sort
template <typename T>
void MyVector<T>::selectionSort(int lo, int hi){
    while(lo < --hi){
        swap(_elem[hi], _elem[max(lo, hi)]);
    }
}
//merge sort
template <typename T>
void MyVector<T>::mergeSort(int lo, int hi){
    if(hi-lo < 2) return;
    int mi = (hi + lo) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}
template <typename T>
void MyVector<T>::merge(int lo, int mi, int hi){
    T *A = _elem + lo; //合并后的向量A[0, hi-lo] = _elem[lo, hi]
	int lb = mi-lo; T *B = new T[lb];//前子向量B[0,lb]=_elem[lo,mi]
	for(int i = 0; i<lb; B[i] = A[i++]); //复制前子向量
	
	int lc = hi-mi; T *C = _elem+mi; //后子向量C[0,lc]=_elem[mi,hi)
	for(int i=0, j=0, k=0; (j<lb) || (k<lc); ){//B[j]和C[k]中的小者续至末尾
		if( (j<lb) && (! (k<lc) || (B[j] <= C[k] )))
			A[i++] = B[j++];
		if( (k<lc) && (! (j<lb) || (C[k] < B[j] )))
			A[i++] = C[k++];
	}
	delete[] B;
}//归并后得到完整的有序向量[lo,hi);
//快排
template <typename T>
void MyVector<T>::quickSort(int lo, int hi){
    //单元素自然有序
    if(hi - lo < 2) return;
    //构造轴点
    int mi = partition(lo, hi);
    //递归对前子向量排序
    quickSort(lo, mi);
    //递归对后子向量排序
    quickSort(mi + 1, hi);
}
//轴点构造
template <typename T>
int MyVector<T>::partition(int lo, int hi){
    //任选一元素并与首元素交换
    swap(_elem[lo], _elem[ lo + rand() % (hi-lo+1) ]);
    T pivot = _elem[lo]; //以随机选取的首元素为轴点
    //从向量的两端交替的向中间扫描
    while(lo < hi){
        while(lo < hi)
            if(pivot < _elem[hi]) //在大于轴点的情况下
                hi--;  //向左拓展
            else{  //一旦小于等于轴点
                _elem[lo++] = _elem[hi]; //将其归入左端子向量
                break; 
            }
        while(lo < hi)
            if(_elem[lo] < pivot) //在小于轴点的情况下
                lo++; //向右拓展
            else{  //一旦大于等于轴点
                _elem[hi--] = _elem[lo]; //将其归入右端子向量
                break;
            }
    }
    _elem[lo] = pivot; //将备份的轴点放在前后子向量之间
    return lo; //返回轴点的秩
}
//有序区间查找
template <typename T>
int MyVector<T>::search(int lo, int hi, const T &e)const{
    return binSearch(_elem, lo, hi, e);
}
//二分查找
template <typename T>
int MyVector<T>::binSearch(int *A, int lo, int hi, const T &e)const{
    while(lo < hi){
        int mi = (hi + lo) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}
//整体置乱
template <typename T>
void MyVector<T>::permute(MyVector<T> &V){
    for(auto i = V.size(); i != 0; i--) //自后向前
        swap(V[i - 1], V[rand() % i]); //将V[i-1]与V[0,i]中某一随机元素交换
}
//区间置乱
template <typename T>
void MyVector<T>::unsort(int lo, int hi){
    T *V = _elem + lo; //将子向量_elem[lo, hi]视作另一向量V[0, hi-lo]
    for(auto i = hi-lo; i != 0; i--) //自后向前
        swap(V[i - 1], V[rand() % i]); //随机交换元素
}
//判断向量是否已排序,返回重复元素的个数
template <typename T>
int MyVector<T>::disordered() const{
    int count = 0; //计数器
    for(auto i = 1; i != _size; ++i){
        if(_elem[i] < _elem[i - 1]) //如果后一个元素小于前一个元素
            ++count;
    }
    return count;
}
//无序去重,返回重复元素的个数
template <typename T>
int MyVector<T>::deduplocate(){
    int oldSize = _size;
    int i = 1;
    while(i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}
//有序去重,返回重复元素的个数
template <typename T>
int MyVector<T>::uniquify(){
    int i = 0, j = 0;
    while(++j < _size)
        if(_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}
//遍历(使用函数指针,只读或局部性修改)
template <typename T>
void traverse(void (* ) (T & visit)){
   for(auto i = 0; i != _size; ++i)
        visit(_elem[i]);
}
//遍历(使用函数对象,可全局性修改)
template <typename T>
template <typename VST>
void MyVector<T>::traverse(VST &visit){
    for(auto i = 0; i != _size; ++i)
        visit(_elem[i]);
}