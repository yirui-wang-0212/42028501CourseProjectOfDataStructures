#include<iostream>
#include<vector>
#include<stack>
#include<cmath>
#include<ctime>
#include<algorithm>

using namespace std;

#define INFINITY 1 << 30

void bubblesort(vector<int> A, vector<int> &B, int n, int &ts) {

	bool sorted = false;
	while (!sorted) {
		sorted = true;
		for (int i = 1; i < n; ++i) {
			if ((++ts, A[i - 1] > A[i])) {
				swap(A[i - 1], A[i]);
				sorted = false;
			}
		}
		n--;
	}
	B = A;
	return;
}

void selectionsort(vector<int> A, vector<int> &B, int n, int &ts) {

	int min;
	for (int i = 0; i < n - 1; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j) {
			if ((++ts, A[min] > A[j]))
				min = j;
		}
		swap(A[i], A[min]);
	}
	B = A;
	return;
}

void insertionsort(vector<int> A, vector<int> &B, int n, int &ts) {

	int temp;
	for (int i = 1; i < n; ++i) {
		temp = A[i];
		int j = i - 1;
		for (; (++ts, j >= 0 && temp < A[j]); --j)
			A[j + 1] = A[j];
		A[j + 1] = temp;
	}
	B = A;
	return;
}

void sethibbard(int n, int *h, int &k) {

	int m = 1;
	for (int i = 0; m <= n; ++i) {
		++k;
		h[i] = m;
		m = m * 2 + 1;
	}
}

void shellsort(vector<int> A, vector<int> &B, int n, int &ts) {

	int hibbard[1000];
	int temp, k = -1;
	sethibbard(n, hibbard, k);
	for (int i = k; i >= 0; --i) {
		int gap = hibbard[i];
		for (int j = gap; j < n; ++j) {
			temp = A[j];
			int l = j - gap;
			for (; (++ts, l >= 0 && A[l] > temp); l -= gap) {
				A[l + gap] = A[l];
			}
			A[l + gap] = temp;
		}
	}
	B = A;
	return;
}

void quicksort(vector<int> A, vector<int> &B, int n, int &ts) {

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
			while (tr > tl && (++ts, A[tr] > pivot))
				--tr;
			while (tr > tl && (++ts, A[tl] < pivot))
				++tl;
			swap(A[tr], A[tl]);
		}
		A[tl] = pivot;
		if (tl - l >= 1) {
			ranges.push(l); ranges.push(tl);
		}
		if (r - (tl + 1) >= 1) {
			ranges.push(tl + 1); ranges.push(r);
		}
	}
	B = A;
	return;
}

void maxheapify(vector<int> &A, int start, int end, int &ts) {

	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) {
		if (son + 1 <= end && (++ts, A[son] < A[son + 1]))
			++son;
		if ((++ts, A[dad] > A[son]))
			return;
		else {
			swap(A[dad], A[son]);
			dad = son;
			son = son * 2 + 1;
		}
	}
	return;
}

void heapsort(vector<int> A, vector<int> &B, int n, int &ts) {

	for (int i = n / 2 - 1; i >= 0; --i)
		maxheapify(A, i, n - 1, ts);
	for (int i = n - 1; i > 0; --i) {
		swap(A[0], A[i]);
		maxheapify(A, 0, i - 1, ts);
	}
	B = A;
	return;
}

void mergesort(vector<int> A, vector<int> &B, int n, int &ts) {

	vector<int>b(n);
	for (int seg = 1; seg < n; seg += seg) {
		for (int start = 0; start < n; start += seg + seg) {
			int low = start, mid = min(start + seg, n), high = min(start + seg + seg, n);
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			int k = low;
			while (start1 < end1 && start2 < end2)
				b[k++] = (++ts, A[start1] < A[start2]) ? A[start1++] : A[start2++];
			while (start1 < end1) {
				b[k++] = A[start1++];
			}
			while (start2 < end2) {
				b[k++] = A[start2++];
			}
		}
		auto temp = A;
		A = b;
		b = temp;
	}
	B = A;
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

void radixsort(vector<int> A, vector<int> &B, int n, int &ts) {

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
			--count[k];
		}
		A = temp;
		radix *= 10;
	}
	B = A;
	return;
}

void binaryinsertsort(vector<int> A, vector<int> &B, int n, int &ts) {

	int temp, low, high, mid, i, j;
	for (i = 1; i < n; ++i) {

		low = 0;
		high = i - 1;
		temp = A[i];

		while (low <= high) {
			mid = (low + high) / 2;
			if ((++ts, A[mid] > temp))
				high = mid - 1;
			else
				low = mid + 1;
		}

		for (j = i - 1; j > high; --j)
			A[j + 1] = A[j];

		A[j + 1] = temp;
	}
	B = A;
	return;
}

struct node {

	int data;
	int id;
	node(int m, int n) {
		data = m;
		id = n;
	}
};

void tournamentsort(vector<int> A, vector<int> &B, int n, int &ts) {


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
		node *p1 = (++ts, tree[2 * i + 1]->data < tree[2 * i + 2]->data) ? tree[2 * i + 1] : tree[2 * i + 2];
		node *p2 = new node(p1->data, p1->id);
		tree[i] = p2;
	}
	for (int i = 0; i < n - 1; ++i) {
		A[i] = tree[0]->data;
		int index = tree[0]->id;
		tree[index + (n - 1)]->data = INFINITY;
		for (int j = (index + (n - 1) - 1) / 2; j >= 0; j = (j - 1) / 2) {
			tree[j] = (++ts, tree[2 * j + 1]->data < tree[2 * j + 2]->data) ? tree[2 * j + 1] : tree[2 * j + 2];
			if (j == 0) break;
		}
	}

	if (!flag)
		A[n - 1] = tree[0]->data;
	for (int i = 0; i < n; ++i)
		delete tree[i + (n - 1)];

	B = A;
	return;
}

int main() {

	int n;
	printf("请输入要产生的随机数个数：");
	scanf("%d", &n);
	printf("\n**               排序问题                  **\n");
	printf("=============================================\n");
	printf("**               请选择排序方法              **\n");
	printf("**              1---冒泡排序                **\n");
	printf("**              2---选择排序                **\n");
	printf("**              3---插入排序                **\n");
	printf("**              4---希尔排序                **\n");
	printf("**              5---快速排序                **\n");
	printf("**              6---堆排序                  **\n");
	printf("**              7---归并排序                **\n");
	printf("**              8---基数排序                **\n");
	printf("**              9---折半插入排序             **\n");
	printf("**              10--锦标赛排序              **\n");
	printf("**              11--退出程序                **\n");
	printf("=============================================\n\n");

	vector<int>num(n + 5);
	vector<int>sorted(n + 5);

	for (int j = 0; j < n; ++j)
		num[j] = rand();

	clock_t clockstart, clockend;
	double timeused;

	while (true) {

		int op;
		time_t t;
		int ts = 0;
		printf("\n请选择排序算法：         ");
		scanf("%d", &op);

		if (op == 1) {

			clockstart = clock();
			bubblesort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("冒泡排序所用时间：        %lf\n", timeused);
			printf("冒泡排序比较次数：        %d\n", ts);
		}

		if (op == 2) {

			clockstart = clock();
			selectionsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("选择排序所用时间：        %lf\n", timeused);
			printf("选择排序比较次数：        %d\n", ts);
		}

		if (op == 3) {

			clockstart = clock();
			insertionsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("插入排序所用时间：        %lf\n", timeused);
			printf("插入排序比较次数：        %d\n", ts);
		}

		if (op == 4) {

			clockstart = clock();
			shellsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("希尔排序所用时间：        %lf\n", timeused);
			printf("希尔排序比较次数：        %d\n", ts);
		}

		if (op == 5) {

			clockstart = clock();
			quicksort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("快速排序所用时间：        %lf\n", timeused);
			printf("快速排序比较次数：        %d\n", ts);
		}

		if (op == 6) {

			clockstart = clock();
			heapsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("堆排序所用时间：         %lf\n", timeused);
			printf("堆排序比较次数：         %d\n", ts);
		}

		if (op == 7) {

			clockstart = clock();
			mergesort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("归并排序所用时间：        %lf\n", timeused);
			printf("归并排序比较次数：        %d\n", ts);
		}
		if (op == 8) {

			clockstart = clock();
			radixsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("基数排序所用时间：        %lf\n", timeused);
			printf("基数排序比较次数：        %d\n", ts);
		}
		if (op == 9) {

			clockstart = clock();
			binaryinsertsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("折半插入排序所用时间：    %lf\n", timeused);
			printf("折半插入排序比较次数：    %d\n", ts);
		}
		if (op == 10) {

			clockstart = clock();
			tournamentsort(num, sorted, n, ts);
			clockend = clock();
			timeused = (clockend - clockstart) / static_cast<double>(CLOCKS_PER_SEC);
			printf("锦标赛排序所用时间：      %lf\n", timeused);
			printf("锦标赛排序比较次数：      %d\n", ts);
		}
		if (op == 11)
			break;
	}
	return 0;

	system("pause");
}