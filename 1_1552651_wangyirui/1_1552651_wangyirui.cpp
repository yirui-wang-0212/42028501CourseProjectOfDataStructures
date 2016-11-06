#include<iostream>
#include<string>
#include"examinee_class.h"
#include"examineelist_class.h"

using namespace std;

int main() {
	
	cout << "首先请建立考生信息系统：" << endl
		<< "请输入考生人数： "<<flush;
	
	int sum;
	cin >> sum;
	//the total number is illegal
	while (sum <= 0) {

		cout << endl << "输入非法数字，请重新输入： "<<flush;
		cin >> sum;
	}

	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;

	int num, age, index;
	string name, gender, category;
	Examinee *examinee;
	ExamineeList *examinee_list = &ExamineeList::Instance();//create the linked list

	//add nodes to the linked list
	for (int i = 0; i < sum; ++i) {

		cin >> num >> name >> gender >> age >> category;
		examinee = new Examinee(num, name, gender, age, category);
		examinee_list->Insert(i + 1, examinee);
	}

	//print the list
	examinee_list->Output();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << "\n\n"
		<< "请选择您要进行的操作： " << flush;

	//store the operation type
	int operation;

	do {
		cin >> operation;

		while (operation < 0 || operation>5) {

			cout << '\n' << "输入非法数字，请重新输入： "<<flush;
			cin >> operation;
		}
		
		//cancel
		if (operation == 0) {
			return 0;
		}

		//insert
		if (operation == 1) {

			cout << "请输入你要插入考生的位置： "<<flush;
			cin >> index;

			if (index > examinee_list->total() + 1)
				cout << '\n' << "在此位置插入为非法操作" << endl;

			else {
				cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
				cin >> num >> name >> gender >> age >> category;
				examinee = new Examinee(num, name, gender, age, category);
				examinee_list->Insert(index, examinee);
				examinee_list->Output();
			}
		}

		//delete
		if (operation == 2) {

			cout << "请输入要删除考生的学号： " << flush;
			cin >> index;
			examinee_list->Delete(index);
			examinee_list->Output();
		}

		//search
		if (operation == 3) {

			cout << "请输入要查找的考生的考号： " << flush;
			cin >> index;
			examinee_list->SearchOutput(index);
		}

		//modify
		if (operation == 4) {

			cout << "请输入要修改的考生的考号： " << flush;
			cin >> index;
			cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
			cin >> num >> name >> gender >> age >> category;
			examinee = new Examinee(num, name, gender, age, category);
			examinee_list->Modify(index, examinee);
			examinee_list->Output();
		}

		// statistics
		if (operation == 5) {

			sum = examinee_list->total();
			cout << '\n' << "共计有" << sum << "位考生" << endl;
			examinee_list->Output();
		}

		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << "\n\n"
			<< "请选择您要进行的操作： " << flush;

	} while (operation != 0);

	return 0;
}