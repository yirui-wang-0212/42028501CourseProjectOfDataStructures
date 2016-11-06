#pragma once

#include<iostream>
#include<string>

using namespace std;

class Examinee {

public:

	Examinee(int num, string name, string gender, int age, string category) :
		num_(num), name_(name), gender_(gender), age_(age), category_(category), prior_(NULL), next_(NULL) {};
	Examinee() = default;
	~Examinee() = default;

	int num() const { return num_; }

	//print this node's information
	void Output();

public:
	Examinee *prior_;
	Examinee *next_;

private:
	int num_;
	string name_;
	string gender_;
	int age_;
	string category_;
};
