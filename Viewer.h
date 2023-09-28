#pragma once
#include <iostream>
#include <windows.h>
using namespace std;
class GameManager;
class Viewer
{
public:
	void errorPrint(int type)
	{
		switch (type)
		{
		case 1:
			cout << "輸入格式錯誤： 請輸入對應座標軸之 \"2位數字\"" << endl;
			break;
		case 2:
			cout << "輸入格式錯誤： 請輸入2位 \"數字\"" << endl;
			break;
		case 3:
			cout << "選擇指令錯誤： 指定格子超出棋盤" << endl;
			break;
		case 4:
			cout << "選擇指令錯誤： 選定該格沒有棋子" << endl;
			break;
		case 5:
			cout << "選擇指令錯誤： 那不是你的棋子，請想好再下" << endl;
			break;
		case 6:
			cout << "選擇指令錯誤： 選定該格未知原因錯誤" << endl;
			break;
		}
	}

	void SetColor(int color);
	void clockCountDown();
	void printChosenChessBoard(GameManager* GM, int x, int y);
	void printBoard(GameManager* GM);
};

