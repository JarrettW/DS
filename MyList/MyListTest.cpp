#include <iostream>
#include <string>
#include <ctime>
#include "MyList.cpp"
using std::string;
//函数指针
template <typename T>
inline void trav(T &e){
    std::cout << e << " ";
}
//函数对象 
template <typename T>
struct Trav{
   void operator()(T &e){
       std::cout << e << " ";
   } 
};

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
    
    MyList<string> S5( { "ok", "yes", "no", "hi", "hi", "no", "see", "zee" });
    S5.show(S5.first());
    //无序查找
    ListNodePosi(string) result = S5.find("yes");
    std::cout << "find: " << *result << std::endl;
    //无序去重
    std::cout << "deduplicate:\n" <<  S5.deduplicate() << std::endl;
    S5.show(S5.first());
    //整体最大者
    std::cout << "selecMax: " << S5.selecMax() << std::endl;
    //排序
    S5.show(S5.first());
    S5.sort();
    S5.show(S5.first());
    //有序去重
    std::cout << "uniquify: " << S5.uniquify() << std::endl;
    S5.show(S5.first());
    //有序查找,小于等于e的元素都可能成为结果
    ListNodePosi(string) Search = S5.search("see");
    std::cout << "search: " << *Search << std::endl;
    //删除位置p的元素
    std::cout << "remove: " << S5.remove(S5.first()) << std::endl;
    S5.show(S5.first());
    //列表整体倒置
    S5.reverse();
    std::cout << "reverse: \n";
    S5.show(S5.first());
    
    //函数指针遍历
    std::cout << "A function pointer to traverse:\n"; 
    S5.traverse(trav);
    //函数对象遍历
    std::cout << "\nA function object to traverse: \n";
    std::cout << "S5:   ";
    S5.traverse(Trav<string>());
    std::cout << "\nS4:   ";
    S4.traverse(Trav<string>());
    //比较操作符
    std::cout << "\ncompare operator:\n";
    std::cout << "==: " << (S5 == S4) << std::endl;
    std::cout << "!=: " <<(S5 != S4) << std::endl;
    std::cout << " >: " <<(S5  > S4) << std::endl;
    std::cout << " <: " <<(S5  < S4) << std::endl;
    std::cout << ">=: " <<(S5 >= S4) << std::endl;
    std::cout << "<=: " <<(S5 <= S4) << std::endl;
    
    MyList<string> S7( { "abc", "cae", "zyx2" });
    MyList<string> S8( { "abc", "cae", "yx3", "s" });
    std::cout << std::endl << (S7 < S8) << std::endl;
    
    std::cout << "\ntime consuming: " << clock();
    return 0;
}