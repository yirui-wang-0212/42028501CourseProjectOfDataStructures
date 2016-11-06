#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

int main() {

	map<string, size_t> article;
	string filename;

	cout << "关键字检索系统\n"
		<< "请输入文件名： " << flush;

	cin >> filename;
	ofstream outfile(filename);
	cout << "\n请输入一段英文： " << endl;

	string word;
	char letter;
	getchar();
	//将文本逐字符读入文件中
	while (scanf("%c", &letter) != EOF) 
		outfile << letter;

	outfile.close();
	cout << "本段文本已保存在文本文件\"src.txt\"中。\n\n" << endl;

	ifstream infile(filename);
	string keyword;
	cout << "请输入要检索的关键字： " << flush;
	//读入用户输入的关键字
	cin >> keyword;
	cout << "显示源文件\"" << filename << "\":\n" << endl;

	//将文件中的文本逐字符串读入，逐字符串进行处理
	while (infile >> word) {
		string realword;
		//将单词中的标点符号去除
		for (auto it = word.begin(); it != word.end(); it++) {
			if ((it == word.begin() || it == word.end() - 1) && ispunct(*it))
				continue;
			realword += *it;
		}
		//将单词转为全小写字母
		transform(realword.begin(), realword.end(), realword.begin(), ::tolower);
		//若该单词不存在map中，则将该将单词放入map中，否则map的值自加一
		++article[realword];
		cout << word << " ";
	}
	
	//将用户输入的关键字转为全小写字母
	transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
	
	//在map中搜索用户输入的关键字
	auto it = article.find(keyword);
	cout << "\n\n在源文件中共检索到： " << it->second << "个关键字\"" << keyword << "\"" << endl;

	return 0;
}