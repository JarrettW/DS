#include <iostream>
#include <string>
#include "MyBinTree.cpp"
using std::string;
//函数对象
template <typename T>
class visit{
public:
	void operator()(T &e){
		std::cout << e << " ";
	}
};

int main(){
	BinTree<string> *BT = new BinTree<string>;
	//插入根节点
	BT->insertRoot("ZhuXi");
	std::cout << "_root: ";
	std::cout << BT->root()->data << std::endl;
	std::cout << "_size: " << BT->size() << std::endl;
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	//插入左孩子
	BT->insertAsLC(BT->root(), "FuzhuXi");
	std::cout << BT->root()->lc->data << std::endl;
	std::cout << "_size: " << BT->size() << std::endl;
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	//插入右孩子
	BT->insertAsRC(BT->root(), "Zongli");
	std::cout << BT->root()->rc->data << std::endl;
	std::cout << "_size: " << BT->size() << std::endl;
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	
	//创建一棵树T1
	BinTree<string> *T1 = new BinTree<string>;
	T1->insertRoot("ShiZhang");
	T1->insertAsLC(T1->root(), "QuZhang");
	T1->insertAsRC(T1->root(), "XianZhang");
	//创建一棵树T2
	BinTree<string> *T2 = new BinTree<string>;
	T2->insertRoot("ZhenZhang");
	T2->insertAsLC(T2->root(), "XiangZhang");
	T2->insertAsRC(T2->root(), "CunZhang");
	
	//分别为BT的左右孩子节点下接入子树
	BT->attachAsLC(BT->root()->lc, T1);
	BT->attachAsRC(BT->root()->rc, T2);
	
	std::cout << "height: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	
	//层次遍历
	std::cout << "\ntravLevel: \n";
	BT->travLevel(visit<string>());
	
	//先序遍历
	std::cout << "\ntravPre: \n";
	BT->travPre(visit<string>());
	
	//中序遍历
	std::cout << "\ntravIn: \n";
	BT->travIn(visit<string>());
	
	//后序遍历
	std::cout << "\ntravPost: \n";
	BT->travPost(visit<string>());
	
	//比较器,判等器
	std::cout << "\n\nBT < T2: " << (BT < T2) << std::endl;
	std::cout << "BT >= T2: " << (BT >= T2) << std::endl;
	std::cout << "BT > T2: " << (BT > T2) << std::endl;
	std::cout << "BT <= T2: " << (BT <= T2) << std::endl;
	std::cout << "BT == T2: " << (BT == T2) << std::endl;
	std::cout << "BT != T2: " << (BT != T2) << std::endl;
	
	//删除以位置x处节点为根的子树,返回该子树原先的规模
	std::cout << "\nremove BinNodePosi(T) x, size of x is: "
			<< BT->remove(BT->root()->lc->lc) << std::endl;
	//后序遍历
	std::cout << "\ntravPost: \n";
	BT->travPost(visit<string>());
	std::cout << std::endl;
    std::cout << "\nheight: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	//将子树x从当前树中摘除,并将其转换为一棵独立子树
	BinTree<string>* ST = new BinTree<string>;
	ST = BT->secede(BT->root()->rc);
	std::cout << "secede subtree, the subtree is: ";
	//后序遍历
	std::cout << "\ntravPost: \n";
	BT->travPost(visit<string>());
	
	std::cout << "\nheight: " << BT->updateHeight(BT->root()) << std::endl;
	std::cout << std::endl;
	
	return 0;
}