#include <iostream>
#include "MyVector.cpp"
#include <ctime>

int main(){
    MyVector<int> DefaultConstructor; //默认构造函数
    MyVector<int> (10);
    for(auto i = 0; i != DefaultConstructor.size(); ++i)
        std::cout << DefaultConstructor[i] << " ";
    
	std::cout << std::endl;
    std::cout << "Time consuming: " << clock();
	return 0;
}