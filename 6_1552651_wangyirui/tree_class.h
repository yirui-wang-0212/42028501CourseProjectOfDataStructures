#pragma once
#include<iostream>
#include<string>
using namespace std;

typedef struct TreeNode *PtrToNode;

struct  TreeNode{

	string name_;
	PtrToNode firstchild_ = NULL;                                 //第一个孩子
	PtrToNode presibling_ = NULL;                                 //前一个兄弟姐妹
	PtrToNode nextsibling_ = NULL;                                //后一个兄弟姐妹
};

class Tree {
public:
	~Tree();
	PtrToNode Find(string name, PtrToNode t);                     //根据姓名称寻找节点
	void Init(string name);                                       //初始化，加入根节点
	void BuildFamily(string dadname, int sonnum, string *sonname);//完善家庭
	void AddChild(string dadname, string sonname);                //添加家庭成员
	void Remove(string name);                                     //解散局部家庭
	void RecursionForRemove(PtrToNode);                           //用于remove的递归函数
	void Modify(string oldname, string newname);                  //更改家庭成员姓名
	void PrintAncestor();                                         //打印祖先
	void PrintSon(string name);                                   //打印儿子
	void PrintNewName(string oldname, string name);               //打印更改前后的姓名
private:
	PtrToNode root_ = NULL;                                       //祖先
};
