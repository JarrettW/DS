#include <iostream>
#include "MyVector.cpp"
#include <ctime>
#include <string>
//函数指针
// template <typename T>
void Fun(int &e){
    std::cout << e << " ";
}
//函数对象
template <typename T>
struct Visit{
  void operator()(T &e){
      std::cout << e << " ";
  }
};
 
int main(){
    MyVector<int> DefaultConstructor; //默认构造函数
    const int a = 10;
    MyVector<int> V1(a);  //初始化为a个0
    MyVector<int> V2(a, 6);  //将向量初始化为a个6
    MyVector<int> V3( {211, 12, 143, 14, 615, 16 } ); //列表初始化
    MyVector<int> V4(V2);   //拷贝构造函数
    MyVector<int> V5 = V3;  //拷贝赋值运算符
    V5.insert(12);
    V5.insert(16);
    V5.insert(211);
    MyVector<int> V6(std::move(V1));  //移动构造函数
    MyVector<int> V7 = std::move(V2); //移动赋值运算符
    MyVector<int> V8( {3, 6, 3, 4, 7, 7, 11, 15, 11, 7} );
    
    //比较操作
    std::cout << (V1 < V2) << std::endl;
    std::cout << (V2 > V3) << std::endl;
    std::cout << (V3 == V4) << std::endl;
    std::cout << (V4 != V5) << std::endl;
    std::cout << (V5 >= V6) << std::endl;
    std::cout << (V6 <= V7) << std::endl;
    
    std::cout << "Before the write operation: \n";
    for(auto i = 0; i != V1.size(); ++i)
       std::cout << V1[i] << " ";
    //容量
    std::cout << "\ncapacity: " << V1.capacity() << std::endl;
    //规模
    std::cout << "size: " << V1.size() << std::endl;
    //判空
    std::cout << "empty: " << V1.empty() << std::endl;
    //作为末元素插入
    V1.insert(33);
    //获取秩为r的元素
    std::cout << "_elem[5] : " << V1.get(5) << std::endl;
    //无序查找
    std::cout << "find? : " << V1.find(2) << std::endl;
    //排序V3
    V3.sort();
    std::cout << "\nAfter the write operation: \n";
    for(auto i = 0; i != V3.size(); ++i)
       std::cout << V3[i] << " ";
    //有序区间查找
    std::cout << "\nsearch 16: " << V3.search(16) << std::endl;
    //删除秩为r的元素,返回被删除的元素
    std::cout << "remove _elem[4]: \n";
    std::cout << V2.remove(4) << std::endl;
    //删除所有元素
    std::cout << "clear: \n";
    V2.clear();
    std::cout << "size: " << V2.size() << std::endl;
    std::cout << "capacity: " << V2.capacity() << std::endl;
    std::cout << "V5: \n";
    for(auto i = 0; i != V5.size(); ++i)
       std::cout << V5[i] << " ";

    //返回向量中逆序相邻元素对的总数,即判断向量是否已经排序,返回0为有序
    std::cout << "\nbackward sequence: " << V5.disordered() << std::endl;
    //对V3区间置乱
    V3.unsort(V3.size() - 5, V3.size());
    for(auto i = 0; i != V3.size(); ++i)
       std::cout << V3[i] << " ";
    std::cout << std::endl;
    //对V3整体置乱
    V3.permute(V3);
    for(auto i = 0; i != V3.size(); ++i)
       std::cout << V3[i] << " ";
    std::cout << std::endl;
    
    std::cout << "V8: \n";
    for(auto i = 0; i != V8.size(); ++i)
        std::cout << V8[i] << " ";
    //无序去重,返回重复元素的个数
    std::cout << "\nThe number of repeating elements: " << V8.deduplicate() << std::endl;
    std::cout << "V8: \n";
    for(auto i = 0; i != V8.size(); ++i)
        std::cout << V8[i] << " ";
    std::cout << std::endl;
    V5.sort();
    for(auto i = 0; i != V5.size(); ++i)
        std::cout << V5[i] << " ";
    //有序去重
    std::cout << "\nThe number of repeating elements : " << V5.uniquify();
    std::cout << std::endl;
    for(auto i = 0; i != V5.size(); ++i)
        std::cout << V5[i] << " ";
    
    std::cout << std::endl;
    //函数指针
    MyVector<int> V10;
    for(auto i =10; i != 0; --i)
        V10.insert(i);
    V10.traverse(Fun);
    
    std::cout << std::endl;
    //函数对象
    MyVector<std::string> V9( {"This", "is", "programing", "test!"});
    V9.traverse( Visit<std::string> () );
     
   	std::cout << std::endl;
    std::cout << "Time consuming: " << clock();
	return 0;
}