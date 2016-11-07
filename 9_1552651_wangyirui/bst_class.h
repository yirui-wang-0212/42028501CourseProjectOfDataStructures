#pragma once
#include<iostream>
using namespace std;

#define BinNodePosi BinNode*

//BST节点的结构体
struct BinNode {
	
	BinNode(int data) {

		data_ = data;
		lc = NULL;
		rc = NULL;
	}

	int data_;//关键码
	BinNodePosi lc = NULL;//左儿子
	BinNodePosi rc = NULL;//右儿子
};

class BST {

public:

	//析构函数，通过后序遍历删除节点
	~BST();
	//递归：在子树v中查找关键码e
	BinNodePosi &SearchIn(BinNodePosi &v, const int e, BinNodePosi &hot);
	//通过调用SearchIn算法，实现BST的标准接口Search()
	BinNodePosi &Search(const int e);
	//BST中插入新节点e的过程
	bool Insert(const int e);
	//通过调用BST的后序遍历删除BST中的节点
	void Release();
	//递归：BST的中序遍历（打印节点）
	void TravIn_R(BinNodePosi x);
	//递归：BST的后序遍历（删除节点）
	void TravPost_R(BinNodePosi x);
	//通过调用TravIn_R将BST中的关键码由小到大地打印出来
	void PrintBST();
	//判断BST是否为空
	bool empty() { return !root_; }

private:

	BinNodePosi root_ = NULL;//二叉查找树地根节点
	BinNodePosi hot_ = NULL;//在SearchIn函数中用于存储当前节点
};