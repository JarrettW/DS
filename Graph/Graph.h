#ifndef GRAPH_H_
#define GRAPH_H_
#include "../MyList/MyList.cpp"

//辅助数据结构MyStack和MyQueue
template <typename T>
class MyStack: public MyList<T>{
public:
    //默认构造函数 
    MyStack(){}
    //入栈,仅支持在尾元素插入
    void push(const T &e);
    //出栈,仅支持删除尾元素
    T pop();
    //取顶,返回最顶端元素,不删除
    T top()const;
};
template <typename T>
class MyQueue: public MyList<T>{
public:
  //入队,插入队尾
  void enqueue(const T&e);
  //出队
  T dequeue();
  //引用队首元素
  T& front()const;
};

/***********************************************了解, Graph***********************************************/


/***Graph模板类---图ADT操作接口, 纯虚函数***/
//顶点状态
typedef enum{ UNDISCOVERED, DISCOVERED, VISITED } VStatus; // vertex status { 未发现, 已发现, 已访问}
//边(在遍历树中所属的)类型
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType; // edge type { 未确定, 树边, 跨边, 前向边, 后向边}

template <typename Tv, typename Te>  //顶点类型、边类型
class Graph{
private:
	void reset(){  //所有顶点、边的辅助信息复位
		for(int i = 0; i < n; i++){  //所有顶点的
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;  //状态、时间标签
			parent(i) = -1;
			priority(i) = INT_MAX; //(在遍历树中的)父节点, 优先级数
			for(int j = 0; j < n; j++) //所有边的
				if( exists(i, j))
					type(i, j) = UNDETERMINED;  //(边的)类型
		}
	}
	void BFS(int, int &); //(连通域)广度优先搜索算法
	void DFS(int, int &); //(连通域)深度优先搜索算法
	void BCC(int, int &, MyStack<int> & ); //(连通域)基于DFS的双连通分量分解算法
	bool TSort(int m, int &, MyStack<Tv>* ); //(连通域)基于DFS的拓扑排序算法
	template <typename PU>
	void PFS(int, PU); //(连通域)优先级搜索框架
public:
    // i = index; j 亦为下标; w = weight权重
//顶点
	int n; //顶点数
	virtual int insert(const Tv &e) = 0;  //插入节点,返回编号
	virtual Tv remove(int i) = 0; //删除顶点及其关联边,返回该顶点信息
	virtual Tv& vertex(int i) = 0; //顶点v的数据(该顶点的确存在)
	virtual int inDegree(int i) = 0 ; //顶点v的入度(该顶点的确存在)
	virtual int outDegree(int i) = 0; //顶点v的出度(该顶点的确存在)
	virtual int firstNbr(int i) = 0; //顶点v的首个邻接顶点
	virtual int nextNbr(int i, int j) = 0; //顶点v的(相对于顶点j的)下一邻接顶点
	virtual VStatus& status(int i) = 0; //顶点v的状态
	virtual int& dTime(int i) = 0; //顶点v的时间标签dTime
	virtual int& fTime(int i) = 0; //顶点v的时间标签fTime
	virtual int& parent(int i)  = 0; //顶点v在遍历树中的父亲
	virtual int& priority(int i) = 0 ; //顶点v在遍历树中的优先级数
//边:
	//这里约定,无向边均统一转化为方向互逆的一对有向边,从而将无向图视作有向图的特例
	int e; //边总数
	virtual bool exists(int i, int j)  = 0; //边(i, j)是否存在
	virtual void insert(const Te &e, int w, int i, int j) = 0 ; //在顶点v和u之间插入权重为w的边e
	virtual Te remove(int i, int j) = 0 ; //删除顶点v和u之间的边e,返回改边信息
	virtual EType &type(int i, int j) = 0 ; //边(i, j)的类型
	virtual Te &edge(int i, int j) = 0; //边(i, j)的数据(该边的确存在)
	virtual int &weight(int i, int j)  = 0; //边(i, j)的权重
//算法:
	void bfs(int i); //广度优先搜索算法
	void dfs(int i); //深度优先搜索算法
	void bcc(int i); //基于DFS的双连通分量分解算法
	MyStack<Tv>* tSort(int i); //基于DFS的拓扑排序算法
	//void prim(int i); //最小支撑树Prim算法
	//void dijkstra(int i); //最短路径Dijkstra算法
	template <typename PU>
	void pfs(int i, PU); //优先级搜索框架, PU = prioUpdater
};
#endif