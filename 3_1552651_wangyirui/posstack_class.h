#pragma once
#include<iostream>
using namespace std;

#define PAIR pair<int, int>

class PosStack {

public:

	int top() { return top_; }
	PAIR route(int n) { return route_[n]; }

	void push(PAIR pos) {
		++top_;
		route_[top_] = pos;
	}

	void pop() {
		--top_;
	}

private:
	PAIR route_[40];//存放路线的位置坐标
	int top_ = -1;//栈顶指针
};
