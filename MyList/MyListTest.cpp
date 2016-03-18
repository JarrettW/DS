#include <iostream>
#include <string>
#include <ctime>
#include "MyList.cpp"
using std::string;
int main(){
    MyList<string> S1;  //默认构造函数
    std::cout << "size: " << S1.size() << std::endl;
    std::cout << "empty: " << S1.empty() << std::endl;
    MyList<string> S2( { "You", "become", "what", "you", "believe!" });  //列表初始化
    S2.show(S2.first());
    
    //复制列表中自位置p起的n项
    MyList<string> S3(S2.first(), S2.size());
    S3.show(S3.first());
    std::cout << "S3 size: " << S3.size() << std::endl;
    
    //拷贝构造函数
    MyList<string> S4(S2);
    S4.show(S4.first());
    std::cout << "S4 size: " << S4.size() << std::endl;
    
    //清空列表,返回删除元素的总数
    std::cout << "\nclear(): " << S2.clear() << std::endl;
    
    //下标循秩访问(效率低)
    for(auto i = 0; i != S3.size(); ++i)
        std::cout << S3[i] << " ";
    
    //S4首元素与末元素
    std::cout << "\nS4 first element: " << S4.firstElem() << " --- S4 last element: " << S4.lastElem() << std::endl;
    
    //重载 << 操作符
    std::cout << "S4 data: " << S4 << std::endl;
    
    //判断列表是否排序,返回未排序的个数
    std::cout << "disorder: " << S4.disorder() << std::endl;
    
    //把e当做首节点插入
    S4.insertAsFirst("Hello!");
    //把e当做末节点插入
    S4.insertAsLast("Yes~");
    //把e当做p的后继插入
    S4.insertA(S4.first(), "insert-succ");
    //把e当做p的前驱插入
    S4.insertB(S4.last(), "insert-succ");
    S4.show(S4.first());
    
    
    std::cout << "\ntime consuming: " << clock();
    return 0;
}