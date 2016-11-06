#include"passenger_class.h"
#include"passengerlist_class.h"

int main() {

	int total, startnum, deathnum, residue;

	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K人为止" << "\n\n"
		<< "请输入生死游戏的总人数N：" << flush;
	cin >> total;
	while (total < 1) {
		cout << "您输入的数字为非法数字，请重新输入：" << flush;
		cin >> total;
	}

	cout << "请输入游戏开始的位置S：  " << flush;
	cin >> startnum;
	while (startnum < 1 || startnum > total) {
		cout << "您输入的数字为非法数字，请重新输入：" << flush;
		cin >> startnum;
	}

	cout << "请输入死亡数字M：        " << flush;
	cin >> deathnum;
	while (deathnum < 1 || deathnum > total) {
		cout << "您输入的数字为非法数字，请重新输入：" << flush;
		cin >> deathnum;
	}

	cout << "请输入剩余的生者人数：   " << flush;
	cin >> residue;
	while (residue < 0 || residue > total) {
		cout << "您输入的数字为非法数字，请重新输入：" << flush;
		cin >> residue;
	}

	cout << endl;
	
	if (residue == 0) {
		cout << "很遗憾，不存在幸存者" << endl;
		return 0;
	}

	if (total == residue) {
		cout << "幸运的是，所有人都将存活" << endl;
		return 0;
	}

	//initialize the linked list with arguments offered
	PassengerList passengerlist(total, startnum, deathnum, residue);

	passengerlist.Create();
	passengerlist.Kill();
	passengerlist.SurvivalListOutput();

	return 0;
}