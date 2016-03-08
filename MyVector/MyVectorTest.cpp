#include <iostream>
#include "Vec.cpp"
#include <string>
#include <time.h>
int main(){
	Vec<int> V;
	Vec<int> V2;
    
	V.insert(13);
    V.insert(1119);
    V.insert(2113);
    V.insert(2513);
    V.insert(9913);
    V.insert(11113);
    
    V2.insert(1313);
    V2.insert(2219);
    V2.insert(3213);
    V2.insert(3513);
    V2.insert(4414);
    V2.insert(5163);
    V2.insert(3513);
    V2.insert(4414);
    V2.insert(5163);
 
    //int maj = 131;
    //std::cout << "\nmajority: " << V.majority(V, maj) << std::endl;
    //std::cout << std::endl << V[V.size() / 2];
	// std::cout << V[V.min(0, V.size()-1)] << std::endl;
    
    V.trivialMedian(V, 0, V.size(), V2, 0, V2.size() );
    //两个等长向量
    //std::cout << "\n" << V.median(V, 0, V2, 0, V.size() );
    //两个不等长向量
    std::cout << "\n" << V.median2(V, 0, V.size(), V2, 0, V2.size());
    // std::cout << "\nmedian: " << V.trivialMedian(V, 0, V.size(), V2, 0, V2.size() ) << std::endl;
    
	std::cout << std::endl;
    std::cout << "Time: " << clock() << std::endl;
	return 0;
}