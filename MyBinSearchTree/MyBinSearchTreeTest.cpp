#include <iostream>
#include <time.h>
#include "MyBinSearchTree.cpp"

template <typename T>
class visit{
public:
	void operator()(T &e){
		std::cout << e << " ";
	}
};

int main(){
    std::cout << "\ntime: " << clock() << std::endl;
	MyBinSearchTree<int> *BT = new MyBinSearchTree<int>;
	//插入根节点
	BT->insertRoot(36);
	std::cout << "_root: ";
	std::cout << BT->root()->data << std::endl;
	std::cout << "_size: " << BT->size() << std::endl;
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	//插入左孩子
	BT->insertAsLC(BT->root(), 27);
	std::cout << BT->root()->lc->data << std::endl;
	std::cout << "_size: " << BT->size() << std::endl;
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	//插入右孩子
	BT->insertAsRC(BT->root(), 58);
	std::cout << BT->root()->rc->data << std::endl;
	std::cout << "_size: " << BT->size() << std::endl;
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	
	//创建一棵树T1
	MyBinTree<int> *T1 = new MyBinTree<int>;
	T1->insertRoot(16);
	//创建一棵树T2
	MyBinTree<int> *T2 = new MyBinTree<int>;
	T2->insertRoot(61);
	T2->insertAsLC(T2->root(), 60);
	T2->insertAsRC(T2->root(), 63); 
	
	//分别为BT的左右孩子节点下接入子树
	BT->attachAsLC(BT->root()->lc, T1);
	BT->attachAsRC(BT->root()->rc, T2);
	
	std::cout << "height: " << BT->updateHeight(BT->root()) <<
    "\nsize: " << BT->size() << std::endl;
	std::cout << std::endl;
	//中序遍历
	std::cout << "\ntravIn: \n";
	BT->travIn(visit<int>());
    std::cout << "\n-------------------------------------------------------------------------------\n";
	
    std::cout << "\nsearch: \n";
    BT->insert(62);
    std::cout << "height: " << BT->updateHeight(BT->root()) <<  "\nsize: " << BT->size() <<std::endl;
     
    std::cout << "\nreomve: \n";
    BT->remove(27);
    std::cout << "height: " << BT->updateHeight(BT->root()) <<  "\nsize: " << BT->size() <<std::endl;
    //中序遍历
	std::cout << "\ntravIn: \n";
	BT->travIn(visit<int>());
	std::cout << "\nfinish time: " << clock() << std::endl;
	return 0;
}