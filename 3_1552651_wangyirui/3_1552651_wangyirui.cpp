#include"posstack_class.h"

enum Type { kMapLn, kMapCol, kLn, kCol };
enum LnMove { kLeft = -1, kStill = 0, kRight = 1 };
enum ColMove { kUp = -1, kDown = 1 };

int ln_move[] = { kLeft, kStill, kRight, kStill };
int col_move[] = { kStill, kUp, kStill, kDown };

char input_map[20][20];//存储玩家输入的地图
bool isvisited[20][20];//存储坐标是否访问过

int map_ln, map_col;//地图的行列
int entrance_ln, entrance_col;//入口坐标
int exit_ln, exit_col;//出口坐标
int route_count = 0;//通路数
PAIR pos;

PosStack posstack;

void DFS(int cur_ln, int cur_col) {

	//若访问的位置是终点，输出路线图和路线经过的坐标
	if (cur_ln == exit_ln && cur_col == exit_col) {

		++route_count;

		//输出路线图
		cout << "地图路线" << route_count << "：" << endl;

		for (int j = 0; j < map_col; ++j) {
			if (j == 0)
				cout << "        " << j << "列";
			else
				cout << "      " << j << "列";
		}
		cout << endl;

		for (int i = 0; i < map_ln; ++i) {
			cout << i << "行";
			for (int j = 0; j < map_col; ++j) {
				if (j == 0)
					cout << "      ";
				else
					cout << "        ";
				if (isvisited[i][j])
					cout << '*';
				else
					cout << input_map[i][j];
			}
			cout << endl;
		}


		//输出路线经过的坐标
		for (int i = 0; i <= posstack.top(); ++i) {

			if (i == 0)
				cout << "<" << posstack.route(i).first << "," << posstack.route(i).second << ">";
			else
				cout << " ---> " << "<" << posstack.route(i).first << "," << posstack.route(i).second << ">";
		}
		cout << endl;

		return;
	}

	for (int i = 0; i < 4; ++i) {

		//访问下一位置
		int next_ln = cur_ln + ln_move[i];
		int next_col = cur_col + col_move[i];

		//若访问的位置不是终点，标记后进行递归
		if (next_ln > -1 && next_ln < map_ln && next_col > -1 && next_col < map_col) {
			if (input_map[next_ln][next_col] == '0'&&isvisited[next_ln][next_col] == false) {

				isvisited[next_ln][next_col] = true;
				//压栈
				pos = make_pair(next_ln, next_col);
				posstack.push(pos);
				//递归
				DFS(next_ln, next_col);
				//回溯、出栈
				isvisited[next_ln][next_col] = false;
				posstack.pop();
			}
		}
	}
	return;
}

//读入函数，用第二个参数判断第一个参数，输出相应的输入提示文字
void readin(int &n, int type) {

	cin >> n;
	if(type == kMapLn)
	while (n <= 0) {
		cout << "输入非法数字，请重新输入： " << endl
			<< "行： " << flush;
		cin >> n;
	}
	if (type == kMapCol)
		while (n <= 0) {
			cout << "输入非法数字，请重新输入： " << endl
				<< "列： " << flush;
			cin >> n;
		}
	if (type == kLn)
		while (n < 0 || n >= map_ln) {
			cout << "输入非法数字，请重新输入： " << endl
				<< "行： " << flush;
			cin >> n;
		}
	if (type == kCol)
		while (n < 0 || n >= map_col) {
			cout << "输入非法数字，请重新输入： " << endl
				<< "列： " << flush;
			cin >> n;
		}
}

int main() {

	cout << "请输入地图规格： (<=20*20)" << endl;

	cout << "行： " << flush;
	readin(map_ln, kMapLn);
	cout << "列： " << flush;
	readin(map_col, kMapCol);

	cout << "请输入地图： （0代表路，#代表墙，两字符以单个空格为间隔，行末以回车键结束）" << endl;

	for (int i = 0; i < map_ln; ++i)
		for (int j = 0; j < map_col; ++j) {
			cin >> input_map[i][j];
			getchar();
		}

	cout << "请输入入口坐标： （从0开始计数）" << endl;

	cout << "行： " << flush;
	readin(entrance_ln, kLn);

	cout << "列： " << flush;
	readin(entrance_col, kCol);

	while (input_map[entrance_ln][entrance_col] != '0') {

		cout << "此位置不能作为入口，请重新输入： " << endl;

		cout << "行： " << flush;
		readin(entrance_ln, kLn);
		cout << "列： " << flush;
		readin(entrance_col, kCol);
	}

	cout << "请输入出口坐标： （从0开始计数）" << endl;

	cout << "行： " << flush;
	readin(exit_ln, kLn);
	cout << "列： " << flush;
	readin(exit_col, kCol);

	while (input_map[exit_ln][exit_col] != '0') {

		cout << "此位置不能作为出口，请重新输入： " << endl;

		cout << "行： " << flush;
		readin(exit_ln, kLn);
		cout << "列： " << flush;
		readin(exit_ln, kCol);

	}
	
	//入口
	isvisited[entrance_ln][entrance_col] = true;
	pos = make_pair(entrance_ln, entrance_col);
	posstack.push(pos);
	DFS(entrance_ln, entrance_col);

	//若不存在通路数的输出
	if (route_count == 0) {
		cout << "不存在从出口到达入口的通路" << endl;
	}

	return 0;

}
