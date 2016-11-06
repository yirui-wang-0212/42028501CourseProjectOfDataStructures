#pragma once
#include<iostream>
using namespace std;

//linked list's node
class Passenger {

public:
	Passenger(int num) { num_ = num; }
	int num() { return num_; }

public:
	Passenger *next_ = NULL;

private:
	int num_;
};
