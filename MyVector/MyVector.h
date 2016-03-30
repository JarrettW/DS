#ifndef MYVECTOR_H_
#define MYVECTOR_H_
//向量模板类
#define DEFAULT_CAPACITY 3 //默认初始容量
template <typename T>
class MyVector{
    //Friend functions
    //comparison operator
    template <typename T>
    friend bool operator< (const MyVector<T> &lhs, const MyVector<T> &rhs);  
    template <typename T>
    friend bool operator==(const MyVector<T> &lhs, const MyVector<T> &rhs);
    template <typename T>
    friend bool operator!=(const MyVector<T> &lhs, const MyVector<T> &rhs);
    template <typename T>
    friend bool operator> (const MyVector<T> &lhs, const MyVector<T> &rhs);
    template <typename T>
    friend bool operator<=(const MyVector<T> &lhs, const MyVector<T> &rhs);
    template <typename T>
    friend bool operator>=(const MyVector<T> &lhs, const MyVector<T> &rhs);
public:
    //default constructor
    MyVector():_size(0), _capacity(DEFAULT_CAPACITY), _elem(NULL){}
    //constructor,将向量初始化为n个0
    MyVector(int n);
    //constructor,将向量初始化为n个e
    MyVector(int n, const T e);
    //initialization_list,列表初始化
    MyVector(std::initializer_list<T> li);
    //destructor
    ~MyVector(){
        delete[] _elem; //释放内部空间
    }
    //copy constructor
    MyVector(const MyVector<T> &mv);
    //assignment operator
    MyVector<T>& operator=(const MyVector<T> &mv);
    //move constructor
    MyVector(MyVector<T> &&mv)noexcept;
    //move assignment operator
    MyVector<T>& operator=(MyVector<T> &&mv)noexcept;
    //size
    unsigned size()const { return _size; }
    //capacity
    unsigned capacity()const { return _capacity; }
    //judge empty
    bool empty()const { return _size == 0; }
    //重载下标运算符
    T& operator[](int n)const{
        return _elem[n];
    }
    //获取秩为r的元素
    T& get(int r){
        return _elem[r];
    }
    //insert, 默认作为末元素插入,返回元素插入位置
    int insert(const T &e);
    //insert, 将元素e插入秩r,原后继元素依次后移
    int insert(int r, const T &e);
    //find, 无序查找(基于区间查找),返回其秩,失败返回-1
    int find(const T &e)const{
        return find(0, _size, e);
    }
    //sort, 统一排序接口, 随机选择排序方法(整体排序)
    void sort();
    //search, 有序查找(基于区间查找)
    int search(const T &e)const{
        return search(0, _size, e);
    }
    //remove, 删除秩为r的元素(基于区间删除)
    T remove(int r){
        T oldElem = _elem[r];
        remove(r, r + 1);
        return oldElem;
    }
    //删除秩在区间[lo,hi)之内的元素,返回删除元素的个数
    int remove(int lo, int hi);
    //删除所有元素clear
	void clear(){
        remove(0, _size);
    }
    //返回向量中逆序相邻元素对的总数,即判断向量是否已经排序,返回0为有序
    int disordered()const;
    //整体置乱器
    void permute(MyVector<T> &V);
    //对[lo, hi)区间置乱
    void unsort(int lo, int hi);
    //无序去重,返回重复元素的个数
    int deduplicate();
    //有序去重
    int uniquify();
    //遍历(使用函数指针,只读或局部性修改)
    void traverse(void (*visit) (T&)); //参数:visit指向一个函数,该函数的参数是一个T类型的引用,返回值是void类型
    //遍历(使用函数对象, 可全局性修改)
    //函数对象
    template <typename VST>
    void traverse(VST &);
protected:
    //复制数组区间A[lo,hi)
    void copyFrom(T *A, int , int );
    //空间不足时扩容
    void expand();
    //缩容
    void shrink();
    //数值交换
    void swap(T &a, T &b){
        T temp = a;
        a = b;
        b = temp;
    }
    //无序区间查找
    int find(int lo, int hi, const T &e)const;
    //有序区间查找
    int search(int lo, int hi, const T &e)const;
    //二分查找
    int binSearch(int *A, int lo, int hi, const T &e)const;
    //max.选取最大元素,返回其秩
    int max(int lo, int hi);    
    //partition, 轴点构造算法
    int partition(int lo, int hi);
    //区间排序,统一排序接口,随机选择排序方法
    void sort(int lo, int hi);
    //bubble sort
    void bubbleSort(int lo, int hi);
    //selection sort//无序前缀,有序后缀
    void selectionSort(int lo, int hi);
    //merge sort
    void mergeSort(int lo, int hi);
    void merge(int lo, int mi, int hi);
    //quick sort,快排
    void quickSort(int lo, int hi);
protected:
  T *_elem;
  unsigned _size;
  unsigned _capacity;
};
#endif