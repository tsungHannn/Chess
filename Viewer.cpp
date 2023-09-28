#include "Viewer.h"
#include "GameManager.h"

//調整顯示顏色用
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

//印出已選擇完欲移動棋子的棋盤
void Viewer::printChosenChessBoard(GameManager* GM, int x, int y)
{
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7";
	cout << "          第" << GM->round + 1 << "回合      上一步的 移動起點              移動終點" << endl;
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
			if (i == x && j == y) //被選中的棋子
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
			else   //沒被選到的位置
			{
				Piece p = GM->square[i][j].getPiece();
				Color c = GM->square[i][j].getColor();

				switch (p)
				{
				case KING:	//如果這個位置是KING
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
						{
							/*SetColor(143);
							cout << " K ";*/
							switch (GM->getSquare(x, y)->getPiece())	//判斷選到的是什麼旗子
							{
							case KING:	//如果選到國王
								if (GM->checkKing(GM->getSquare(x, y), GM->getSquare(i, j)))	//如果沒被選到的那格可以被選到的國王走
								{
									if (GM->getSquare(x, y)->getColor() == BLACK)	//如果選到的是黑色
									{
										SetColor(156);	//換顏色(可被吃)
										cout << " K ";
									}
									else	//不可以吃自己人
									{
										SetColor(143);	//用原本的顏色
										cout << " K ";
									}
								}
								else  //沒被選到的那格不可以被選到的國王走
								{
									SetColor(143);	//原本的顏色
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
						else //白格
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
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else //白格
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
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else //白格
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
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else //白格
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
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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
					//根本用不到
					if (c == WHITE) //白棋
					{
						if ((i + j) % 2 == 0) //黑格
						{
							SetColor(136);
							cout << "   ";
						}
						else  //白格
						{
							SetColor(119);
							cout << "   ";
						}
					}
					else  //黑棋
					{
						if ((i + j) % 2 == 0) //黑格
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
						else  //白格
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

//印出棋盤
void Viewer::printBoard(GameManager* GM)
{
	using namespace std;
	cout << "   y: 0  1  2  3  4  5  6  7";
	cout << "          第" << GM->round + 1 << "回合      上一步的 移動起點              移動終點" << endl;
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
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(143);
						cout << " K ";
					}
					else //白格
					{
						SetColor(127);
						cout << " K ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(128);
						cout << " K ";
					}
					else //白格
					{
						SetColor(112);
						cout << " K ";
					}
				}

				break;
			case QUEEN:
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(143);
						cout << " Q ";
					}
					else  //白格
					{
						SetColor(127);
						cout << " Q ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(128);
						cout << " Q ";
					}
					else  //白格
					{
						SetColor(112);
						cout << " Q ";
					}
				}

				break;
			case BISHOP:
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(143);
						cout << " B ";
					}
					else  //白格
					{
						SetColor(127);
						cout << " B ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(128);
						cout << " B ";
					}
					else  //白格
					{
						SetColor(112);
						cout << " B ";
					}
				}

				break;
			case KNIGHT:
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(143);
						cout << " N ";
					}
					else  //白格
					{
						SetColor(127);
						cout << " N ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(128);
						cout << " N ";
					}
					else //白格
					{
						SetColor(112);
						cout << " N ";
					}
				}

				break;
			case ROOK:
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(143);
						cout << " R ";
					}
					else  //白格
					{
						SetColor(127);
						cout << " R ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(128);
						cout << " R ";
					}
					else //白格
					{
						SetColor(112);
						cout << " R ";
					}
				}

				break;
			case PAWN:
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(143);
						cout << " P ";
					}
					else  //白格
					{
						SetColor(127);
						cout << " P ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(128);
						cout << " P ";
					}
					else  //白格
					{
						SetColor(112);
						cout << " P ";
					}
				}
				break;
			case EMPTY:
				if (c == WHITE) //白棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(136);
						cout << "   ";
					}
					else  //白格
					{
						SetColor(119);
						cout << "   ";
					}
				}
				else  //黑棋
				{
					if ((i + j) % 2 == 0) //黑格
					{
						SetColor(136);
						cout << "   ";
					}
					else  //白格
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