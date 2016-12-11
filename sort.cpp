#include<iostream>
#include<vector>
#include<stack>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;

#define INFINITY 1 << 30

void bubblesort(vector<int> A, int n, time_t &t, int &ts) {
	
	time_t t_start, t_end;
	t_start = time(NULL);
	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 1; i < n; ++i) {
			if (A[i - 1] > A[i]) {
				swap(A[i - 1], A[i]);
				++ts;
				sorted = false;
			}
		}
		n--;
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

void selectionsort(vector<int> A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	int min;
	for (int i = 0; i < n - 1; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[min] > A[j])
				min = j;
		}
		swap(A[i], A[min]);
		++ts;
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

void insertionsort(vector<int> A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	int temp;
	for (int i = 1; i < n; ++i) {
		temp = A[i];
		int j = i - 1;
		for (; j >= 0 && temp < A[j]; --j) {
			A[j + 1] = A[j];
			++ts;
		}
		A[j + 1] = temp;
		++ts;
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

void sethibbard(int *h, int k) {

	int m = 1;
	for (int i = 0; i <= k; ++i) {
		h[i] = m;
		m *= 2;
	}
}

void shellsort(vector<int> A, int n, time_t &t, int &ts) {
	time_t t_start, t_end;
	t_start = time(NULL);
	int hibbard[1000];
	int k = log2(n) - 1;
	int temp;
	sethibbard(hibbard, k);
	for (int i = k; i >= 0; --i) {
		int gap = hibbard[i];
		for (int j = gap; j < n; ++j) {
			temp = A[j];
			int l = j - gap;
			for (; l >= 0 && A[l] > temp; l -= gap) {
				A[l + gap] = A[l];
				++ts;
			}
			A[l + gap] = temp;
		}
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

//void quicksort_recursive(vector<int> &A, int start, int end, int &ts) {
//
//	if (start >= end)return;
//	int mid = A[end];
//	int l = start, r = end - 1;
//	while (l < r) {
//		while (A[l] < mid && l < r)l++;
//		while (A[r] > mid && l < r)r--;
//		swap(A[l], A[r]);
//		++ts;
//	}
//	if (A[l] >= A[end]) {
//		swap(A[l], A[r]);
//		++ts;
//	}
//	else
//		++l;
//	quicksort_recursive(A, start, l - 1, ts);
//	quicksort_recursive(A, l + 1, end, ts);
//
//}

//void quicksort(vector<int> A, int n, time_t &t, int &ts) {
//
//	time_t t_start, t_end;
//	t_start = time(NULL);
//	quicksort_recursive(A, 0, n - 1, ts);
//	t_end = time(NULL);
//	t = difftime(t_end, t_start);
//	return;
//}

void quicksort(vector<int> A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	if (n <= 1)
		return;
	stack<int> ranges;
	int l = 0;
	int r = n - 1;
	ranges.push(l);
	ranges.push(r);
	while (!ranges.empty()) {
		int tr = r = ranges.top(); ranges.pop();
		int tl = l = ranges.top(); ranges.pop();
		int pivot = A[tl];
		while (tr > tl) {
			while (tr > tl && A[tr] > pivot)
				--tr;
			while (tr > tl && A[tl] < pivot)
				++tl;
			swap(A[tr], A[tl]);
			++ts;
		}
		A[tl] = pivot;
		if (tl - l >= 1) { 
			ranges.push(l); ranges.push(tl);
		}
		if (r - (tl + 1) >= 1) { 
			ranges.push(tl + 1); ranges.push(r); 
		}
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

void max_heapify(vector<int> A, int start, int end, int &ts) {

	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && A[son] < A[son + 1])
			++son;
		if (A[dad] > A[son])
			return;
		else {
			swap(A[dad], A[son]);
			++ts;
			dad = son;
			son = son * 2 + 1;
		}
	}
}

void heapsort(vector<int> A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	for (int i = (n - 1) / 2; i >= 0; --i)
		max_heapify(A, i, n - 1, ts);
	for (int i = n - 1; i > 0; --i) {
		swap(A[0], A[i]);
		++ts;
		max_heapify(A, 0, i - 1, ts);
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

void mergesort(vector<int> &A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	vector<int>b(n);
	for (int seg = 1; seg < n; seg += seg) {
		for (int start = 0; start < n; start += seg + seg) {
			int low = start, mid = min(start + seg, n), high = min(start + seg + seg, n);
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			int k = low;
			while (start1 < end1 && start2 < end2) {
				b[k++] = A[start1] < A[start2] ? A[start1++] : A[start2++];
				++ts;
			}
			while (start1 < end1) {
				b[k++] = A[start1++];
				++ts;
			}
			while (start2 < end2) {
				b[k++] = A[start2++];
				++ts;
			}
		}
		auto temp = A;
		A = b;
		b = temp;
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

int maxbit(vector<int> &A, int n) {

	int max = A[0];
	for (int i = 0; i < n; ++i) {
		if (max < A[i])
			max = A[i];
	}
	int d = 1;
	int p = 10;
	while (max >= p) {
		max /= 10;
		++d;
	}
	return d;
}

void radixsort(vector<int> &A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	int d = maxbit(A, n);
	vector<int>temp(n);
	vector<int>count(10);
	int radix = 1;
	int i, j, k;
	for (i = 0; i < d; ++i) {
		for (j = 0; j < 10; ++j) {
			count[j] = 0;
		}
		for (j = 0; j < n; ++j) {
			k = (A[j] / radix) % 10;
			++count[k];
		}
		for (int j = 1; j < 10; ++j) {
			count[j] = count[j - 1] + count[j];
		}
		for (j = n - 1; j >= 0; --j) {
			k = (A[j] / radix) % 10;
			temp[count[k] - 1] = A[j];
			++ts;
			--count[k];
		}
		A = temp;
		radix *= 10;
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

void binaryinsertsort(vector<int> A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);
	int temp, low, high, mid, i, j;
	for (i = 1; i < n; ++i) {

		low = 0;
		high = i - 1;
		temp = A[i];

		while (low <= high) {
			mid = (low + high) / 2;
			if (A[mid] > temp)
				high = mid - 1;
			else
				low = mid + 1;
		}

		for (j = i - 1; j > high; --j) {
			A[j + 1] = A[j];
			++ts;
		}
		A[j + 1] = temp;
		++ts;
	}
	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

struct node{

	int data;
	int id;
	node(int m, int n) {
		data = m;
		id = n;
	}
};

void tournamentsort(vector<int> &A, int n, time_t &t, int &ts) {

	time_t t_start, t_end;
	t_start = time(NULL);

	bool flag = false;

	if (n % 2) {
		A[n] = INFINITY;
		n += 1;
		flag = true;
	}
	vector<node*>tree(2 * n - 1);

	for (int i = 0; i < n; ++i) {
		node *p = new node(A[i], i);
		tree[i + (n - 1)] = p;
	}
	for (int i = n - 2; i >= 0; --i) {
		node *p1 = tree[2 * i + 1]->data < tree[2 * i + 2]->data ? tree[2 * i + 1] : tree[2 * i + 2];
		++ts;
		node *p2 = new node(p1->data, p1->id);
		tree[i] = p2;
	}
	for (int i = 0; i < n - 1; ++i) {
		A[i] = tree[0]->data;
		int index = tree[0]->id;
		tree[index + (n - 1)]->data = INFINITY;
		for (int j = (index + (n - 1) - 1) / 2; j >= 0; j = (j - 1) / 2) {
			tree[j] = tree[2 * j + 1]->data < tree[2 * j + 2]->data ? tree[2 * j + 1] : tree[2 * j + 2];
			++ts;
			if (j == 0) break;
		}
	}

	if (!flag)
		A[n - 1] = tree[0]->data;
	for (int i = 0; i < n; ++i)
		delete tree[i + (n - 1)];

	t_end = time(NULL);
	t = difftime(t_end, t_start);
	return;
}

int main() {

	int n;
	printf("请输入要产生的随机数个数：");
	scanf("%d", &n);
	vector<int>num(n + 5);

	for (int j = 0; j < n; ++j)
		num[j] = rand();

	while (true) {

		int op;
		time_t t;
		int ts = 0;
		printf("\n请选择排序算法：         ");
		scanf("%d", &op);

		if (op == 1) {

			bubblesort(num, n, t, ts);
			printf("冒泡排序所用时间：        %d\n", t);
			printf("冒泡排序交换次数：        %d\n", ts);
		}

		if (op == 2) {
			selectionsort(num, n, t, ts);
			printf("选择排序所用时间：        %d\n", t);
			printf("选择排序交换次数：        %d\n", ts);
		}

		if (op == 3) {
			insertionsort(num, n, t, ts);
			printf("插入排序所用时间：        %d\n", t);
			printf("插入排序交换次数：        %d\n", ts);
		}

		if (op == 4) {

			shellsort(num, n, t, ts);
			printf("希尔排序所用时间：        %d\n", t);
			printf("希尔排序交换次数：        %d\n", ts);
		}

		if (op == 5) {

			quicksort(num, n, t, ts);
			printf("快速排序所用时间：        %d\n", t);
			printf("快速排序交换次数：        %d\n", ts);
		}

		if (op == 6) {

			heapsort(num, n, t, ts);
			printf("堆排序所用时间：        %d\n", t);
			printf("堆排序交换次数：        %d\n", ts);
		}

		if (op == 7) {

			mergesort(num, n, t, ts);
			printf("归并排序所用时间：        %d\n", t);
			printf("归并排序交换次数：        %d\n", ts);
		}
		if (op == 8) {

			radixsort(num, n, t, ts);
			printf("基数排序所用时间：        %d\n", t);
			printf("基数排序交换次数：        %d\n", ts);
		}
		if (op == 9) {

			binaryinsertsort(num, n, t, ts);
			printf("折半插入排序所用时间：        %d\n", t);
			printf("折半插入排序交换次数：        %d\n", ts);
		}
		if (op == 10) {
			tournamentsort(num, n, t, ts);
			printf("锦标赛排序所用时间：        %d\n", t);
			printf("锦标赛排序交换次数：        %d\n", ts);
		}
	}
	return 0;
}