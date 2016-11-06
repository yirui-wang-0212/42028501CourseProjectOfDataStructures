#include<iostream>
#include<stack>
#include<cstring>
#include<queue>
using namespace std;

class Node {

public:

	char opr_= NULL;//操作符
	int opd_ = 0;//操作数
	int pr_ = -2;//优先级,操作数的优先级为-1
	Node* lc_ = NULL;
	Node* rc_ = NULL;

	void setNode(char opr, int pr) {
		opr_ = opr;
		pr_ = pr;
	}

	void setNode(int opd, int pr) {
		opd_ = opd;
		pr_ = pr;
	}

};

typedef Node* pNode;

class BT {
public:

	pNode root_ = NULL;//表达式树的根节点

	void visit(pNode x);//访问并打印打印节点
	void travPre_R(pNode x);//先序遍历
	void travIn_R(pNode x);//后序遍历
	void empty(pNode x);//用于清空二叉树

	~BT() { empty(root_); }
};