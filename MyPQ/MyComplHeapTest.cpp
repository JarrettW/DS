#include <iostream>
#include "MyComplHeap.cpp"

int main(){
    int arr[6] = { 0, 5, 3, 4, 1, 2};
    MyComplHeap<int> MCH(arr, 6);
    MCH.insert(7);
    MCH.show();
    std::cout << "\ngetMax(): " << MCH.getMax() << std::endl;
    std::cout << "delMax(): " << MCH.delMax() << std::endl;
    std::cout << "getMax(): " << MCH.getMax() << std::endl;
    std::cout << "MCH: \n";
    MCH.show();
    std::cout << std::endl;
    MCH.heapSort(0, 6);
    std::cout << "heapSort: \n";
    MCH.show();
    
    return 0;
}