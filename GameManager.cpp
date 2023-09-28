#include "GameManager.h"

Square::Square()//default constructor
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)//棋子 constructor
{
	color = space->getColor();  //棋子顏色
	piece = space->getPiece();  //棋子種類
}

void Square::setEmpty()//空格 constructor
{
	piece = EMPTY;  //空格 沒棋子種類
	color = NONE;   //空格 沒棋子顏色
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

// 檢查選擇棋子合法性
bool GameManager::chooseChessToMove(const string chosenChess)
{
	int x1, y1;

	if (chosenChess.length() != 2)
	{
		viewer.errorPrint(1);
		//cout << "輸入格式錯誤： 請輸入對應座標軸之 \"2位數字\" 以指定欲移動棋子" << endl;
		return false;
	}
	else if (chosenChess.length() == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (chosenChess[i] < '0' || chosenChess[i]>'9') //輸入的不是數字
			{
				viewer.errorPrint(2);
				//cout << "輸入格式錯誤： 請輸入2位 \"數字\" 以指定欲移動棋子" << endl;
				return false;
			}
		}

		x1 = chosenChess[0] - 48;
		y1 = chosenChess[1] - 48;

		if (x1 < 0 || x1>7 || y1 < 0 || y1>7)
		{
			viewer.errorPrint(3);
			//std::cout << "選擇指令錯誤： 指定格子超出棋盤" << std::endl; //超出棋盤報錯
			return false;
		}


		if (getSquare(x1, y1)->getColor() == turn) //確定該回合下棋者顏色正確
		{
			//是你的棋子
			return true;
		}
		else if (getSquare(x1, y1)->getColor() == NONE) //選定該格沒有棋子
		{
			viewer.errorPrint(4);
			//cout << "選擇指令錯誤： 選定該格沒有棋子" << endl;
			return false;
		}
		else if (getSquare(x1, y1)->getColor() != turn) //選定該格不是你的棋子
		{
			viewer.errorPrint(5);
			//cout << "選擇指令錯誤： 那不是你的棋子，請想好再下" << endl;  //輸出該回合不是你的回合
			return false;
		}
		else
		{
			viewer.errorPrint(6);
			//cout << "選擇指令錯誤： 選定該格未知原因錯誤" << endl;
			return false;
		}
	}
}

// 檢查選擇目的地合法性
bool GameManager::chooseDestinationMoveTo(string chooseDestination)
{
	system("cls");
	viewer.printBoard(this);

	if (chooseDestination.length() != 2)
	{
		viewer.errorPrint(1);
		//cout << "輸入格式錯誤，請輸入 \"2位數字\" 指定欲移動位置" << endl;
		return false;
	}
	else if (chooseDestination.length() == 2)
	{
		for (int i = 0; i < 2; i++)
		{
			if (chooseDestination[i] < '0' || chooseDestination[i]>'9') //輸入的不是數字
			{
				viewer.errorPrint(2);
				//cout << "輸入格式錯誤，請輸入 \"數字\"" << endl;
				return false;
			}
		}

		return true;
	}
}

//檢查 輸入合法 移動合法 (判斷勝利與否)
bool GameManager::doMove()
{
	using namespace std;
	string move;
	string chosenChess, chooseDestination;
	int x1, x2, y1, y2;  //原始x 原始y 後來x 後來y
	bool stop = false;  //輸入合法性
	bool KingDead = false;


	while (!stop) //除非輸入合法  否則需重新輸入
	{
		cout << "===================================================================" << endl << endl;

		(turn == WHITE) ? cout << "現在輪到白色下棋 : " << endl : cout << "現在輪到黑色下棋 : " << endl << endl;  //輸出這回合輪到誰(黑白)

		cout << "選定欲下的旗子，請輸入兩個數字，坐標軸對應為 xy" << endl; //輸入提示 
		cout << "若想投降，請輸入 \"gg\"，返回上一步請輸入 \"regret\"，重回下一步請輸入\"next\"" << endl;

		bool inputOriginChessVaild; //預設指令正確
		bool regretOrNot = false;	//檢測悔棋
		bool regretBroken = false;	//悔棋失敗
		bool nextOrNot = false;	//檢測覆蓋悔棋
		bool nextBroken = false;	//覆蓋悔棋失敗
		bool saveOrNot = false;	//檢查存檔
		// //檢查輸入合法性
		while (player.OnMove(chosenChess))
		{
			system("cls");
			viewer.printBoard(this);
			if (chosenChess == "gg")
			{
				if (turn == WHITE)
				{
					cout << "白棋方投降，本局由黑棋方獲勝 ！！！" << endl; //白色獲勝

					return false; //沒有下一回合 跳出遊戲流程
				}
				else
				{
					cout << "黑棋方投降，本局由白棋方獲勝 ！！！" << endl; //白色獲勝

					return false; //沒有下一回合 跳出遊戲流程
				}
			}

			if (chosenChess == "regret")	//上一步
			{
				if (round < 1)
				{
					cout << "已經沒有上一步了" << endl;
					system("PAUSE");
					regretBroken = true;
					break;
				}
				else
				{
					//要從destination移回original
					Square* destination;
					Square* original;

					//取得目前的destination
					destination = getSquare(moveList[round - 1][2], moveList[round - 1][3]);

					//把destination的內容套用在original上
					original = getSquare(moveList[round - 1][0], moveList[round - 1][1]);
					original->setPieceAndColor(destination->getPiece(), destination->getColor());
					original->setX(moveList[round - 1][0]);
					original->setY(moveList[round - 1][1]);

					//把destination調回動作前的樣子
					Piece destinationPiece;
					Color destinationColor;
					switch (moveList[round - 1][4])	//定義destinationPiece是什麼棋子
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
						cout << "上一步的棋子種類有錯" << endl;
						break;
					}

					switch (moveList[round - 1][5])	//定義destinationColor是什麼顏色
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
						cout << "上一步的棋子顏色有錯" << endl;
						break;
					}


					destination->setPieceAndColor(destinationPiece, destinationColor);	//設定destination原本的棋子
					destination->setX(moveList[round - 1][2]);
					destination->setY(moveList[round - 1][3]);

					regretOrNot = true;
					break;

				}

			}

			if (chosenChess == "next")	//下一步(悔棋之後可以進行)
			{
				if (round < moveList.size())
				{
					makeMove(moveList[round][0], moveList[round][1], moveList[round][2], moveList[round][3]);
					cout << "redo成功，輸入任意鍵以繼續遊戲" << endl;
					nextOrNot = true;
					break;
				}
				else
				{
					cout << "沒有悔棋可以覆蓋" << endl;
					system("PAUSE");
					nextBroken = true;
					break;
				}
			}

			//if (chosenChess == "replay")	//重播到目前的棋子動向
			//{
			//	system("CLS");
			//	GameManager replayBoard;
			//	replayBoard.setBoard();	//初始化棋盤
			//	replayBoard.viewer.printBoard(&replayBoard);	//印出棋盤
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
			//	cout << "播放完成，輸入任意鍵以繼續遊戲" << endl;
			//	continue;
			//}

			if (chosenChess == "replay")	//重播到目前的棋子動向
			{
				system("CLS");
				GameManager replayBoard;
				replayBoard.setBoard();	//初始化棋盤
				replayBoard.viewer.printBoard(&replayBoard);	//印出棋盤
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
				cout << "播放完成，輸入任意鍵以繼續遊戲" << endl;
				continue;
			}

			if (chosenChess == "save")
			{
				fstream saveBoard;
				saveBoard.open("save.txt", ios::trunc | ios::out);
				saveBoard << turn;	//順序
				saveBoard << endl;

				for (int i = 0; i < 8; i++)	//版面
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

				cout << "存檔成功" << endl;
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

		if (regretOrNot)	//如果悔棋
		{
			if (turn == BLACK) //黑色回合結束
			{
				turn = WHITE; //換白色回合
			}
			else              //白色回合結束
			{
				turn = BLACK;   //換黑色回合
			}
			round--;
			return true;
		}
		if (regretBroken)	//悔棋失敗
		{
			return true;
		}
		if (nextOrNot)	//如果覆蓋悔棋
		{
			if (turn == BLACK) //黑色回合結束
			{
				turn = WHITE; //換白色回合
			}
			else              //白色回合結束
			{
				turn = BLACK;   //換黑色回合
			}
			round++;
			return true;
		}
		if (nextBroken)	//覆蓋悔棋失敗
		{
			return true;
		}
		if (saveOrNot)	//存檔成功
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
		cout << "選定(" << x1 << "," << y1 << ")  選定的棋子為： ";
		if (getSquare(x1, y1)->getColor() == 0)
		{
			cout << "\"白色\"";
		}
		else
		{
			cout << "\"黑色\"";
		}
		cout << " 的 ";
		switch (getSquare(x1, y1)->getPiece())
		{
		case 0:
			cout << "\"國王\"" << endl;
			break;
		case 1:
			cout << "\"皇后\"" << endl;
			break;
		case 2:
			cout << "\"主教\"" << endl;
			break;
		case 3:
			cout << "\"騎士\"" << endl;
			break;
		case 4:
			cout << "\"城堡\"" << endl;
			break;
		case 5:
			cout << "\"士兵\"" << endl;
			break;
		case 6:
			cout << "\"空格\"" << endl;
			break;
		default:
			break;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Print 選定旗子提示和可走路徑
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//檢查移動合法性
		while (player.OnMove(chooseDestination))
		{
			bool inputDestinationVaild; //預設指令正確

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

		if (stop == false) //重新輸入選擇棋子
		{
			continue;
		}

		x2 = chooseDestination[0] - 48;
		y2 = chooseDestination[1] - 48;

		if (getSquare(x2, y2)->getPiece() == KING) //移動前先判定目的地是否為對方將軍
		{
			KingDead = true;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		drawMoveList(x1, y1, x2, y2);

		if (makeMove(x1, y1, x2, y2) == false)
		{
			cout << "未成功移動，請重新輸入" << endl; //輸入錯誤 重新輸入
			eraseMoveList();
			stop = false;
			KingDead = false;
			continue;
		}
		else
		{
			stop = true; //輸入正確 檢查勝利條件
			cout << "從(" << x1 << "," << y1 << ")移動至(" << x2 << "," << y2 << ")  移動成功" << endl;
		}

		//system("pause");
	}

	//檢查將死
	if (whiteCheck())
	{
		cout << "!!!!!! 白棋被將軍了 !!!!!!" << endl;
		system("PAUSE");
	}
	if (blackCheck())
	{
		cout << "!!!!!! 黑棋被將軍了 !!!!!!" << endl;
		system("PAUSE");
	}

	if (KingDead)
	{
		system("cls");
		viewer.printBoard(this);
		cout << "===============================================================" << endl;

		if (getSquare(x1, y1)->getColor() == WHITE)
		{
			cout << "黑棋方將軍死亡，恭喜白棋方獲勝 ！！！" << endl; //白色獲勝

			return false; //沒有下一回合 跳出遊戲流程
		}
		else
		{
			cout << "白棋方將軍死亡，恭喜黑棋方獲勝 ！！！" << endl; //黑色獲勝

			return false; //沒有下一回合 跳出遊戲流程
		}
	}

	if (turn == BLACK) //黑色回合結束
	{
		turn = WHITE; //換白色回合
	}
	else              //白色回合結束
	{
		turn = BLACK;   //換黑色回合
	}

	return true; //還有下一回合
}

//================================================================moveList
//新增moveList
void GameManager::drawMoveList(int x1, int y1, int x2, int y2)
{
	vector <int> temp;	//存這回合的移動
	Square* original;
	Square* destination;
	original = getSquare(x1, y1);
	destination = getSquare(x2, y2);
	temp.resize(6);
	temp[0] = x1;
	temp[1] = y1;
	temp[2] = x2;
	temp[3] = y2;
	temp[4] = destination->getPiece();	//紀錄被吃掉的棋子種類
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
//移動不合法的話要刪掉上一個moveList
void GameManager::eraseMoveList()
{
	moveList.pop_back();
	round--;
}

//設置初始棋盤
void GameManager::setBoard()
{
	//初始白色棋子
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[0][1].setPieceAndColor(KNIGHT, WHITE);
	square[0][2].setPieceAndColor(BISHOP, WHITE);
	square[0][3].setPieceAndColor(QUEEN, WHITE);
	square[0][4].setPieceAndColor(KING, WHITE);
	square[0][5].setPieceAndColor(BISHOP, WHITE);
	square[0][6].setPieceAndColor(KNIGHT, WHITE);
	square[0][7].setPieceAndColor(ROOK, WHITE);

	//初始黑色棋子
	square[7][0].setPieceAndColor(ROOK, BLACK);
	square[7][1].setPieceAndColor(KNIGHT, BLACK);
	square[7][2].setPieceAndColor(BISHOP, BLACK);
	square[7][3].setPieceAndColor(QUEEN, BLACK);
	square[7][4].setPieceAndColor(KING, BLACK);
	square[7][5].setPieceAndColor(BISHOP, BLACK);
	square[7][6].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	//初始黑白小兵
	for (int i = 0; i < 8; i++)
	{
		square[1][i].setPieceAndColor(PAWN, WHITE);
		square[6][i].setPieceAndColor(PAWN, BLACK);
	}

	//初始中間空格
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

//每一回合
bool GameManager::playGame()
{
	system("cls");  //清除舊版面
	viewer.printBoard(this);   //印出新版面
	return doMove(); //true 有下一回合
					  //false  沒有下一回合 結束遊戲流程 
}

//檢查移動 King 國王 是否合法  如果合法直接移動
bool GameManager::moveKing(Square* thisKing, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	if (abs(thatSpace->getX() - thisKing->getX()) <= 1)  //九宮格合法
		if (abs(thatSpace->getY() - thisKing->getY()) <= 1)
		{
			thatSpace->setSpace(thisKing); //移動到destination
			thisKing->setEmpty();		   //原格set空格
			return true;
		}
		else return false;
	else return false;
}

//檢查移動 Queen 皇后 是否合法  如果合法直接移動
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
	if (queenX != thatX || queenY != thatY)//有動
	{

		if (queenX == thatX)//橫向
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)//直向
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))//斜向
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

//檢查移動 Bishop 主教 是否合法  如果合法直接移動
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

//檢查移動 Kinght 騎士 是否合法  如果合法直接移動
bool GameManager::moveKnight(Square* thisKnight, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) //日字走合法
	{
		thatSpace->setSpace(thisKnight);  //移動到destination
		thisKnight->setEmpty();			  //原格set空格
		return true;
	}
	else
	{
		return false;
	}
}

//檢查移動 Rook 城堡 是否合法  如果合法直接移動
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
	if (invalid == false)  //城堡 合法移動 + 移動
	{
		thatSpace->setSpace(thisRook); //移動到destination
		thisRook->setEmpty();		   //原格set空格
		return true;
	}
	else  //城堡 非法移動
	{//Return some erorr or something. Probably return false;
		std::cout << "That is an invalid move for rook";
		return false;
	}
}

//檢查移動 Pawn 小兵 是否合法  如果合法直接移動
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
			thatSpace->setSpace(thisPawn);  //移動到destination
			thisPawn->setEmpty();			//原格set空格
			return true;
		}
		//Y不變
		if (pawnY == thatY && thatX == pawnX + 1 && thatSpace->getColor() == NONE)
		{
			thatSpace->setSpace(thisPawn);  //移動到destination
			thisPawn->setEmpty();			//原格set空格
			checkPromoting(thatSpace);
			return true;
		}
		else
			if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX + 1 == thatX && thatSpace->getColor() == BLACK)
			{
				thatSpace->setSpace(thisPawn);  //移動到destination
				thisPawn->setEmpty();			//原格set空格
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
				thatSpace->setSpace(thisPawn);  //移動到destination
				thisPawn->setEmpty();			//原格set空格
				return true;
			}
			if (pawnY == thatY && thatX == pawnX - 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);  //移動到destination
				thisPawn->setEmpty();			//原格set空格
				checkPromoting(thatSpace);
				return true;
			}
			else
				if ((pawnY + 1 == thatY || pawnY - 1 == thatY) && pawnX - 1 == thatX && thatSpace->getColor() == WHITE)
				{
					thatSpace->setSpace(thisPawn);  //移動到destination
					thisPawn->setEmpty();			//原格set空格
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
			cout << "你的士兵到達底線，現在你可以選擇一種升級\n";
			cout << "輸入欲升變之兵種 Q(Queen)/R(Rook)/N(Knight)/B(Bishop):\n";
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
				cout << "Error:不合法的升變或無法辨識的字元，請重新輸入。\n";
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
			cout << "你的士兵到達底線，現在你可以選擇一種升級\n";
			cout << "輸入欲升變之兵種 Q(Queen)/R(Rook)/N(Knight)/B(Bishop):\n";
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
				cout << "Error:不合法的升變或無法辨識的字元，請重新輸入。\n";
				done = false;
				break;
			}
		}
	}

}


//Intent: 確實移動指令  
//Pre: 原始x 原始y 後來x 後來y
//Post: 
bool GameManager::makeMove(int x1, int y1, int x2, int y2)
{
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		std::cout << "移動指令錯誤： 指定格子超出棋盤" << std::endl; //超出棋盤報錯
		return false;
	}

	Square* original = getSquare(x1, y1);
	Square* destination = getSquare(x2, y2);

	if (original->getColor() == destination->getColor() && destination->getColor() != NONE)
	{
		std::cout << "移動指令錯誤： 目標已經有己方棋子" << std::endl; //目標格已經有己方棋子
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
	case EMPTY: std::cout << "指定的格子沒有你的棋子" << std::endl;  return false; //原目標original沒有棋子
		break;
	default: std::cerr << "有錯但不知道原因  Something went wrong in the switch statement in makeMove()" << std::endl; //有錯但不知道原因
		break;
	}
	return false;
}

void GameManager::choseFirstColor()
{
	string color;

	while (1)
	{
		cout << "決定先手方的顏色： 請輸入\"black\" 或 \"white\"" << endl;
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
			cout << "選擇顏色指定錯誤，請重新輸入：" << endl;
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
		cout << "是否要讀檔?  請輸入\"yes\" or \"no\"" << endl;
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
			cout << "選擇讀檔輸入錯誤，請重新輸入：" << endl;
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
		getline(loadFile, tempTurn);	//讀取誰先下
		if (tempTurn == "0")
		{
			turn = WHITE;
		}
		else if (tempTurn == "1")
		{
			turn = BLACK;
		}
		for (int i = 0; i < 8; i++)	//讀取piece
		{
			getline(loadFile, loadString);
			vector <int> temp;
			for (int j = 0; j < 8; j++)	//換成int
			{
				temp.push_back(loadString[j] - '0');
			}
			loadPiece.push_back(temp);
		}
		for (int i = 0; i < 8; i++)
		{
			getline(loadFile, loadString);
			vector <int> temp;
			for (int j = 0; j < 8; j++)	//換成int
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

				switch (loadPiece[i][j])	//讀取該格是什麼棋子
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
					cout << "讀檔的棋子種類有錯" << endl;
					break;
				}
				switch (loadColor[i][j])	//讀取該格是什麼顏色
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
					cout << "讀檔的棋子顏色有錯" << endl;
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
bool GameManager::blackCheck()	//黑色被將軍
{
	bool ans = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)	//前兩個for是把整個盤面掃一次
		{
			if (getSquare(i, j)->getColor() != NONE)	//如果這個格子有棋子
			{
				if (getSquare(i, j)->getColor() == WHITE)	//而且是白色
				{
					//白色可以吃黑色的王的話就return true
					switch (getSquare(i, j)->getPiece())
					{
					case KING:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)	//上面兩個for是把整個盤面掃一次
							{
								if (k == i && m == j)//等於自己
								{
									continue;
								}
								if (checkKing(getSquare(i, j), getSquare(k, m)))//如果這個位子是移動合法的位子
								{
									if (getSquare(k, m)->getPiece() == KING)	//如果這個位子是KING
									{
										if (getSquare(k, m)->getColor() == BLACK)	//而且是黑色的
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

bool GameManager::whiteCheck()	//白色被將軍
{
	bool ans = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)	//前兩個for是把整個盤面掃一次
		{
			if (getSquare(i, j)->getColor() != NONE)	//如果這個格子有棋子
			{
				if (getSquare(i, j)->getColor() == BLACK)	//而且是黑色
				{
					//黑色可以吃白色的王的話就return true
					switch (getSquare(i, j)->getPiece())
					{
					case KING:
						for (int k = 0; k < 8; k++)
						{
							for (int m = 0; m < 8; m++)	//上面兩個for是把整個盤面掃一次
							{
								if (k == i && m == j)//等於自己
								{
									continue;
								}
								if (checkKing(getSquare(i, j), getSquare(k, m)))//如果這個位子是移動合法的位子
								{
									if (getSquare(k, m)->getPiece() == KING)	//如果這個位子是KING
									{
										if (getSquare(k, m)->getColor() == WHITE)	//而且是黑色的
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
	if (abs(thatSpace->getX() - thisKing->getX()) <= 1)  //九宮格合法
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
	if (queenX != thatX || queenY != thatY)//有動
	{

		if (queenX == thatX)//橫向
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)//直向
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))//斜向
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

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) //日字走合法
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
	if (invalid == false)  //城堡 合法移動 + 移動
	{
		return true;
	}
	else  //城堡 非法移動
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
		//Y不變
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