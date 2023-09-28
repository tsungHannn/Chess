#include "Viewer.h"
#include "GameManager.h"

//�վ�����C���
void Viewer::SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void Viewer::clockCountDown()
{
	for (int i = 120; i >= 0; i--)
	{
		std::cout << std::to_string(i / 60) << ":" << std::to_string(i % 60) << "\r";
		Sleep(1000);
	}
}

//�L�X�w��ܧ������ʴѤl���ѽL
void Viewer::printChosenChessBoard(GameManager* GM, int x, int y)
{
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7";
	cout << "          ��" << GM->round + 1 << "�^�X      �W�@�B�� ���ʰ_�I              ���ʲ��I" << endl;
	cout << "x:";
	if (GM->round == 0)
	{
		cout << endl;
	}
	else if (GM->round != 0)
	{
		cout << "                                                             ";
		cout << GM->moveList[GM->round - 1][0] << "," << GM->moveList[GM->round - 1][1];
		cout << "                   " << GM->moveList[GM->round - 1][2] << "," << GM->moveList[GM->round - 1][3] << endl;
	}
	
	for (int i = 0; i < 8; i++)
	{
		SetColor();
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			if (i == x && j == y) //�Q�襤���Ѥl
			{
				Piece p = GM->square[i][j].getPiece();
				Color c = GM->square[i][j].getColor();

				switch (p)
				{
				case KING:
					if (c == WHITE)
					{
						SetColor(206);
						
					}
						

					else
						SetColor(192);
					cout << " K ";
					break;
				case QUEEN:
					if (c == WHITE)
						SetColor(206);
					else
						SetColor(192);
					cout << " Q ";
					break;
				case BISHOP:
					if (c == WHITE)
						SetColor(206);
					else
						SetColor(192);
					cout << " B ";
					break;
				case KNIGHT:
					if (c == WHITE)
						SetColor(206);
					else
						SetColor(192);
					cout << " N ";
					break;
				case ROOK:
					if (c == WHITE)
						SetColor(206);
					else
						SetColor(192);
					cout << " R ";
					break;
				case PAWN:
					if (c == WHITE)
					{
						SetColor(206);
						
					}
						
					else
						SetColor(192);
					cout << " P ";
					break;
				default:
					SetColor();
					cout << "XXX";
					break;
				}
			}
			else   //�S�Q��쪺��m
			{
				Piece p = GM->square[i][j].getPiece();
				Color c = GM->square[i][j].getColor();

				switch (p)
				{
				case KING:	//�p�G�o�Ӧ�m�OKING
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(143);
							cout << " K ";*/
							switch (GM->getSquare(x, y)->getPiece())	//�P�_��쪺�O����X�l
							{
							case KING:	//�p�G�����
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))	//�p�G�S�Q��쪺����i�H�Q��쪺�����
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)	//�p�G��쪺�O�¦�
									{
										SetColor(156);	//���C��(�i�Q�Y)
										cout << " K ";
									}
									else	//���i�H�Y�ۤv�H
									{
										SetColor(143);	//�έ쥻���C��
										cout << " K ";
									}
								}
								else  //�S�Q��쪺���椣�i�H�Q��쪺�����
								{
									SetColor(143);	//�쥻���C��
									cout << " K ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(143);
										cout << " K ";
									}
								}
								else
								{
									SetColor(143);
									cout << " K ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(143);
										cout << " K ";
									}
								}
								else
								{
									SetColor(143);
									cout << " K ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(143);
										cout << " K ";
									}
								}
								else
								{
									SetColor(143);
									cout << " K ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(143);
										cout << " K ";
									}
								}
								else
								{
									SetColor(143);
									cout << " K ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(143);
										cout << " K ";
									}
								}
								else
								{
									SetColor(143);
									cout << " K ";
								}
								break;
							}
							
						}
						else //�ծ�
						{
							/*SetColor(127);
							cout << " K ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(127);
										cout << " K ";
									}
								}
								else
								{
									SetColor(127);
									cout << " K ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{

									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(127);
										cout << " K ";
									}
								}
								else
								{
									SetColor(127);
									cout << " K ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{

									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(127);
										cout << " K ";
									}
								}
								else
								{
									SetColor(127);
									cout << " K ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{

									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(127);
										cout << " K ";
									}
								}
								else
								{
									SetColor(127);
									cout << " K ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{

									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(127);
										cout << " K ";
									}
								}
								else
								{
									SetColor(127);
									cout << " K ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{

									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(127);
										cout << " K ";
									}
								}
								else
								{
									SetColor(127);
									cout << " K ";
								}
								break;
							}
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(128);
							cout << " K ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{

									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(128);
										cout << " K ";
									}
								}
								else
								{
									SetColor(128);
									cout << " K ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(128);
										cout << " K ";
									}
								}
								else
								{
									SetColor(128);
									cout << " K ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(128);
										cout << " K ";
									}
								}
								else
								{
									SetColor(128);
									cout << " K ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(128);
										cout << " K ";
									}
								}
								else
								{
									SetColor(128);
									cout << " K ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(128);
										cout << " K ";
									}
								}
								else
								{
									SetColor(128);
									cout << " K ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(128);
										cout << " K ";
									}
								}
								else
								{
									SetColor(128);
									cout << " K ";
								}
								break;
							}
						}
						else //�ծ�
						{
							/*SetColor(112);
							cout << " K ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(112);
										cout << " K ";
									}
								}
								else
								{
									SetColor(112);
									cout << " K ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(112);
										cout << " K ";
									}
								}
								else
								{
									SetColor(112);
									cout << " K ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(112);
										cout << " K ";
									}
								}
								else
								{
									SetColor(112);
									cout << " K ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(112);
										cout << " K ";
									}
								}
								else
								{
									SetColor(112);
									cout << " K ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(112);
										cout << " K ";
									}
								}
								else
								{
									SetColor(112);
									cout << " K ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " K ";
									}
									else
									{
										SetColor(112);
										cout << " K ";
									}
								}
								else
								{
									SetColor(112);
									cout << " K ";
								}
								break;
							}
						}
					}

					break;
				case QUEEN:
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(143);
							cout << " Q ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(143);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(143);
									cout << " Q ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(143);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(143);
									cout << " Q ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(143);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(143);
									cout << " Q ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(143);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(143);
									cout << " Q ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(143);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(143);
									cout << " Q ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(143);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(143);
									cout << " Q ";
								}
								break;
							}
						}
						else  //�ծ�
						{
							/*SetColor(127);
							cout << " Q ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(127);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(127);
									cout << " Q ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(127);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(127);
									cout << " Q ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(127);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(127);
									cout << " Q ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(127);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(127);
									cout << " Q ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(127);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(127);
									cout << " Q ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(127);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(127);
									cout << " Q ";
								}
								break;
							}
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(128);
							cout << " Q ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(128);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(128);
									cout << " Q ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(128);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(128);
									cout << " Q ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										if (GM->getSquare(x, y)->getColor() == WHITE)
										{
											SetColor(156);
											cout << " Q ";
										}
										else
										{
											SetColor(128);
											cout << " Q ";
										}
									}
									else
									{
										SetColor(128);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(128);
									cout << " Q ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(128);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(128);
									cout << " Q ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(128);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(128);
									cout << " Q ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(128);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(128);
									cout << " Q ";
								}
								break;
							}
						}
						else  //�ծ�
						{
							/*SetColor(112);
							cout << " Q ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(112);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(112);
									cout << " Q ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(112);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(112);
									cout << " Q ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(112);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(112);
									cout << " Q ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(112);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(112);
									cout << " Q ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(112);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(112);
									cout << " Q ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " Q ";
									}
									else
									{
										SetColor(112);
										cout << " Q ";
									}
								}
								else
								{
									SetColor(112);
									cout << " Q ";
								}
								break;
							}
						}
					}

					break;
				case BISHOP:
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(143);
							cout << " B ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(143);
										cout << " B ";
									}
								}
								else
								{
									SetColor(143);
									cout << " B ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(143);
										cout << " B ";
									}
								}
								else
								{
									SetColor(143);
									cout << " B ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(143);
										cout << " B ";
									}
								}
								else
								{
									SetColor(143);
									cout << " B ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(143);
										cout << " B ";
									}
								}
								else
								{
									SetColor(143);
									cout << " B ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(143);
										cout << " B ";
									}
								}
								else
								{
									SetColor(143);
									cout << " B ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(143);
										cout << " B ";
									}
								}
								else
								{
									SetColor(143);
									cout << " B ";
								}
								break;
							}
						}
						else  //�ծ�
						{
							/*SetColor(127);
							cout << " B ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(127);
										cout << " B ";
									}
								}
								else
								{
									SetColor(127);
									cout << " B ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(127);
										cout << " B ";
									}
								}
								else
								{
									SetColor(127);
									cout << " B ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(127);
										cout << " B ";
									}
								}
								else
								{
									SetColor(127);
									cout << " B ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(127);
										cout << " B ";
									}
								}
								else
								{
									SetColor(127);
									cout << " B ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(127);
										cout << " B ";
									}
								}
								else
								{
									SetColor(127);
									cout << " B ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(127);
										cout << " B ";
									}
								}
								else
								{
									SetColor(127);
									cout << " B ";
								}
								break;
							}
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(128);
							cout << " B ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(128);
										cout << " B ";
									}
								}
								else
								{
									SetColor(128);
									cout << " B ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(128);
										cout << " B ";
									}
								}
								else
								{
									SetColor(128);
									cout << " B ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(128);
										cout << " B ";
									}
								}
								else
								{
									SetColor(128);
									cout << " B ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(128);
										cout << " B ";
									}
								}
								else
								{
									SetColor(128);
									cout << " B ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(128);
										cout << " B ";
									}
								}
								else
								{
									SetColor(128);
									cout << " B ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(128);
										cout << " B ";
									}
								}
								else
								{
									SetColor(128);
									cout << " B ";
								}
								break;
							}
						}
						else  //�ծ�
						{
							/*SetColor(112);
							cout << " B ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(112);
										cout << " B ";
									}
								}
								else
								{
									SetColor(112);
									cout << " B ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(112);
										cout << " B ";
									}
								}
								else
								{
									SetColor(112);
									cout << " B ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(112);
										cout << " B ";
									}
								}
								else
								{
									SetColor(112);
									cout << " B ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(112);
										cout << " B ";
									}
								}
								else
								{
									SetColor(112);
									cout << " B ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(112);
										cout << " B ";
									}
								}
								else
								{
									SetColor(112);
									cout << " B ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " B ";
									}
									else
									{
										SetColor(112);
										cout << " B ";
									}
								}
								else
								{
									SetColor(112);
									cout << " B ";
								}
								break;
							}
						}
					}

					break;
				case KNIGHT:
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(143);
							cout << " N ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(143);
										cout << " N ";
									}
								}
								else
								{
									SetColor(143);
									cout << " N ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(143);
										cout << " N ";
									}
								}
								else
								{
									SetColor(143);
									cout << " N ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(143);
										cout << " N ";
									}
								}
								else
								{
									SetColor(143);
									cout << " N ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(143);
										cout << " N ";
									}
								}
								else
								{
									SetColor(143);
									cout << " N ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(143);
										cout << " N ";
									}
								}
								else
								{
									SetColor(143);
									cout << " N ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(143);
										cout << " N ";
									}
								}
								else
								{
									SetColor(143);
									cout << " N ";
								}
								break;
							}
						}
						else  //�ծ�
						{
						/*	SetColor(127);
							cout << " N ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(127);
										cout << " N ";
									}
								}
								else
								{
									SetColor(127);
									cout << " N ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(127);
										cout << " N ";
									}
								}
								else
								{
									SetColor(127);
									cout << " N ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(127);
										cout << " N ";
									}
								}
								else
								{
									SetColor(127);
									cout << " N ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(127);
										cout << " N ";
									}
								}
								else
								{
									SetColor(127);
									cout << " N ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(127);
										cout << " N ";
									}
								}
								else
								{
									SetColor(127);
									cout << " N ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(127);
										cout << " N ";
									}
								}
								else
								{
									SetColor(127);
									cout << " N ";
								}
								break;
							}
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(128);
							cout << " N ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(128);
										cout << " N ";
									}
								}
								else
								{
									SetColor(128);
									cout << " N ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(128);
										cout << " N ";
									}
								}
								else
								{
									SetColor(128);
									cout << " N ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(128);
										cout << " N ";
									}
								}
								else
								{
									SetColor(128);
									cout << " N ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(128);
										cout << " N ";
									}
								}
								else
								{
									SetColor(128);
									cout << " N ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(128);
										cout << " N ";
									}
								}
								else
								{
									SetColor(128);
									cout << " N ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(128);
										cout << " N ";
									}
								}
								else
								{
									SetColor(128);
									cout << " N ";
								}
								break;
							}
						}
						else //�ծ�
						{
							/*SetColor(112);
							cout << " N ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(112);
										cout << " N ";
									}
								}
								else
								{
									SetColor(112);
									cout << " N ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(112);
										cout << " N ";
									}
								}
								else
								{
									SetColor(112);
									cout << " N ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(112);
										cout << " N ";
									}
								}
								else
								{
									SetColor(112);
									cout << " N ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(112);
										cout << " N ";
									}
								}
								else
								{
									SetColor(112);
									cout << " N ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(112);
										cout << " N ";
									}
								}
								else
								{
									SetColor(112);
									cout << " N ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " N ";
									}
									else
									{
										SetColor(112);
										cout << " N ";
									}
								}
								else
								{
									SetColor(112);
									cout << " N ";
								}
								break;
							}
						}
					}

					break;
				case ROOK:
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(143);
							cout << " R ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(143);
										cout << " R ";
									}
								}
								else
								{
									SetColor(143);
									cout << " R ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(143);
										cout << " R ";
									}
								}
								else
								{
									SetColor(143);
									cout << " R ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(143);
										cout << " R ";
									}
								}
								else
								{
									SetColor(143);
									cout << " R ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(143);
										cout << " R ";
									}
								}
								else
								{
									SetColor(143);
									cout << " R ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(143);
										cout << " R ";
									}
								}
								else
								{
									SetColor(143);
									cout << " R ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(143);
										cout << " R ";
									}
								}
								else
								{
									SetColor(143);
									cout << " R ";
								}
								break;
							}

						}
						else  //�ծ�
						{
							/*SetColor(127);
							cout << " R ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(127);
										cout << " R ";
									}
								}
								else
								{
									SetColor(127);
									cout << " R ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(127);
										cout << " R ";
									}
								}
								else
								{
									SetColor(127);
									cout << " R ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(127);
										cout << " R ";
									}
								}
								else
								{
									SetColor(127);
									cout << " R ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(127);
										cout << " R ";
									}
								}
								else
								{
									SetColor(127);
									cout << " R ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(127);
										cout << " R ";
									}
								}
								else
								{
									SetColor(127);
									cout << " R ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(127);
										cout << " R ";
									}
								}
								else
								{
									SetColor(127);
									cout << " R ";
								}
								break;
							}
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(128);
							cout << " R ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(128);
										cout << " R ";
									}
								}
								else
								{
									SetColor(128);
									cout << " R ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(128);
										cout << " R ";
									}
								}
								else
								{
									SetColor(128);
									cout << " R ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(128);
										cout << " R ";
									}
								}
								else
								{
									SetColor(128);
									cout << " R ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(128);
										cout << " R ";
									}
								}
								else
								{
									SetColor(128);
									cout << " R ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(128);
										cout << " R ";
									}
								}
								else
								{
									SetColor(128);
									cout << " R ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(128);
										cout << " R ";
									}
								}
								else
								{
									SetColor(128);
									cout << " R ";
								}
								break;
							}
						}
						else //�ծ�
						{
							/*SetColor(112);
							cout << " R ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(112);
										cout << " R ";
									}
								}
								else
								{
									SetColor(112);
									cout << " R ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(112);
										cout << " R ";
									}
								}
								else
								{
									SetColor(112);
									cout << " R ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(112);
										cout << " R ";
									}
								}
								else
								{
									SetColor(112);
									cout << " R ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(112);
										cout << " R ";
									}
								}
								else
								{
									SetColor(112);
									cout << " R ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(112);
										cout << " R ";
									}
								}
								else
								{
									SetColor(112);
									cout << " R ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " R ";
									}
									else
									{
										SetColor(112);
										cout << " R ";
									}
								}
								else
								{
									SetColor(112);
									cout << " R ";
								}
								break;
							}
						}
					}

					break;
				case PAWN:
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(143);
							cout << " P ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(143);
										cout << " P ";
									}
									
								}
								else
								{
									SetColor(143);
									cout << " P ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(143);
										cout << " P ";
									}
								}
								else
								{
									SetColor(143);
									cout << " P ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(143);
										cout << " P ";
									}
								}
								else
								{
									SetColor(143);
									cout << " P ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(143);
										cout << " P ";
									}
								}
								else
								{
									SetColor(143);
									cout << " P ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(143);
										cout << " P ";
									}
								}
								else
								{
									SetColor(143);
									cout << " P ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(143);
										cout << " P ";
									}
								}
								else
								{
									SetColor(143);
									cout << " P ";
								}
								break;
							}
						}
						else  //�ծ�
						{
							/*SetColor(127);
							cout << " P ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(127);
										cout << " P ";
									}
								}
								else
								{
									SetColor(127);
									cout << " P ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(127);
										cout << " P ";
									}
								}
								else
								{
									SetColor(127);
									cout << " P ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(127);
										cout << " P ";
									}
								}
								else
								{
									SetColor(127);
									cout << " P ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(127);
										cout << " P ";
									}
								}
								else
								{
									SetColor(127);
									cout << " P ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(127);
										cout << " P ";
									}
								}
								else
								{
									SetColor(127);
									cout << " P ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(127);
										cout << " P ";
									}
								}
								else
								{
									SetColor(127);
									cout << " P ";
								}
								break;
							}
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(128);
							cout << " P ";*/

							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(128);
										cout << " P ";
									}
								}
								else
								{
									SetColor(128);
									cout << " P ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(128);
										cout << " P ";
									}
								}
								else
								{
									SetColor(128);
									cout << " P ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(128);
										cout << " P ";
									}
								}
								else
								{
									SetColor(128);
									cout << " P ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(128);
										cout << " P ";
									}
								}
								else
								{
									SetColor(128);
									cout << " P ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(128);
										cout << " P ";
									}
								}
								else
								{
									SetColor(128);
									cout << " P ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(128);
										cout << " P ";
									}
								}
								else
								{
									SetColor(128);
									cout << " P ";
								}
								break;
							}
						}
						else  //�ծ�
						{
							/*SetColor(112);
							cout << " P ";*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(112);
										cout << " P ";
									}
								}
								else
								{
									SetColor(112);
									cout << " P ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(112);
										cout << " P ";
									}
								}
								else
								{
									SetColor(112);
									cout << " P ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(112);
										cout << " P ";
									}
								}
								else
								{
									SetColor(112);
									cout << " P ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(112);
										cout << " P ";
									}
								}
								else
								{
									SetColor(112);
									cout << " P ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(112);
										cout << " P ";
									}
								}
								else
								{
									SetColor(112);
									cout << " P ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									if (GM->getSquare(x, y)->getColor() == WHITE)
									{
										SetColor(156);
										cout << " P ";
									}
									else
									{
										SetColor(112);
										cout << " P ";
									}
								}
								else
								{
									SetColor(112);
									cout << " P ";
								}
								break;
							}

						}
					}
					break;
				case EMPTY:
					//�ڥ��Τ���
					if (c == WHITE) //�մ�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							SetColor(136);
							cout << "   ";
						}
						else  //�ծ�
						{
							SetColor(119);
							cout << "   ";
						}
					}
					else  //�´�
					{
						if ((i + j) % 2 == 0) //�®�
						{
							/*SetColor(136);
							cout << "   ";*/

							/*if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
							{


								SetColor(239);
								cout << "   ";

							}
							else
							{
								SetColor(136);
								cout << "   ";
							}*/
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(136);
									cout << "   ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(136);
									cout << "   ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(136);
									cout << "   ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(136);
									cout << "   ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(136);
									cout << "   ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(136);
									cout << "   ";
								}
								break;
							}


						}
						else  //�ծ�
						{
							//=============
							switch (GM->getSquare(x, y)->getPiece())
							{
							case KING:
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(119);
									cout << "   ";
								}
								break;
							case QUEEN:
								if (GM->checkQueen(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(119);
									cout << "   ";
								}
								break;
							case BISHOP:
								if (GM->checkBishop(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(119);
									cout << "   ";
								}
								break;
							case KNIGHT:
								if (GM->checkKnight(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(119);
									cout << "   ";
								}
								break;
							case ROOK:
								if (GM->checkRook(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(119);
									cout << "   ";
								}
								break;
							case PAWN:
								if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
								{
									SetColor(239);
									cout << "   ";
								}
								else
								{
									SetColor(119);
									cout << "   ";
								}
								break;
							}
							/*if (GM->checkPawn(GM->getSquare(x, y), GM->getSquare(i, j)))
							{


								SetColor(239);
								cout << "   ";

							}
							else
							{
								SetColor(119);
								cout << "   ";
							}*/
						}
					}
					break;

				default:
					SetColor();
					cout << "XXX";
					break;
				}
			}
		}
		cout << endl;
	}
	cout << endl;
	SetColor();
}

//�L�X�ѽL
void Viewer::printBoard(GameManager* GM)
{
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7";
	cout << "          ��" << GM->round + 1 << "�^�X      �W�@�B�� ���ʰ_�I              ���ʲ��I" << endl;
	cout << "x:";
	if (GM->round == 0)
	{
		cout << endl;
	}
	else if (GM->round != 0)
	{
		cout << "                                                             ";
		cout << GM->moveList[GM->round - 1][0] << "," << GM->moveList[GM->round - 1][1];
		cout << "                   " << GM->moveList[GM->round - 1][2] << "," << GM->moveList[GM->round - 1][3] << endl;
	}

	for (int i = 0; i < 8; i++)
	{
		SetColor();
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = GM->square[i][j].getPiece();
			Color c = GM->square[i][j].getColor();

			switch (p)
			{
			case KING:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(143);
						cout << " K ";
					}
					else //�ծ�
					{
						SetColor(127);
						cout << " K ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(128);
						cout << " K ";
					}
					else //�ծ�
					{
						SetColor(112);
						cout << " K ";
					}
				}

				break;
			case QUEEN:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(143);
						cout << " Q ";
					}
					else  //�ծ�
					{
						SetColor(127);
						cout << " Q ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(128);
						cout << " Q ";
					}
					else  //�ծ�
					{
						SetColor(112);
						cout << " Q ";
					}
				}

				break;
			case BISHOP:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(143);
						cout << " B ";
					}
					else  //�ծ�
					{
						SetColor(127);
						cout << " B ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(128);
						cout << " B ";
					}
					else  //�ծ�
					{
						SetColor(112);
						cout << " B ";
					}
				}

				break;
			case KNIGHT:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(143);
						cout << " N ";
					}
					else  //�ծ�
					{
						SetColor(127);
						cout << " N ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(128);
						cout << " N ";
					}
					else //�ծ�
					{
						SetColor(112);
						cout << " N ";
					}
				}

				break;
			case ROOK:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(143);
						cout << " R ";
					}
					else  //�ծ�
					{
						SetColor(127);
						cout << " R ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(128);
						cout << " R ";
					}
					else //�ծ�
					{
						SetColor(112);
						cout << " R ";
					}
				}

				break;
			case PAWN:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(143);
						cout << " P ";
					}
					else  //�ծ�
					{
						SetColor(127);
						cout << " P ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(128);
						cout << " P ";
					}
					else  //�ծ�
					{
						SetColor(112);
						cout << " P ";
					}
				}
				break;
			case EMPTY:
				if (c == WHITE) //�մ�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(136);
						cout << "   ";
					}
					else  //�ծ�
					{
						SetColor(119);
						cout << "   ";
					}
				}
				else  //�´�
				{
					if ((i + j) % 2 == 0) //�®�
					{
						SetColor(136);
						cout << "   ";
					}
					else  //�ծ�
					{
						SetColor(119);
						cout << "   ";
					}
				}
				break;

			default:
				SetColor();
				cout << "XXX";
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
	SetColor();
}