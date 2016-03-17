#ifndef CLIST_H_
#define CLIST_H_
//列表节点模板类指针
#define ListNodePosi(T) ListNode<T>*
template <typename T>
struct ListNode{
	//存储的数据,列表中的元素
	T data;
	//前驱
	ListNodePosi(T) pred;
	//后继
	ListNodePosi(T) succ;
	//默认构造函数
	ListNode(){}   
	//构造函数
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL):data(e), pred(p), succ(s){}
	//在紧靠当前节点之前插入元素e, 返回插入后的节点
	ListNodePosi(T) insertAsPred(const T &e){    
		//1.创建新节点
		ListNodePosi(T) x = new ListNode(e, pred, this);
		pred->succ = x;//当前节点的前驱的后继为x
		pred = x;//改变当前节点的前驱为x,x插在了中间
		return x;
	}
	//在紧靠当前节点之后后插入元素e,返回插入后的节点
	ListNodePosi(T) insertAsSucc(const T &e){     
		ListNodePosi(T) x = new ListNode(e, this, succ);
		succ->pred = x; //改变当前节点的后继的前驱为x节点
		succ = x;  //再将当前节点的后继改为x,就构成了紧靠当前节点之后是x,再之后就是以前的节点后继,x插在了中间
		return x;
	}
};

template <typename T>
class MyList{
public:
	int clear();//返回删除元素的总数
	MyList(){
        init();
    }
	//列表初始化
	MyList(std::initializer_list<T>);  
	//拷贝构造函数
	MyList(const MyList<T>&);  

	//复制列表中自位置p起的n项
	MyList(ListNodePosi(T), int);   
	//析构函数
	~MyList(){
        clear();
        delete header;
        delete trailer;
    }
	//显示数据
	T show(ListNodePosi(T) p){ 
		if( p == NULL)
			return 0;
		return p->data;
	}
	//返回规模
	int size() { return _size;}   
	//判空
	bool empty() { return !_size; }   
	//下标重载---支持循秩访问(效率低)
	T& operator[](int r)const;   
	//首节点位置
	ListNodePosi(T) first()const { return header->succ; }   
	//尾节点位置
	ListNodePosi(T) last()const { return trailer->pred; }   
	//返回首元素
	T firstElem()const { return header->succ->data; }    
	//返回末元素
	T lastElem()const { return trailer->pred->data; }   
	//判断位置p是否对外合法 --- 将头尾节点等同于NULL
	bool valid(ListNodePosi(T) p)const{
		return p && (trailer != p) && (header != p);
	}
	//判断列表是否排序,返回未排序的个数
	int disorder()const;   
	//把e当做首节点插入,返回插入的节点
	ListNodePosi(T) insertAsFirst(const T &e);    
	//把e当做末节点插入
	ListNodePosi(T) insertAsLast(const T &e);   
	//把e当做p的后继插入
	ListNodePosi(T) insertA(ListNodePosi(T) p, const T &e);   
	//把e当做p的前驱插入
	ListNodePosi(T) insertB(ListNodePosi(T) p, const T &e);   
	//无序去重           方法待验证
	int deduplicate();    
	//无序区间查找,找到返回节点,未找到返回NULL,默认从后向前查
	ListNodePosi(T) find(const T &e, ListNodePosi(T) p, int n)const;
	//无序整体查找
	ListNodePosi(T) find(const T &e)const;   
	//在p及其n-1个后继中选出最大者
	T selecMax(ListNodePosi(T), int)const;   
	//整体最大者
	T selecMax()const;   
	//有序去重
	int uniquify();   
	//有序区间查找, 自后向前查找
	ListNodePosi(T) search(const T &e, ListNodePosi(T) p, int n)const;  
	//有序整体查找, 自后向前查找
	ListNodePosi(T) search(const T &e)const;   
	//删除位置p的元素,返回被删除的元素
	T remove(ListNodePosi(T));
	//归并排序---对从p开始连续的n个节点归并排序
	void mergeSort(ListNodePosi(T) p, int n);  //这个函数未实现排序,可能是前半段或后半段的问题
	//全列表归并,即对两个已排序的列表进行归并
	void merge(MyList<T> &L){
		merge(first(), _size, L, L.first(), L.size());
	}
	//列表区间排序
	void sort(ListNodePosi(T), int n);   
	//列表整体排序
	void sort();   
	//整体倒置
	void reverse();   
	//遍历
	//函数指针
	void traverse(void(*) (T&));
	//函数对象
	template <typename VST>
	void traverse(VST &);    
	
protected:
	void init(); //初始化节点函数    
	void copyNode(ListNodePosi(T) p, int n);  //拷贝区间节点   
	//内部排序接口
	void merge(ListNodePosi(T), int n, MyList<T> & L, ListNodePosi(T), int m);
    //节点版本,返回最大值的节点
	ListNodePosi(T) selecMaxPosi(ListNodePosi(T), int n);  
    //选择排序
	void selectionSort(ListNodePosi(T), int);
    //插入排序  
	void insertionSort(ListNodePosi(T), int);
private:
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;
	int _size;
};
#endif