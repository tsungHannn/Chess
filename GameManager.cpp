#include "GameManager.h"

Square::Square()//default constructor
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)//�Ѥl constructor
{
	color = space->getColor();  //�Ѥl�C��
	piece = space->getPiece();  //�Ѥl����
}

void Square::setEmpty()//�Ů� constructor
{
	piece = EMPTY;  //�Ů� �S�Ѥl����
	color = NONE;   //�Ů� �S�Ѥl�C��
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;

}

// �ˬd��ܴѤl�X�k��
bool GameManager::chooseChessToMove(const string chosenChess)
{
	int x1, y1;

	if (chosenChess.length() != 2)
	{
		viewer.errorPrint(1);
		//cout << "��J�榡���~�G �п�J�����y�жb�� \"2��Ʀr\" �H���w�����ʴѤl" << endl;
		return false;
	}
	else if (chosenChess.length() == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (chosenChess[i] < '0' || chosenChess[i]>'9') //��J�����O�Ʀr
			{
				viewer.errorPrint(2);
				//cout << "��J�榡���~�G �п�J2�� \"�Ʀr\" �H���w�����ʴѤl" << endl;
				return false;
			}
		}

		x1 = chosenChess[0] - 48;
		y1 = chosenChess[1] - 48;

		if (x1 < 0 || x1>7 || y1 < 0 || y1>7)
		{
			viewer.errorPrint(3);
			//std::cout << "��ܫ��O���~�G ���w��l�W�X�ѽL" << std::endl; //�W�X�ѽL����
			return false;
		}


		if (getSquare(x1, y1)->getColor() == turn) //�T�w�Ӧ^�X�U�Ѫ��C�⥿�T
		{
			//�O�A���Ѥl
			return true;
		}
		else if (getSquare(x1, y1)->getColor() == NONE) //��w�Ӯ�S���Ѥl
		{
			viewer.errorPrint(4);
			//cout << "��ܫ��O���~�G ��w�Ӯ�S���Ѥl" << endl;
			return false;
		}
		else if (getSquare(x1, y1)->getColor() != turn) //��w�Ӯ椣�O�A���Ѥl
		{
			viewer.errorPrint(5);
			//cout << "��ܫ��O���~�G �����O�A���Ѥl�A�зQ�n�A�U" << endl;  //��X�Ӧ^�X���O�A���^�X
			return false;
		}
		else
		{
			viewer.errorPrint(6);
			//cout << "��ܫ��O���~�G ��w�Ӯ楼����]���~" << endl;
			return false;
		}
	}
}

// �ˬd��ܥت��a�X�k��
bool GameManager::chooseDestinationMoveTo(string chooseDestination)
{
	system("cls");
	viewer.printBoard(this);

	if (chooseDestination.length() != 2)
	{
		viewer.errorPrint(1);
		//cout << "��J�榡���~�A�п�J \"2��Ʀr\" ���w�����ʦ�m" << endl;
		return false;
	}
	else if (chooseDestination.length() == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (chooseDestination[i] < '0' || chooseDestination[i]>'9') //��J�����O�Ʀr
			{
				viewer.errorPrint(2);
				//cout << "��J�榡���~�A�п�J \"�Ʀr\"" << endl;
				return false;
			}
		}

		return true;
	}
}

//�ˬd ��J�X�k ���ʦX�k (�P�_�ӧQ�P�_)
bool GameManager::doMove()
{
	using namespace std;
	string move;
	string chosenChess, chooseDestination;
	int x1, x2, y1, y2;  //��lx ��ly ���x ���y
	bool stop = false;  //��J�X�k��
	bool KingDead = false;


	while (!stop) //���D��J�X�k  �_�h�ݭ��s��J
	{
		cout << "===================================================================" << endl << endl;

		(turn == WHITE) ? cout << "�{�b����զ�U�� : " << endl : cout << "�{�b����¦�U�� : " << endl << endl;  //��X�o�^�X�����(�¥�)

		cout << "��w���U���X�l�A�п�J��ӼƦr�A���жb������ xy" << endl; //��J���� 
		cout << "�Y�Q�뭰�A�п�J \"gg\"�A��^�W�@�B�п�J \"regret\"�A���^�U�@�B�п�J\"next\"" << endl;

		bool inputOriginChessVaild; //�w�]���O���T
		bool regretOrNot = false;	//�˴�����
		bool regretBroken = false;	//���ѥ���
		bool nextOrNot = false;	//�˴��л\����
		bool nextBroken = false;	//�л\���ѥ���
		bool saveOrNot = false;	//�ˬd�s��
		// //�ˬd��J�X�k��
		while (player.OnMove(chosenChess))
		{
			system("cls");
			viewer.printBoard(this);
			if (chosenChess == "gg")
			{
				if (turn == WHITE)
				{
					cout << "�մѤ�뭰�A�����Ѷ´Ѥ���� �I�I�I" << endl; //�զ����

					return false; //�S���U�@�^�X ���X�C���y�{
				}
				else
				{
					cout << "�´Ѥ�뭰�A�����ѥմѤ���� �I�I�I" << endl; //�զ����

					return false; //�S���U�@�^�X ���X�C���y�{
				}
			}

			if (chosenChess == "regret")	//�W�@�B
			{
				if (round < 1)
				{
					cout << "�w�g�S���W�@�B�F" << endl;
					system("PAUSE");
					regretBroken = true;
					break;
				}
				else
				{
					//�n�qdestination���^original
					Square* destination;
					Square* original;

					//���o�ثe��destination
					destination = getSquare(moveList[round - 1][2], moveList[round - 1][3]);

					//��destination�����e�M�Φboriginal�W
					original = getSquare(moveList[round - 1][0], moveList[round - 1][1]);
					original->setPieceAndColor(destination->getPiece(), destination->getColor());
					original->setX(moveList[round - 1][0]);
					original->setY(moveList[round - 1][1]);

					//��destination�զ^�ʧ@�e���ˤl
					Piece destinationPiece;
					Color destinationColor;
					switch (moveList[round - 1][4])	//�w�qdestinationPiece�O����Ѥl
					{
					case 0:
						destinationPiece = KING;
						break;
					case 1:
						destinationPiece = QUEEN;
						break;
					case 2:
						destinationPiece = BISHOP;
						break;
					case 3:
						destinationPiece = KNIGHT;
						break;
					case 4:
						destinationPiece = ROOK;
						break;
					case 5:
						destinationPiece = PAWN;
						break;
					case 6:
						destinationPiece = EMPTY;
						break;
					default:
						cout << "�W�@�B���Ѥl��������" << endl;
						break;
					}

					switch (moveList[round - 1][5])	//�w�qdestinationColor�O�����C��
					{
					case 0:
						destinationColor = WHITE;
						break;
					case 1:
						destinationColor = BLACK;
						break;
					case 2:
						destinationColor = NONE;
						break;
					default:
						cout << "�W�@�B���Ѥl�C�⦳��" << endl;
						break;
					}


					destination->setPieceAndColor(destinationPiece, destinationColor);	//�]�wdestination�쥻���Ѥl
					destination->setX(moveList[round - 1][2]);
					destination->setY(moveList[round - 1][3]);

					regretOrNot = true;
					break;

				}

			}

			if (chosenChess == "next")	//�U�@�B(���Ѥ���i�H�i��)
			{
				if (round < moveList.size())
				{
					makeMove(moveList[round][0], moveList[round][1], moveList[round][2], moveList[round][3]);
					cout << "redo���\�A��J���N��H�~��C��" << endl;
					nextOrNot = true;
					break;
				}
				else
				{
					cout << "�S�����ѥi�H�л\" << endl;
					system("PAUSE");
					nextBroken = true;
					break;
				}
			}

			//if (chosenChess == "replay")	//������ثe���Ѥl�ʦV
			//{
			//	system("CLS");
			//	GameManager replayBoard;
			//	replayBoard.setBoard();	//��l�ƴѽL
			//	replayBoard.viewer.printBoard(&replayBoard);	//�L�X�ѽL
			//	system("CLS");
			//	for (int i = 0; i < round; i++)
			//	{
			//		replayBoard.viewer.printChosenChessBoard(this, moveList[i][0], moveList[i][1]);
			//		Sleep(1000);
			//		system("CLS");
			//		replayBoard.makeMove(moveList[i][0], moveList[i][1], moveList[i][2], moveList[i][3]);
			//		replayBoard.viewer.printBoard(this);
			//		Sleep(1000);
			//		system("CLS");

			//	}
			//	cout << "���񧹦��A��J���N��H�~��C��" << endl;
			//	continue;
			//}

			if (chosenChess == "replay")	//������ثe���Ѥl�ʦV
			{
				system("CLS");
				GameManager replayBoard;
				replayBoard.setBoard();	//��l�ƴѽL
				replayBoard.viewer.printBoard(&replayBoard);	//�L�X�ѽL
				system("CLS");
				for (int i = 0; i < round; i++)
				{
					replayBoard.viewer.printChosenChessBoard(&replayBoard, moveList[i][0], moveList[i][1]);
					Sleep(1000);
					system("CLS");
					replayBoard.makeMove(moveList[i][0], moveList[i][1], moveList[i][2], moveList[i][3]);
					replayBoard.viewer.printBoard(&replayBoard);
					Sleep(1000);
					system("CLS");

				}
				cout << "���񧹦��A��J���N��H�~��C��" << endl;
				continue;
			}

			if (chosenChess == "save")
			{
				fstream saveBoard;
				saveBoard.open("save.txt", ios::trunc | ios::out);
				saveBoard << turn;	//����
				saveBoard << endl;

				for (int i = 0; i < 8; i++)	//����
				{
					for (int j = 0; j < 8; j++)
					{
						saveBoard << getSquare(i, j)->getPiece();
					}
					saveBoard << endl;
				}

				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						saveBoard << getSquare(i, j)->getColor();
					}
					if (i < 7)
					{
						saveBoard << endl;
					}

				}
				/*for (int i = 0; i < moveList.size(); i++)
				{
					for (int j = 0; j < 6; j++)
					{
						saveBoard << moveList[i][j];
					}
					if (i < moveList.size() - 1)
					{
						saveBoard << endl;
					}

				}*/

				cout << "�s�ɦ��\" << endl;
				system("PAUSE");
				saveOrNot = true;
				saveBoard.close();
			}
			inputOriginChessVaild = chooseChessToMove(chosenChess);

			if (inputOriginChessVaild != true)
			{
				break;
			}
			else
			{
				break;
			}
		}

		if (regretOrNot)	//�p�G����
		{
			if (turn == BLACK) //�¦�^�X����
			{
				turn = WHITE; //���զ�^�X
			}
			else              //�զ�^�X����
			{
				turn = BLACK;   //���¦�^�X
			}
			round--;
			return true;
		}
		if (regretBroken)	//���ѥ���
		{
			return true;
		}
		if (nextOrNot)	//�p�G�л\����
		{
			if (turn == BLACK) //�¦�^�X����
			{
				turn = WHITE; //���զ�^�X
			}
			else              //�զ�^�X����
			{
				turn = BLACK;   //���¦�^�X
			}
			round++;
			return true;
		}
		if (nextBroken)	//�л\���ѥ���
		{
			return true;
		}
		if (saveOrNot)	//�s�ɦ��\
		{
			return true;
		}

		if (inputOriginChessVaild == false)
		{
			continue;
		}

		x1 = chosenChess[0] - 48;
		y1 = chosenChess[1] - 48;

		system("cls");
		viewer.printChosenChessBoard(this, x1, y1);


		cout << "======================================================================" << endl;
		cout << "��w(" << x1 << "," << y1 << ")  ��w���Ѥl���G ";
		if (getSquare(x1, y1)->getColor() == 0)
		{
			cout << "\"�զ�\"";
		}
		else
		{
			cout << "\"�¦�\"";
		}
		cout << " �� ";
		switch (getSquare(x1, y1)->getPiece())
		{
		case 0:
			cout << "\"���\"" << endl;
			break;
		case 1:
			cout << "\"�ӦZ\"" << endl;
			break;
		case 2:
			cout << "\"�D��\"" << endl;
			break;
		case 3:
			cout << "\"�M�h\"" << endl;
			break;
		case 4:
			cout << "\"����\"" << endl;
			break;
		case 5:
			cout << "\"�h�L\"" << endl;
			break;
		case 6:
			cout << "\"�Ů�\"" << endl;
			break;
		default:
			break;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Print ��w�X�l���ܩM�i�����|
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//�ˬd���ʦX�k��
		while (player.OnMove(chooseDestination))
		{
			bool inputDestinationVaild; //�w�]���O���T

			inputDestinationVaild = chooseDestinationMoveTo(chooseDestination);

			if (inputDestinationVaild != true)
			{
				stop = false;
				break;
			}
			else
			{
				stop = true;
				break;
			}
		}

		if (stop == false) //���s��J��ܴѤl
		{
			continue;
		}

		x2 = chooseDestination[0] - 48;
		y2 = chooseDestination[1] - 48;

		if (getSquare(x2, y2)->getPiece() == KING) //���ʫe���P�w�ت��a�O�_�����N�x
		{
			KingDead = true;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		drawMoveList(x1, y1, x2, y2);

		if (makeMove(x1, y1, x2, y2) == false)
		{
			cout << "�����\���ʡA�Э��s��J" << endl; //��J���~ ���s��J
			eraseMoveList();
			stop = false;
			KingDead = false;
			continue;
		}
		else
		{
			stop = true; //��J���T �ˬd�ӧQ����
			cout << "�q(" << x1 << "," << y1 << ")���ʦ�(" << x2 << "," << y2 << ")  ���ʦ��\" << endl;
		}

		//system("pause");
	}

	//�ˬd�N��
	if (whiteCheck())
	{
		cout << "!!!!!! �մѳQ�N�x�F !!!!!!" << endl;
		system("PAUSE");
	}
	if (blackCheck())
	{
		cout << "!!!!!! �´ѳQ�N�x�F !!!!!!" << endl;
		system("PAUSE");
	}

	if (KingDead)
	{
		system("cls");
		viewer.printBoard(this);
		cout << "===============================================================" << endl;

		if (getSquare(x1, y1)->getColor() == WHITE)
		{
			cout << "�´Ѥ�N�x���`�A���ߥմѤ���� �I�I�I" << endl; //�զ����

			return false; //�S���U�@�^�X ���X�C���y�{
		}
		else
		{
			cout << "�մѤ�N�x���`�A���߶´Ѥ���� �I�I�I" << endl; //�¦����

			return false; //�S���U�@�^�X ���X�C���y�{
		}
	}

	if (turn == BLACK) //�¦�^�X����
	{
		turn = WHITE; //���զ�^�X
	}
	else              //�զ�^�X����
	{
		turn = BLACK;   //���¦�^�X
	}

	return true; //�٦��U�@�^�X
}

//================================================================moveList
//�s�WmoveList
void GameManager::drawMoveList(int x1, int y1, int x2, int y2)
{
	vector <int> temp;	//�s�o�^�X������
	Square* original;
	Square* destination;
	original = getSquare(x1, y1);
	destination = getSquare(x2, y2);
	temp.resize(6);
	temp[0] = x1;
	temp[1] = y1;
	temp[2] = x2;
	temp[3] = y2;
	temp[4] = destination->getPiece();	//�����Q�Y�����Ѥl����
	temp[5] = destination->getColor();
	round++;
	if (round - 1 < moveList.size())
	{
		moveList[round - 1] = temp;
	}
	else
	{
		moveList.push_back(temp);
	}

}
//==============================================================eraseMoveList
//���ʤ��X�k���ܭn�R���W�@��moveList
void GameManager::eraseMoveList()
{
	moveList.pop_back();
	round--;
}

//�]�m��l�ѽL
void GameManager::setBoard()
{
	//��l�զ�Ѥl
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[0][1].setPieceAndColor(KNIGHT, WHITE);
	square[0][2].setPieceAndColor(BISHOP, WHITE);
	square[0][3].setPieceAndColor(QUEEN, WHITE);
	square[0][4].setPieceAndColor(KING, WHITE);
	square[0][5].setPieceAndColor(BISHOP, WHITE);
	square[0][6].setPieceAndColor(KNIGHT, WHITE);
	square[0][7].setPieceAndColor(ROOK, WHITE);

	//��l�¦�Ѥl
	square[7][0].setPieceAndColor(ROOK, BLACK);
	square[7][1].setPieceAndColor(KNIGHT, BLACK);
	square[7][2].setPieceAndColor(BISHOP, BLACK);
	square[7][3].setPieceAndColor(QUEEN, BLACK);
	square[7][4].setPieceAndColor(KING, BLACK);
	square[7][5].setPieceAndColor(BISHOP, BLACK);
	square[7][6].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	//��l�¥դp�L
	for (int i = 0; i < 8; i++)
	{
		square[1][i].setPieceAndColor(PAWN, WHITE);
		square[6][i].setPieceAndColor(PAWN, BLACK);
	}

	//��l�����Ů�
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[i][j].setPieceAndColor(EMPTY, NONE);

	}


	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}
}

//�C�@�^�X
bool GameManager::playGame()
{
	system("cls");  //�M���ª���
	viewer.printBoard(this);   //�L�X�s����
	return doMove(); //true ���U�@�^�X
					  //false  �S���U�@�^�X �����C���y�{ 
}

//�ˬd���� King ��� �O�_�X�k  �p�G�X�k��������
bool GameManager::moveKing(Square* thisKing, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	if (abs(thatSpace->getX() - thisKing->getX()) <= 1)  //�E�c��X�k
		if (abs(thatSpace->getY() - thisKing->getY()) <= 1)
		{
			thatSpace->setSpace(thisKing); //���ʨ�destination
			thisKing->setEmpty();		   //���set�Ů�
			return true;
		}
		else return false;
	else return false;
}

//�ˬd���� Queen �ӦZ �O�_�X�k  �p�G�X�k��������
bool GameManager::moveQueen(Square* thisQueen, Square* thatSpace)
{ //there might be problems with numbers of brackets
//off board inputs should be handled elsewhere (before this)
//squares with same color should be handled elsewhere (before this)

	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	std::cout << "this";
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)//����
	{

		if (queenX == thatX)//��V
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)//���V
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))//�צV
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						std::cout << "It got here somehow";
						if (square[queenX + xIncrement * i][queenY + yIncrement * i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
		//if()
	}



	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

//�ˬd���� Bishop �D�� �O�_�X�k  �p�G�X�k��������
bool GameManager::moveBishop(Square* thisBishop, Square* thatSpace)
{ //there might be problems with number of brackets
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Square* s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			std::cout << "It got here somehow";
			if (square[bishopX + xIncrement * i][bishopY + yIncrement * i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

//�ˬd���� Kinght �M�h �O�_�X�k  �p�G�X�k��������
bool GameManager::moveKnight(Square* thisKnight, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) //��r���X�k
	{
		thatSpace->setSpace(thisKnight);  //���ʨ�destination
		thisKnight->setEmpty();			  //���set�Ů�
		return true;
	}
	else
	{
		return false;
	}
}

//�ˬd���� Rook ���� �O�_�X�k  �p�G�X�k��������
bool GameManager::moveRook(Square* thisRook, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{
		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)  //���� �X�k���� + ����
	{
		thatSpace->setSpace(thisRook); //���ʨ�destination
		thisRook->setEmpty();		   //���set�Ů�
		return true;
	}
	else  //���� �D�k����
	{//Return some erorr or something. Probably return false;
		std::cout << "That is an invalid move for rook";
		return false;
	}
}

//�ˬd���� Pawn �p�L �O�_�X�k  �p�G�X�k��������
bool GameManager::movePawn(Square* thisPawn, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();


	if (thisPawn->getColor() == WHITE)//White
	{
		//Initial move
		if (pawnX == 1 && thatX == 3 && pawnY == thatY && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);  //���ʨ�destination
			thisPawn->setEmpty();			//���set�Ů�
			return true;
		}
		//Y����
		if (pawnY == thatY && thatX == pawnX + 1 && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);  //���ʨ�destination
			thisPawn->setEmpty();			//���set�Ů�
			checkPromoting(thatSpace);
			return true;
		}
		else
			if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX + 1 == thatX && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);  //���ʨ�destination
				thisPawn->setEmpty();			//���set�Ů�
				checkPromoting(thatSpace);
				return true;
			}
			else
				return false;
	}
	else//Black
		if (thisPawn->getColor() == BLACK)
		{
			//Initial move
			if (pawnX == 6 && thatX == 4 && pawnY == thatY && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);  //���ʨ�destination
				thisPawn->setEmpty();			//���set�Ů�
				return true;
			}
			if (pawnY == thatY && thatX == pawnX - 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);  //���ʨ�destination
				thisPawn->setEmpty();			//���set�Ů�
				checkPromoting(thatSpace);
				return true;
			}
			else
				if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX - 1 == thatX && thatSpace->getColor() == WHITE)
				{
					thatSpace->setSpace(thisPawn);  //���ʨ�destination
					thisPawn->setEmpty();			//���set�Ů�
					checkPromoting(thatSpace);
					return true;
				}
				else
					return false;
		}
		else
			return false;
}

void GameManager::checkPromoting(Square* target)
{
	using namespace std;
	int x = target->getX();
	if (x == 7 && target->getColor() == WHITE)//white promote
	{
		bool done = false;
		while (!done)
		{
			done = true;
			cout << "�A���h�L��F���u�A�{�b�A�i�H��ܤ@�ؤɯ�\n";
			cout << "��J�����ܤ��L�� Q(Queen)/R(Rook)/N(Knight)/B(Bishop):\n";
			char type;
			player.OnPromote(type);
			switch (type)
			{
			case 'Q':
				target->setPieceAndColor(QUEEN, WHITE);
				break;
			case 'R':
				target->setPieceAndColor(ROOK, WHITE);
				break;
			case 'N':
				target->setPieceAndColor(KNIGHT, WHITE);
				break;
			case 'B':
				target->setPieceAndColor(BISHOP, WHITE);
				break;
			default:
				cout << "Error:���X�k�����ܩεL�k���Ѫ��r���A�Э��s��J�C\n";
				done = false;
				break;
			}
		}
	}
	else if (x == 0 && target->getColor() == BLACK)//blace promote
	{
		bool done = false;
		while (!done)
		{
			done = true;
			cout << "�A���h�L��F���u�A�{�b�A�i�H��ܤ@�ؤɯ�\n";
			cout << "��J�����ܤ��L�� Q(Queen)/R(Rook)/N(Knight)/B(Bishop):\n";
			char type;
			cin >> type;
			switch (type)
			{
			case 'Q':
				target->setPieceAndColor(QUEEN, BLACK);
				break;
			case 'R':
				target->setPieceAndColor(ROOK, BLACK);
				break;
			case 'N':
				target->setPieceAndColor(KNIGHT, BLACK);
				break;
			case 'B':
				target->setPieceAndColor(BISHOP, BLACK);
				break;
			default:
				cout << "Error:���X�k�����ܩεL�k���Ѫ��r���A�Э��s��J�C\n";
				done = false;
				break;
			}
		}
	}

}


//Intent: �T�겾�ʫ��O  
//Pre: ��lx ��ly ���x ���y
//Post: 
bool GameManager::makeMove(int x1, int y1, int x2, int y2)
{
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "���ʫ��O���~�G ���w��l�W�X�ѽL" << std::endl; //�W�X�ѽL����
		return false;
	}

	Square* original = getSquare(x1, y1);
	Square* destination = getSquare(x2, y2);

	if (original->getColor() == destination->getColor() && destination->getColor() != NONE)
	{
		std::cout << "���ʫ��O���~�G �ؼФw�g���v��Ѥl" << std::endl; //�ؼЮ�w�g���v��Ѥl
		return false;
	}

	switch (original->getPiece())
	{
	case KING:return moveKing(original, destination);
		break;
	case QUEEN: return moveQueen(original, destination);
		break;
	case BISHOP: return moveBishop(original, destination);
		break;
	case KNIGHT: return moveKnight(original, destination);
		break;
	case ROOK: return moveRook(original, destination);
		break;
	case PAWN: return movePawn(original, destination);
		break;
	case EMPTY: std::cout << "���w����l�S���A���Ѥl" << std::endl;  return false; //��ؼ�original�S���Ѥl
		break;
	default: std::cerr << "�����������D��]  Something went wrong in the switch statement in makeMove()" << std::endl; //�����������D��]
		break;
	}
	return false;
}

void GameManager::choseFirstColor()
{
	string color;

	while (1)
	{
		cout << "�M�w����誺�C��G �п�J\"black\" �� \"white\"" << endl;
		cin >> color;

		if (color == "black")
		{
			turn = BLACK;
			return;
		}
		else if (color == "white")
		{
			turn = WHITE;
			return;
		}
		else
		{
			cout << "����C����w���~�A�Э��s��J�G" << endl;
			continue;
		}
	}
}

bool GameManager::loadFile()
{
	string doLoad;
	bool loadFileOrNot;
	fstream loadFile;
	while (1)
	{
		cout << "�O�_�nŪ��?  �п�J\"yes\" or \"no\"" << endl;
		cin >> doLoad;

		if (doLoad == "yes")
		{
			loadFileOrNot = true;
			break;
		}
		else if (doLoad == "no")
		{
			loadFileOrNot = false;
			break;
		}
		else
		{
			cout << "���Ū�ɿ�J���~�A�Э��s��J�G" << endl;
			continue;
		}

	}

	if (loadFileOrNot == true)
	{
		string tempTurn;
		string loadString;
		vector <vector <int> > loadPiece;
		vector <vector <int> > loadColor;
		loadFile.open("save.txt");
		getline(loadFile, tempTurn);	//Ū���֥��U
		if (tempTurn == "0")
		{
			turn = WHITE;
		}
		else if (tempTurn == "1")
		{
			turn = BLACK;
		}
		for (int i = 0; i < 8; i++)	//Ū��piece
		{
			getline(loadFile, loadString);
			vector <int> temp;
			for (int j = 0; j < 8; j++)	//����int
			{
				temp.push_back(loadString[j] - '0');
			}
			loadPiece.push_back(temp);
		}
		for (int i = 0; i < 8; i++)
		{
			getline(loadFile, loadString);
			vector <int> temp;
			for (int j = 0; j < 8; j++)	//����int
			{
				temp.push_back(loadString[j] - '0');
			}
			loadColor.push_back(temp);
		}
		setBoard();
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				Piece tempPiece;
				Color tempColor;

				switch (loadPiece[i][j])	//Ū���Ӯ�O����Ѥl
				{
				case 0:
					tempPiece = KING;
					break;
				case 1:
					tempPiece = QUEEN;
					break;
				case 2:
					tempPiece = BISHOP;
					break;
				case 3:
					tempPiece = KNIGHT;
					break;
				case 4:
					tempPiece = ROOK;
					break;
				case 5:
					tempPiece = PAWN;
					break;
				case 6:
					tempPiece = EMPTY;
					break;
				default:
					cout << "Ū�ɪ��Ѥl��������" << endl;
					break;
				}
				switch (loadColor[i][j])	//Ū���Ӯ�O�����C��
				{
				case 0:
					tempColor = WHITE;
					break;
				case 1:
					tempColor = BLACK;
					break;
				case 2:
					tempColor = NONE;
					break;
				default:
					cout << "Ū�ɪ��Ѥl�C�⦳��" << endl;
					break;
				}
				square[i][j].setPieceAndColor(tempPiece, tempColor);

			}
		}
		return true;
	}
	else
	{
		return false;
	}

}
bool GameManager::blackCheck()	//�¦�Q�N�x
{
	bool ans = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)	//�e���for�O���ӽL�����@��
		{
			if (getSquare(i, j)->getColor() != NONE)	//�p�G�o�Ӯ�l���Ѥl
			{
				if (getSquare(i, j)->getColor() == WHITE)	//�ӥB�O�զ�
				{
					//�զ�i�H�Y�¦⪺�����ܴNreturn true
					switch (getSquare(i, j)->getPiece())
					{
					case KING:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)	//�W�����for�O���ӽL�����@��
							{
								if (k == i && m == j)//����ۤv
								{
									continue;
								}
								if (checkKing(getSquare(i, j), getSquare(k, m)))//�p�G�o�Ӧ�l�O���ʦX�k����l
								{
									if (getSquare(k, m)->getPiece() == KING)	//�p�G�o�Ӧ�l�OKING
									{
										if (getSquare(k, m)->getColor() == BLACK)	//�ӥB�O�¦⪺
										{
											ans = true;
										}
										
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case QUEEN:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkQueen(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == BLACK)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case BISHOP:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkBishop(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == BLACK)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case KNIGHT:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkKnight(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == BLACK)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case ROOK:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkRook(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == BLACK)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case PAWN:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkPawn(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == BLACK)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					}
					if (ans == true)
					{
						return true;
					}
				}
				
				
			}

		}
	}
	return false;

}

bool GameManager::whiteCheck()	//�զ�Q�N�x
{
	bool ans = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)	//�e���for�O���ӽL�����@��
		{
			if (getSquare(i, j)->getColor() != NONE)	//�p�G�o�Ӯ�l���Ѥl
			{
				if (getSquare(i, j)->getColor() == BLACK)	//�ӥB�O�¦�
				{
					//�¦�i�H�Y�զ⪺�����ܴNreturn true
					switch (getSquare(i, j)->getPiece())
					{
					case KING:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)	//�W�����for�O���ӽL�����@��
							{
								if (k == i && m == j)//����ۤv
								{
									continue;
								}
								if (checkKing(getSquare(i, j), getSquare(k, m)))//�p�G�o�Ӧ�l�O���ʦX�k����l
								{
									if (getSquare(k, m)->getPiece() == KING)	//�p�G�o�Ӧ�l�OKING
									{
										if (getSquare(k, m)->getColor() == WHITE)	//�ӥB�O�¦⪺
										{
											ans = true;
										}

									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case QUEEN:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkQueen(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == WHITE)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case BISHOP:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkBishop(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == WHITE)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case KNIGHT:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkKnight(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == WHITE)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case ROOK:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkRook(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == WHITE)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					case PAWN:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)
							{
								if (k == i && m == j)
								{
									continue;
								}
								if (checkPawn(getSquare(i, j), getSquare(k, m)))
								{
									if (getSquare(k, m)->getPiece() == KING)
									{
										if (getSquare(k, m)->getColor() == WHITE)
										{
											ans = true;
										}
									}
								}
							}
						}
						if (ans == true)
						{
							break;
						}
						ans = false;
						break;
					}
					if (ans == true)
					{
						return true;
					}
				}


			}

		}
	}
	return false;

}
bool GameManager::checkKing(Square* thisKing, Square* thatSpace)
{
	if (abs(thatSpace->getX() - thisKing->getX()) <= 1)  //�E�c��X�k
		if (abs(thatSpace->getY() - thisKing->getY()) <= 1)
		{
			return true;
		}
		else return false;
	else return false;
}
bool  GameManager::checkQueen(Square* thisQueen, Square* thatSpace)
{
	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)//����
	{

		if (queenX == thatX)//��V
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)//���V
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))//�צV
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						if (square[queenX + xIncrement * i][queenY + yIncrement * i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
		//if()
	}



	if (invalid == false)
	{

		return true;
	}
	else
	{
		return false;
	}
}
bool  GameManager::checkBishop(Square* thisBishop, Square* thatSpace)
{
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Square* s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			
			if (square[bishopX + xIncrement * i][bishopY + yIncrement * i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		
		return true;
	}
	else
	{
		return false;
	}
}
bool  GameManager::checkKnight(Square* thisKnight, Square* thatSpace)
{
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) //��r���X�k
	{
		
		return true;
	}
	else
	{
		return false;
	}
}
bool GameManager::checkRook(Square* thisRook, Square* thatSpace)
{
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{
		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (invalid == false)  //���� �X�k���� + ����
	{
		return true;
	}
	else  //���� �D�k����
	{//Return some erorr or something. Probably return false;
		
		return false;
	}
}
bool  GameManager::checkPawn(Square* thisPawn, Square* thatSpace)
{
	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();


	if (thisPawn->getColor() == WHITE)//White
	{
		//Initial move
		if (pawnX == 1 && thatX == 3 && pawnY == thatY && thatSpace->getColor() == NONE)
		{
			return true;
		}
		//Y����
		if (pawnY == thatY && thatX == pawnX + 1 && thatSpace->getColor() == NONE)
		{
			return true;
		}
		else
			if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX + 1 == thatX && thatSpace->getColor() == BLACK)
			{
				return true;
			}
			else
				return false;
	}
	else//Black
		if (thisPawn->getColor() == BLACK)
		{
			//Initial move
			if (pawnX == 6 && thatX == 4 && pawnY == thatY && thatSpace->getColor() == NONE)
			{
				return true;
			}
			if (pawnY == thatY && thatX == pawnX - 1 && thatSpace->getColor() == NONE)
			{
				return true;
			}
			else
				if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX - 1 == thatX && thatSpace->getColor() == WHITE)
				{
					return true;
				}
				else
					return false;
		}
		else
			return false;
}