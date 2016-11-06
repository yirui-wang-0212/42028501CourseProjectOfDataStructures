#include"BT_class.h"

const int maxlen = 100;//用户输入表达式的最大长度
char inexpr[maxlen];//存储用户输入的表达式
pNode expr[maxlen];//存储处理过的表达式
int inexprcnt = 0;//用户输入的表达式的长度
int exprcnt = 0;//处理过的表达式的长度

BT bt;

void buildtree(pNode opr, pNode sucopd, pNode preopd) {

	opr->lc_ = preopd;
	opr->rc_ = sucopd;

}

void stackprocess(pNode *expr, int cnt, pNode &root) {

	stack<pNode> operands;//数栈
	stack<pNode> operators;//符栈
	pNode cur;//当前处理的Node
	int index = 0;

	while (index != cnt) {

		cur = expr[index];

		//遇到前括号
		if (cur->opr_=='(') {
			//用于匹配括号，当flag == 0时匹配到正确的')'
			int flag = 1;
			pNode tmp[maxlen];//存储括号内的表达式
			int tmpcnt = 0;//括号内表达式的长度
			pNode tmproot = NULL;//括号内表达式建成树后返回的根节点
			while (true) {

				++index;//读取括号内表达式下一个数字或符号

				//遇到一个')'，flag自减1
				if (expr[index]->opr_ == ')') {
					--flag;
					if (!flag)
						break;	//当flag == 0时匹配到正确的')'，跳出读括号内内容的循环	
				}
				//遇到一个'('， flag自加1
				if (expr[index]->opr_ == '(')
					++flag;

				//依次将括号内内容存入一个数组
				tmp[tmpcnt++] = expr[index];
			}
			//括号内内容递归调用stackprocess函数
			stackprocess(tmp, tmpcnt, tmproot);
			//将括号内表达式建成树后返回的根节点压入数栈
			operands.push(tmproot);

			delete cur;
			delete expr[index];

		}
		//如果是操作符
		else if (cur->pr_ > 0) {
			auto pre = expr[index - 1];
			if (!operators.empty() && operators.top()->pr_ < cur->pr_) {
				while (true) {
					auto opr = operators.top();
					operators.pop();
					auto sucopd = operands.top();
					operands.pop();
					auto preopd = operands.top();
					operands.pop();
					buildtree(opr, sucopd, preopd);//由两个数和一个符号构建一棵树
					//记录树的根节点
					root = opr;
					//将建成的树压入数栈
					operands.push(opr);		
					//弹栈直至栈中优先级高于当前运算符的运算符弹尽
					pre = operators.top();//检查目前的栈顶符号
					if (pre->pr_ >= cur->pr_)
						break;
				}
			}
			//将当前运算符压栈
			operators.push(cur);
		}
		//如果是操作数，直接压栈
		else if (cur->pr_ < 0)
			operands.push(cur);
		++index;
	}
	while (!operators.empty()) {
		auto opr = operators.top();
		operators.pop();
		auto sucopd = operands.top();
		operands.pop();
		auto preopd = operands.top();
		operands.pop();
		buildtree(opr, sucopd, preopd);//由两个数和一个符号构建一棵树
		root = opr;//记录树的根节点
	   //将建成的树压入数栈
		operands.push(opr);
	}
	root = operands.top();//根节点为处理完整个表达式后数栈中唯一的元素
}

void setinex() {

	int i = 0;
	while (i != inexprcnt) {
		pNode op = new Node;
		if (isdigit(inexpr[i])) {
			char num[maxlen];//存储数字的字符串
			//直到读到不是数字的字符
			int j = 0;
			while (isdigit(inexpr[i])) {
				num[j++] = inexpr[i++];
			}
			op->setNode(atoi(num), -1);//将存储数字的字符串转化为int型数字
			memset(num, 0, sizeof(num));
			expr[exprcnt++] = op;//放入表达式数组
		}
		else {

			//根据不同的计算符号设置优先级

			if (inexpr[i] == '(' || inexpr[i] == ')') {
				op->setNode(inexpr[i], 0);
				expr[exprcnt++] = op;
			}

			if (inexpr[i] == '-') {
				//判断此'-'为负号
				if (i == 0 || !isdigit(inexpr[i - 1]) || inexpr[i + 1] == '(') {
					op->setNode(-1, -1);
					expr[exprcnt++] = op;//先在处理后的表达式数组中放入数字-1
					pNode op2 = new Node;
					op2->setNode('*', 2);
					expr[exprcnt++] = op2;//再在处理后的表达式数组中放入运算符*
				}
				
				else {
					op->setNode(inexpr[i], 3);
					expr[exprcnt++] = op;
				}
			}

			if (inexpr[i] == '+') {
				op->setNode(inexpr[i], 3);
				expr[exprcnt++] = op;
			}

			if (inexpr[i] == '*' || inexpr[i] == '/') {
				op->setNode(inexpr[i], 2);
				expr[exprcnt++] = op;
			}
			++i;
		}
		
	}
}



int main() {

	printf("请输入表达式： ");

	//读入并存储用户输入的表达式
	while (true){
		char c;
		scanf("%c", &c);
		if (c == '\n')
			break;
		inexpr[inexprcnt++] = c;
	}

	setinex();

	stackprocess(expr, exprcnt, bt.root_);

	printf("\n\n波兰表达式： ");
	bt.travPre_R(bt.root_);

	printf("\n\n中缀表达式： ");
	int i = 0;
	while (i != inexprcnt) {
		printf("%c", inexpr[i]);
		++i;
	}

	printf("\n\n逆波兰表达式： ");
	bt.travIn_R(bt.root_);


	printf("\n\n");

	return 0;
}