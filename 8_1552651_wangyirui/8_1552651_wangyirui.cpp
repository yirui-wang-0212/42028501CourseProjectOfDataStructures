#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;
const int maxn = 100;

#define INF 1 << 30

struct node {
	int vnum;
	int key;//到已经访问过的顶点边的长度最小值
	friend bool operator<(node a, node b) {
		return a.key > b.key;
	}
};

int n;//顶点个数
int rootnum;//开始点，即最小生成树的根节点
int graph[maxn][maxn];//邻接表，存储两点间是否相连以及两点间边的长度的信息
string vname[maxn];//顶点名字对应节点序号
bool visited[maxn];//顶点是否访问过
int dad[maxn];//顶点在最小生成树中的父亲节点
node v[maxn];//prim算法中各顶点状态
map<int, int> tree;//存储最小生成树的边及边的两顶点
priority_queue <node> q;//选择已知顶点

void prim(int beginnum){

	for (int i = 0; i < n; ++i) {
		v[i].vnum = i;
		v[i].key = INF;
		dad[i] = -1;
		visited[i] = false;
	}

	v[beginnum].key = 0;
	q.push(v[beginnum]);

	while (!q.empty()) {

		node cur_nd = q.top();
		q.pop();
		int cur_vnum = cur_nd.vnum;
		int dad_vnum = dad[cur_vnum];
		if (dad_vnum != -1)
			tree.insert(make_pair(dad_vnum, cur_vnum));
		if (visited[cur_vnum])
			continue;
		visited[cur_vnum] = true;

		for (int i = 0; i < n; ++i) {

			if (i != cur_vnum && !visited[i] && graph[cur_vnum][i] < v[i].key) {

				dad[i] = cur_vnum;
				v[i].key = graph[cur_vnum][i];
				q.push(v[i]);
			}
		}
	}
}


int main() {

	printf("\n**             电网造价模拟系统            **\n");
	printf("=============================================\n");
	printf("**              A---创建电网顶点           **\n");
	printf("**              B---添加电网的边           **\n");
	printf("**              C---构造最小生成树         **\n");
	printf("**              D---显示最小生成树         **\n");
	printf("**              E---退出程序               **\n");
	printf("=============================================\n");

	char op;
	while (true) {

		printf("\n请选择操作：");
		scanf("%c", &op);

		if (op == 'A') {

			printf("请输入顶点个数：");
			scanf("%d", &n);
			printf("请依次输入个顶点名称：\n");
			for (int i = 0; i < n; ++i)
				cin >> vname[i];
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					graph[i][j] = INF;
			getchar();
		}

		if (op == 'B') {
			string v1, v2;
			int v1num, v2num;
			int len;
			while (true) {
				printf("请输入两个顶点及边：");
				cin >> v1 >> v2 >> len;
				if (v1 == "?")
					break;
				for (int i = 0; i < n; ++i) {
					if (vname[i] == v1)
						v1num = i;
					if (vname[i] == v2)
						v2num = i;
				}
				graph[v1num][v2num] = len;
				graph[v2num][v1num] = len;
			}
			getchar();
		}
		if (op == 'C') {
			string root;		
			printf("请输入起始顶点：");
			cin >> root;
			getchar();
			for (int i = 0; i < n; ++i) {
				if (vname[i] == root) {
					rootnum = i;
					break;
				}
			}
			prim(rootnum);
			printf("生成prim最小生成树！\n");
		}
		if (op == 'D') {
			printf("最小生成树的顶点及边为：\n");
			for (auto vpair : tree) {
				int v1num = vpair.first;
				int v2num = vpair.second;
				cout << vname[v1num] << "-<" << graph[v1num][v2num] << ">->" << vname[v2num] << "	";
			}
			cout << endl;
			getchar();
		}
		if (op == 'E')
			break;
	}
}