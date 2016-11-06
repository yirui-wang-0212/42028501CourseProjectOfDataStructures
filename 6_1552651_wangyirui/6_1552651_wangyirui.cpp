#include"tree_class.h"
#include<vector>

int main() {

	Tree tree;

	string ancestorname, operate;
	printf("\n**               家谱管理系统              **\n");
	printf("=============================================\n");
	printf("**            请选择要执行的操作           **\n");
	printf("**              A---完善家谱               **\n");
	printf("**              B---添加家庭成员           **\n");
	printf("**              C---解散局部家庭           **\n");
	printf("**              D---更改家庭成员姓名       **\n");
	printf("**              E---退出程序               **\n");
	printf("=============================================\n");
	printf("首先建立一个家谱！\n请输入祖先的姓名：");
	cin >> ancestorname;
	tree.Init(ancestorname);

	while (true) {

		printf("\n请选择要执行的操作：");
		cin >> operate;

		if (operate == "A") {
			string dadname, sonname;
			int sonnum;
			vector<string> sonnames;
			printf("请输入要建立家庭的人的姓名：");
			cin >> dadname;
			while (true) {
				cout << "请输入" << dadname << "的儿女人数：";
				scanf("%d", &sonnum);
				if (sonnum > 0)
					break;
				printf("输入的数字非法，请重新输入！：\n");
			}
			cout << "请依次输入" << dadname << "的儿女的姓名：";
			for (int i = 0; i < sonnum; ++i) {
				cin >> sonname;
				sonnames.push_back(sonname);
			}
			tree.BuildFamily(dadname, sonnum, &sonnames[0]);
			tree.PrintSon(dadname);
		}
		else if (operate == "B") {
			string dadname, sonname;
			printf("请输入要添加儿子(或女儿)的人的姓名：");
			cin >> dadname;
			cout << "请输入" << dadname << "新添加儿子(或女儿)的姓名：";
			cin >> sonname;
			tree.AddChild(dadname, sonname);
			tree.PrintSon(dadname);
		}
		else if (operate == "C") {
			string dadname;
			printf("请输入要解散家庭的人的姓名：");
			cin >> dadname;
			cout << "要解散家庭的人是：" << dadname << endl;
			tree.PrintSon(dadname);
			tree.Remove(dadname);
		}
		else if (operate == "D") {
			string oldname, newname;
			printf("请输入要更改姓名的人的目前姓名：");
			cin >> oldname;
			printf("请输入更改后的姓名：");
			cin >> newname;
			tree.Modify(oldname, newname);
			tree.PrintNewName(oldname, newname);
		}
		else if (operate == "E")
			break;
		else {
			printf("您输入的操作代码非法，请重新输入！\n");
		}
	}
}