#include "GameManager.h"
#include <iostream>
#include <string>
#include <windows.h> 
using namespace std;

/* 入堡 */

int main()
{
	GameManager b;
	string s;
	bool newgame = true;
	cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl;
	cout << "☆   _____ _    _ ______  _____ _____       ☆\n☆  / ____| |  | |  ____|/ ____/ ____|      ☆\n☆ | |    | |__| | |__  | (___| (___        ☆\n☆ | |    |  __  |  __|  \\___  \\___ \\       ☆\n☆ | |____| |  | | |____ ____) |___) |      ☆\n☆  \\_____|_|  |_|______|_____/_____/ .txt  ☆\n☆                                          ☆" << endl;
	cout << "☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆" << endl << endl;
	cout << "歡迎來到\"文字版\"西洋棋" << ",請輸入任何文字以繼續" << endl;
	cin >> s;

	while (newgame)
	{
		if (!b.loadFile())	// 檢查是否要讀檔
		{
			b.choseFirstColor(); //如果沒有要讀檔的話就   選擇先攻的棋子顏色
			b.setBoard(); //如果沒有要讀檔的話就       初始棋盤
		}

		//b.viewer.clockCountDown();

		while (b.playGame()); //遊戲進行

		cout << "是否要再下一局，是請輸入y，結束請輸入n " << endl; //再下一局
		cin >> s;

		if (s != "y") //No
			newgame = false;
	}

	return 0;
}