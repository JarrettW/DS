#include <iostream>
#include "MyVector.cpp"
#include <ctime>

int main(){
    MyVector<int> DefaultConstructor; //默认构造函数
    int a = 10;
    MyVector<int> V1(a);  //初始化为n个0
    for(auto i = 0; i != V1.size(); ++i)
        std::cout << V1[i] << " ";
       
	std::cout << std::endl;
    std::cout << "Time consuming: " << clock();
	return 0;
}