#pragma once
#include"examinee_class.h"

//using Singleton Pattern
class ExamineeList {

//Singleton Pattern
public:
	static ExamineeList& Instance(){
		static ExamineeList instance;
		return instance;
	}

private:
	//initialize the head and the tail
	ExamineeList() {
		head_->prior_ = NULL;
		head_->next_ = tail_;

		tail_->prior_ = head_;
		tail_->next_ = NULL;

	}
	//delete the linked list
	~ExamineeList() {

		auto current = head_;
		Examinee *following = current;

		while (following != tail_) {
			following = current->next_;
			delete current;
			current = following;
		}
		delete tail_;
	}
	//Singleton Pattern
	ExamineeList(const ExamineeList&);
	ExamineeList& operator=(const ExamineeList&);

public:
	// return and set total_
	int total() const { return total_; }
	void set_total(int total) { total_ = total; }

	//index with position
	Examinee *IndexPosition(int index);
	//index with number
	Examinee *IndexNum(int index);

	//required operation
	void Insert(int index, Examinee *node);
	void Delete(int index);
	void Modify(int index, Examinee *node);
	//print the searched student's information
	void SearchOutput(int index);
	//print the list
	void Output();

private:
	static Examinee *head_;
	static Examinee *tail_;
	static int total_;//the total number
};