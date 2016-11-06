#include"examineelist_class.h"

//initialize the static member variable
Examinee *ExamineeList::head_ = new Examinee;
Examinee *ExamineeList::tail_ = new Examinee;
int ExamineeList::total_ = 0;

//index with position
Examinee* ExamineeList::IndexPosition(int index) {

	Examinee *current = head_;

	for (int i = 0; i < index; ++i)
		current = current->next_;

	return current;

}

//index with number
Examinee* ExamineeList::IndexNum(int index) {

	Examinee *current = head_;

	while (current->num() != index && current != tail_) 
		current = current -> next_;

	if (current == tail_)
		return NULL;
	
	return current;
}

void ExamineeList::Insert(int index, Examinee *node) {

	Examinee *previous = IndexPosition(index - 1);

	node->next_ = previous->next_;
	node->prior_ = previous;
	previous->next_ = node;
	node->next_->prior_ = node;

	++total_;

	return;
}

void ExamineeList::Delete(int index) {

	Examinee *current = IndexNum(index);

	if (current == NULL) {

		cout << '\n' << "不存在学号为" << index << "的考生信息" << endl;
		return;
	}

	Examinee *previous = current->prior_;
	Examinee *following = current->next_;

	previous->next_ = following;
	following->prior_ = previous;

	delete current;

	--total_;
	
	return;
}

void ExamineeList::Modify(int index, Examinee *node) {

	Examinee *current = IndexNum(index);
	if (current == NULL) {

		cout << '\n' << "不存在学号为" << index << "的考生信息" << endl;
		return;
	}

	Examinee *previous = current->prior_;
	Examinee *following = current->next_;

	//change the node
	node->prior_ = previous;
	node->next_ = following;
	previous->next_ = node;
	following->prior_ = node;

	delete current;

	return;
}

//print the searched student's information
void ExamineeList::SearchOutput(int index){

	Examinee *current = IndexNum(index);
	if (current == NULL) {

		cout << '\n' << "不存在学号为" << index << "的考生信息" << endl;
		return;
	}

	cout << endl;
	//print this node's information
	current->Output();

	return;
}

//print the list
void ExamineeList::Output() {

	if (total_ == 0) {

		cout << '\n' << "不存在考生信息" << endl;
		return;
	}

	cout << "\n"
		<< "考号" << "    "
		<< "姓名" << "    "
		<< "性别" << "    "
		<< "年龄" << "    "
		<< "报考类别" << endl;

	Examinee *current = head_;
	current = head_->next_;
	while (current != tail_) { 
		//print this node's information
		current->Output();
		current = current->next_;
	}

	return;
}