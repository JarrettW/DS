#include <iostream>
#include "MyLeftHeap.cpp"
template <typename T>
struct Visit{
    void operator()(T &e){
        std::cout << e << ' '; 
    }
};

int main(){
    int arr[6] { 23, 45, 12, 53, 54, 12 };
    MyLeftHeap<int> MLH(arr, 6);
    MLH.insert(999);
    /*std::cout << "MLH: \n";
    MLH.travIn( Visit<int>() );
    std::cout << std::endl;
    std::cout << "getMax: " << MLH.getMax() << std::endl;
    std::cout << "delMax: " << MLH.delMax() << std::endl;
    
    std::cout << "MLH: \n";
    MLH.travIn( Visit<int>() );*/
    
    return 0;
}