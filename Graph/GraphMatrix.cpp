#include "GraphMatrix.h"
//搜索算法, 逐顶点、逐边的查看并设置状态,达到搜索目的
//BFS算法
template <typename Tv, typename Te>//广度优先搜索BFS算法(全图)
void Graph<Tv, Te>::bfs(int i){   //assert: 0 <= i < n
    reset(); int clock = 0; int v = i; //初始化
    do{
        if(UNDISCOVERED == status(v))  //一旦遇到尚未发现的顶点
            BFS(v, clock); //即从该顶点触发启动一次BFS
    }while( i != ( v = (++v % n))); //按序号检查,故不漏不重
}

template <typename Tv, typename Te> //广度优先搜索BFS算法(单个连通域)
void Graph<Tv, Te>::BFS(int v, int &clock){
    MyQueue<int> Q; //引入辅助队列
    status(v) = DISCOVERED;
    Q.enqueue(v);  //初始化起点
    while(!Q.empty()){  //在Q变空之前,不断
        int v = Q.dequeue(); dTime(v) = ++clock;  //取出队首顶点v
        for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u))  //枚举v的所有邻居
            if(UNDISCOVERED == status(u)){  //尚未被发现,则
                status(u) = DISCOVERED;  //设置为已发现
                Q.enqueue(u);   //并且将该顶点入队
                type(v, u) = TREE;
                parent(u) = v;   //引入树边拓展支撑树
            }else{
                type(v, u) = CROSS; //将(v,u)归类于跨边
            }
        status(v) = VISITED;  //至此,当前节点访问完毕
    }
}
//DFS算法
template <typename Tv, typename Te>//深度优先搜索DFS算法(全图)
void Graph<Tv, Te>::dfs(int s){  //assert: 0 <= s < n
    reset(); int clock = 0; int v = s; //初始化
    do{ //逐一检查所有顶点
        if( UNDISCOVERED == status(v))
            BFS(v, clock);
    }while(s != ( v = (++v) % n ));//按序号检查,故不漏不重
}
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock){   //深度优先搜索DFS算法(单个连通域)
    dTime(v) = ++clock; status(v) = DISCOVERED;  //发现当前顶点v
    for( int u = firstNbr(v); -1 < u; u = nextNbr(v, u) ){  //枚举v的所有邻居u
        switch(status(u)){
            case UNDISCOVERED://u尚未发现,意味着支撑树可在此拓展
                type(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
            case DISCOVERED:  //u已被发现但未访问完毕, 应属被后代指向的祖先
                type(v, u) = BACKWARD; break;
            default: //u已访问完毕(VISITED, 有向图), 则视承袭关系分为前向边或跨边
                type(v, u) = (dTime(v) < dTime(u) ) ? FORWARD : CROSS; break; 
        }
    }
    status(v) = VISITED; fTime(v) = ++clock; //至此,当前顶点v方告访问完毕
}

//基于DFS搜索框架实现拓扑排序算法
template <typename Tv, typename Te>  //基于DFS的拓扑排序算法
MyStack<Tv>* Graph<Tv, Te>::tSort(int s){  //assert: 0 <= s < n
    reset(); int clock = 0; int v = s;
    MyStack<Tv> * S = new MyStack<Tv>;  //用栈记录排序顶点
    do{
        if(UNDISCOVERED == status(v))
            if( !TSort(v, clock, S) ){  //clock并非必需
                while( !S->empty())  //任一连通域(亦即整图) 非DAG
                    S->pop(); break;
            }
    }while(s != ( v = (++v) % n));
    return S;  //若输入为DAG,则s内各顶点自顶向低排序; 否则(不存在拓扑排序), S空
}
template <typename Tv, typename Te>//基于DFS的拓扑排序算法(单趟)
bool Graph<Tv, Te>::TSort(int v, int &clock, MyStack<Tv> *S){  //assert: 0 <= v < n
    dTime(v) = ++clock;
    status(v) = DISCOVERED;  //发现顶点v
    for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u))  //枚举v的所有邻居u
        switch(status(v)){
            case UNDISCOVERED:
                parent(u) = v; type(v, u) = TREE;
                if( !TSort(u, clock, S))  //从顶点u处出发深入搜索
                    return false;  //若u及其后代不能拓扑程序(则全图亦必如此), 故返回并报告
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;  //一旦发现后向边(非DAG), 则
                return false; //不必深入,故返回并报告
            default:   //VISITED(digraphs only)
                type(v, u) = (dTime(v) < dTime(u) ) ? FORWARD : CROSS;
                break;
        }
     status(v) = VISITED; S->push(vertex(v) );  //顶点被标记为VISITED时, 随即入栈
     return true; //v及其后代可以拓扑排序
}

//基于DFS搜索框架实现双连通域分解算法
template <typename Tv, typename Te>  //基于DFS的BCC分解算法
void Graph<Tv, Te>::bcc(int s){ 
    reset(); int clock = 0; int v = s; MyStack<int> S;  //栈s用以记录已访问的顶点
    do{
        if(UNDISCOVERED == status(v) ){  //一旦发现未发现的顶点(新连通分量)
            BCC(v, clock, S);  //即从该顶点触发启动一次BCC
            S.pop(); //遍历返回后,弹出栈中最后一个顶点---当前连通域的起点
        }
    }while( s != (v = ( ++v % n)));
}
#define hca(x) (fTime(x))  //利用此处闲置的fTime[]充当hca[]
template <typename Tv, typename Te>  //顶点类型、边类型
void Graph<Tv, Te>::BCC(int v, int &clock, MyStack<int> &S){  //assert: 0 <= v < n
    hca(v) = dTime(v) = ++clock; status(v) = DISCOVERED; S.push(v); //v被发现并入栈
    for(int u = firstNbr(v); -1 < u; u = nextNbr(v, u))  //枚举v的所有邻居u
        switch(status(u)){  //并视u的状态分别处理
            case UNDISCOVERED:
                parent(u) = v; type(v,u) = TREE; BCC(u, clock, S);  //从顶点u处深入
                if(hca(u) < dTime(v)) //遍历返回后, 若发现u(通过回边)可指向v的真祖先
                    hca(v) = min( hca(v), hca(u) ); //则v亦必如此
                else{  //否则,以v为关节点(u以下即是一个BCC, 且其中顶点此时正集中于栈s的顶部)
                    while( v != S.pop() );  //依次弹出当前BCC中的节点,亦可根据实际需求转存至其他结构
                    S.push(v);  //最后一个顶点(关节点)重新入栈---总计至多两次
                }
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD; //标记(v,u), 并按照"越小越高"的准则
                if( u != parent(v) )
                    hca(v) = min(hca(v), dTime(u));  //更新hca(v)
                break;
            default: //VISITED(digraphs only)
                type(v, u) = (dTime(V) < dTime(u) ? FORWARD : CROSS);
                break;
        }
    status(v) = VISITED;   //对v的访问结束
}
#undef hca

//优先级搜索算法框架
template <typename Tv, typename Te>
template <typename PU>  //优先级搜索(全图)
void Graph<Tv, Te>::pfs(int s, PU prioUpdater){  //assert: 0 <= s < n
    reset(); int v = s;  //初始化
    do{ //逐一检查所有顶点
        if( UNDISCOVERED == status(v))  //一旦遇到尚未发现的节点
            PFS(v, prioUpdater);   //即从该节点出发启动一次PFS
    }while(s != ( v = (++v % n)));  //按序号检查,故不漏不重
}
template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater){  //优先级搜索(单个连通域)
    priority(s) = 0; status(s) = VISITED; parent(s) = -1;  //初始化,起点s加至PFS树中
    while(1){  //将下一顶点和边加至PFS树中
        for(int w = firstNbr(s); -1 < w; w = nextNbr(s, w))  //枚举s的所有邻居w
            prioUpdater(this, s, w); //更新顶点w的优先级及其父顶点
        for(int shortest = INT_MAX, w = 0; w < n; w++)
            if(UNDISCOVERED == status(w))  //从尚未加入遍历树的顶点中
                if(shortest > priority(w)){ //选出下一个
                    shortest = priority(w);
                    s = w;  //优先级最高的顶点s
                }
        if(VISITED == status(s) )
            break;  //直至所有顶点均已加入
        status(s) = VISITED;
        type( parent(s), s ) = TREE;  //将s及与其父的联边加入遍历树
    }
}//通过定义具体的优先级更新策略prioUpdater,即可实现不同的算法功能

//针对Prim算法的顶点优先级更新器
template <typename Tv, typename Te>
struct PrimPU{ 
  virtual void operator() ( GraphMatrix<Tv, Te>* g, int uk, int v){
      if( UNDISCOVERED == g->status(v))  //对于uk每一尚未被发现的邻接顶点v
        if(g->priority(v) > g->weight(uk, v)) {  //按Prim策略做松弛
            g->priority(v) = g->weight(uk, v);  //更新优先级(数)
            g->parent(v) = uk;  //更新父节点
        }
  }  
};

//针对Dijkstra算法的顶点优先级更新器
template <typename Tv, typename Te>
struct DijkstraPU{  
    virtual void operator()( GraphMatrix<Tv, Te>* g, int uk, int v){
        if(UNDISCOVERED == g->status(v) ) //对于uk每一尚未被发现的邻接顶点v,按Dijkstra策略
            if(g->priority(v) > g->priority(uk) + g->weight(uk, v)){  //做松弛
                g->priority(v) = g->priority(uk) + g->weight(uk, v); //更新优先级(数)
                g->parent(v) = uk; //并同时更新父节点
            }
    }
};

// 1.入栈
template <typename T>
void MyStack<T>::push(const T &e){
    insertAsLast(e);
}
// 2.出栈
template <typename T>
T MyStack<T>::pop(){
    return remove(last());
}
// 3.取顶
template <typename T>
T MyStack<T>::top()const {
    return lastElem();
}

//入队,插入队尾
template <typename T>
void MyQueue<T>::enqueue(const T &e){
    insertAsLast(e);
}
//出队
template <typename T>
T MyQueue<T>::dequeue(){
    return remove(first());;
}
//引用队首元素
template <typename T>
T& MyQueue<T>::front()const{
    return first()->data;
}