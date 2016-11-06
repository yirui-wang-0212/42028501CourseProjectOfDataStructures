#include<iostream>
using namespace std;

char chessboard[50][50];                                         //棋盘
int position[50];                                                //记录每行皇后的位置
bool column_available[50];                                       //记录此列是否已存在皇后

int n;
int cnt;

bool diagonal_availabe(int ln, int col) {                        //从对角线角度看是否能在此位置放置皇后

	for (int i = 0; i < ln; ++i)
		if (ln - i == col - position[i] || ln - i == position[i] - col)
			return false;
	
	return true;
}

void DFS(int ln) {

	if (ln == n) {                                               //全部放完后打印棋盘
		 
		++cnt;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cout << chessboard[i][j] << ' ';
			cout << endl;
		}
		cout << endl;
		return;
	}

	for (int i = 0; i < n; ++i) {

		if (column_available[i] && diagonal_availabe(ln, i)) {   //列和对角线都符合要求
			column_available[i] = false;
			chessboard[ln][i] = 'X';
			position[ln] = i;
			DFS(ln + 1);                                         //递归
			column_available[i] = true;                          //回溯
			chessboard[ln][i] = '0';
		}
	}
	return;
}

int main() {

	cout << "现有N×N的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！\n\n"
		<< "请输入皇后的个数： " << flush;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) 
			chessboard[i][j] = '0';	

		column_available[i] = true;
	}
	DFS(0);
	cout << "共有" << cnt << "种解法！" << endl;

	return 0;
}