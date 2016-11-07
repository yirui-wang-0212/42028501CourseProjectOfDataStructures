#include<string>
#include"bst_class.h"

int main() {

	cout << "\n**               二叉排序树               **"
		<< "\n============================================"
		<< "\n**             1 --- 建立二叉排序树       **"
		<< "\n               2 --- 插入元素             **"
		<< "\n               3 --- 查询元素             **"
		<< "\n               4 --- 退出程序             **"
		<< "\n============================================"
		<< endl;

	BST bst;

	while (true) {

		string operate;
		int num;

		cout << "\n\nPlease select: " << flush;
		cin >> operate;

		//若用户输入1，开始建立二叉排序树
		if (operate == "1") {

			cout << "Please input key to create Bsort_Tree:" << endl;
			while (cin >> num && num) {

				bool flag = bst.Insert(num);

				if (!flag)
					cout << "The input key<" << num << ">is have in" << endl;
			}
			cout << "Bsort_Tree is:" << endl;
			if (bst.empty())
				cout << "The Bsort_Tree is empty!" << endl;
			else
				bst.PrintBST();
		}
		
		//若用户输入2，开始插入元素
		else if (operate == "2") {

			cout << "Please input key which inserted: " << flush;
			cin >> num;

			bool flag = bst.Insert(num);

			if (!flag)
				cout << "The input key<" << num << ">is have in" << endl;

			cout << "Bsort_Tree is:" << endl;
			if (bst.empty())
				cout << "The Bsort_Tree is empty!" << endl;
			else
				bst.PrintBST();
		}

		//若用户输入3，开始查询元素
		else if (operate == "3") {

			cout << "Please input key which searched: " << flush;
			cin >> num;

			bool flag = bst.Search(num);
			if (flag)
				cout << "search success!" << endl;
			else
				cout << num << " not exist!" << endl;
		}

		//若用户输入4，跳出循环，退出程序
		else if (operate == "4")
			break;

		else
			cout << "您输入的操作代码非法，请重新输入！" << endl;
	}
	return 0;
}