#include <iostream>
#include "MyBTree.cpp"

int main(){
    MyBTree<int> Btree;
    std::cout << "Btree size: " << Btree.size() << std::endl;
    std::cout << "Btree order: " << Btree.order() << std::endl;
    std::cout << "Btree empty: " << Btree.empty() << std::endl << std::endl;
    
    Btree.insert(53);
    std::cout << "Btree size: " << Btree.size() << std::endl;
    std::cout << "Btree order: " << Btree.order() << std::endl;
    std::cout << "Btree empty: " << Btree.empty() << std::endl << std::endl;
    
    Btree.insert(36);
    std::cout << "Btree size: " << Btree.size() << std::endl;
    std::cout << "Btree order: " << Btree.order() << std::endl;
    std::cout << "Btree empty: " << Btree.empty() << std::endl << std::endl;
    
    Btree.insert(77);
   
    std::cout << "Btree size: " << Btree.size() << std::endl;
    std::cout << "Btree order: " << Btree.order() << std::endl;
    std::cout << "Btree empty: " << Btree.empty() << std::endl << std::endl;
    return 0;
}