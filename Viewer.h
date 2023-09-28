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
			cout << "��J�榡���~�G �п�J�����y�жb�� \"2��Ʀr\"" << endl;
			break;
		case 2:
			cout << "��J�榡���~�G �п�J2�� \"�Ʀr\"" << endl;
			break;
		case 3:
			cout << "��ܫ��O���~�G ���w��l�W�X�ѽL" << endl;
			break;
		case 4:
			cout << "��ܫ��O���~�G ��w�Ӯ�S���Ѥl" << endl;
			break;
		case 5:
			cout << "��ܫ��O���~�G �����O�A���Ѥl�A�зQ�n�A�U" << endl;
			break;
		case 6:
			cout << "��ܫ��O���~�G ��w�Ӯ楼����]���~" << endl;
			break;
		}
	}

	void SetColor(int color);
	void clockCountDown();
	void printChosenChessBoard(GameManager* GM, int x, int y);
	void printBoard(GameManager* GM);
};

