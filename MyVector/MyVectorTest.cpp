#include <iostream>
#include "MyVector.cpp"
#include <ctime>

int main(){
    MyVector<int> DefaultConstructor; //默认构造函数
    const int a = 10;
    MyVector<int> V1(a);  //初始化为a个0
    MyVector<int> V2(a, 6);  //将向量初始化为a个6
    MyVector<int> V3( {11, 12, 13, 14, 15, 16 } ); //列表初始化
    MyVector<int> V4(V2);   //拷贝构造函数
    MyVector<int> V5 = V3;  //拷贝赋值运算符
    MyVector<int> V6(std::move(V1));  //移动构造函数
    MyVector<int> V7 = std::move(V2); //移动赋值运算符
    
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
    
    
    std::cout << "\nAfter the write operation: \n";
    for(auto i = 0; i != V1.size(); ++i)
       std::cout << V1[i] << " ";
    
	std::cout << std::endl;
    std::cout << "Time consuming: " << clock();
	return 0;
}