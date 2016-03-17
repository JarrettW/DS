#include <iostream>
#include <string>
#include "MyList.cpp"
using std::string;
int main(){
    MyList<string> S1;  //默认构造函数
    std::cout << "size: " << S1.size() << std::endl;
    std::cout << "empty: " << S1.empty() << std::endl;
    MyList<string> S2( { "You", "become", "what", "you", "believe!" });  //列表初始化
    S2.show(S2.first());
    MyList<string> S3(S2);
    S2.show(S2.last());
    return 0;
}