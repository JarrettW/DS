//基于MyList实现队列数据结构
//队列---先进先出(FIFO)
#include "../MyList/MyList.cpp"
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