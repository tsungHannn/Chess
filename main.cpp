#include "GameManager.h"
#include <iostream>
#include <string>
#include <windows.h> 
using namespace std;

/* �J�� */

int main()
{
	GameManager b;
	string s;
	bool newgame = true;
	cout << "����������������������������������������������" << endl;
	cout << "��   _____ _    _ ______  _____ _____       ��\n��  / ____| |  | |  ____|/ ____/ ____|      ��\n�� | |    | |__| | |__  | (___| (___        ��\n�� | |    |  __  |  __|  \\___  \\___ \\       ��\n�� | |____| |  | | |____ ____) |___) |      ��\n��  \\_____|_|  |_|______|_____/_____/ .txt  ��\n��                                          ��" << endl;
	cout << "����������������������������������������������" << endl << endl;
	cout << "�w��Ө�\"��r��\"��v��" << ",�п�J�����r�H�~��" << endl;
	cin >> s;

	while (newgame)
	{
		if (!b.loadFile())	// �ˬd�O�_�nŪ��
		{
			b.choseFirstColor(); //�p�G�S���nŪ�ɪ��ܴN   ��ܥ��𪺴Ѥl�C��
			b.setBoard(); //�p�G�S���nŪ�ɪ��ܴN       ��l�ѽL
		}

		//b.viewer.clockCountDown();

		while (b.playGame()); //�C���i��

		cout << "�O�_�n�A�U�@���A�O�п�Jy�A�����п�Jn " << endl; //�A�U�@��
		cin >> s;

		if (s != "y") //No
			newgame = false;
	}

	return 0;
}