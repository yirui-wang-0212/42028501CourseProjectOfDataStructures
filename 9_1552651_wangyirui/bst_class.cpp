#include<string>
#include"bst_class.h"

//析构函数，通过后序遍历删除节点
BST::~BST() {

	Release();
}

//递归：在子树v中查找关键码e
BinNodePosi &BST::SearchIn(BinNodePosi &v, const int e, BinNodePosi &hot) {

	//递归基：当节点为空或在节点中查找到关键码
	if (!v || (e == v->data_))
		return v;//当在二叉查找树中未查找到关键码时返回的是一个空指针

	hot = v;//一般情况：先记下当前节点

	//递归查找
	return SearchIn(((e < v->data_) ? v->lc : v->rc), e, hot);
}

//通过调用SearchIn算法，实现二叉查找树的标准接口Search()
//在二叉查找树中查找关键码e
BinNodePosi &BST::Search(const int e) {

	//返回目标节点的引用
	return SearchIn(root_, e, hot_=NULL);
}

//二叉查找树中插入新节点e的过程
bool BST::Insert(const int e) {

	//若不存在根节点，则将此节点作为根节点
	if (!root_) {
		auto root = new BinNode(e);
		root_ = root;
		return true;
	}

	//查找关键码e是否存在
	auto x = Search(e);
	//若存在，插入失败，返回
	if (x)
		return false;

	//若不存在，创造节点e
	x = new BinNode(e);

	//将节点e插入二叉查找树
	if (e < hot_->data_)
		hot_->lc = x;
	else
		hot_->rc = x;
	
	return true;//返回插入成功
}

void BST::Release() {

	if (root_)
		TravPost_R(root_);
	return;
}

//递归：二叉查找树的中序遍历(打印节点)
void BST::TravIn_R(BinNodePosi x) {

	if (!x)
		return;

	TravIn_R(x->lc);
	cout << x->data_ << "->";
	TravIn_R(x->rc);
	return;
}

//递归：BST的后序遍历（删除节点）
void BST::TravPost_R(BinNodePosi x) {

	if (!x)
		return;

	TravPost_R(x->lc);
	TravPost_R(x->rc);
	delete x;
	return;
}

//通过调用TravIn_R将二叉查找树中的关键码由小到大地打印出来
void BST::PrintBST() {

	TravIn_R(root_);
	return;
}