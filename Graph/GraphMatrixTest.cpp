#include <iostream>
#include <string>
#include "GraphMatrix.cpp"
using std::string;

int main(){
    //顶点为城市, 边为城市间距离(公里)
    GraphMatrix<int, int> G;
    //插入五个城市
    //1: BeiJing, 2: QingDao, 3: Shanghai, 4: ShenZhen, 5: ChengDu 
    G.insert(1);
    G.insert(2);
    G.insert(3);
    G.insert(4);
    G.insert(5);
    //北京至青岛的驾车距离669公里
    G.insert(669, 0, 1, 2);
    //查看边(北京, 青岛)的数据
    std::cout << "BeiJing->QingDao: " << G.edge(1, 2) << "KM.\n";
    
    //青岛至上海的驾车距离718公里
    G.insert(718, 0, 2, 3);
    //查看边(青岛, 上海)的数据
    std::cout << "QingDao->ShangHai: " << G.edge(2, 3) << "KM.\n";
    
    //上海至深圳的驾车距离1480公里
    G.insert(1480, 0, 3, 4);
    //查看边(上海, 深圳)的数据
    std::cout << "ShangHai->ShenZhen: " << G.edge(3, 4) << "KM.\n";
    
    //深圳至成都的驾车距离1782公里
    G.insert(1782, 0, 4, 5);
    //查看边(深圳, 成都)的数据
    std::cout << "ShenZhen->ChengDu: " << G.edge(4, 5) << "KM.\n";
    
    //成都至北京的驾车距离1787公里
    G.insert(1787, 0, 5, 1);
    //查看边(成都, 北京)的数据
    std::cout << "ChengDu->BeiJing: " << G.edge(5, 1) << "KM.\n";
    std::cout << "3 status: " << G.status(3) << std::endl;
    G.dfs(3);
    std::cout << "3 status: " << G.status(3) << std::endl;
    G.showV();
    return 0;
}