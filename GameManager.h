#pragma once
#include "Player.h"
#include "Viewer.h"
#include <string>
#include <vector>
#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };

enum Color { WHITE, BLACK, NONE };

class Square //棋盤單格 class
{
	Piece piece;  //當格棋子種類
	Color color;  //當格棋子顏色
	int x, y;     //當格旗子座標

public:
	void setSpace(Square*);
	void setEmpty();         //set該格為空格
	void setPieceAndColor(Piece, Color); //設定該格棋子種類 和 顏色
	Piece getPiece();		 //取得該格棋子種類	
	Color getColor();		 //取得該格棋子顏色
	void setX(int ex) { x = ex; }	//set該格的x座標
	void setY(int ey) { y = ey; } //set該格的y座標
	int getX() { return x; }  //取得該格的x座標
	int getY() { return y; }  //取得該格的y座標
	Square();
};

class GameManager
{
public:
	Player* players[2];				//兩名玩家
	Color turn = WHITE;				//現在作動的玩家 default white
	Square square[8][8];			//棋盤
	Viewer viewer;					//輸出
	Player player;
	vector<vector<int> > moveList;	//移動過程
public:
	int round = 0;
	int time = 120;
	bool moveKing(Square* thisKing, Square* thatSpace);
	bool moveQueen(Square* thisQueen, Square* thatSpace);
	bool moveBishop(Square* thisBishop, Square* thatSpace);
	bool moveKnight(Square* thisKnight, Square* thatSpace);
	bool moveRook(Square* thisRook, Square* thatSpace);
	bool movePawn(Square* thisPawn, Square* thatSpace);
	bool makeMove(int x1, int y1, int x2, int y2);
	//↓↓↓  檢查checkMate用的(檢查該格是否移動合法)
	bool checkKing(Square* thisKing, Square* thatSpace);
	bool checkQueen(Square* thisKing, Square* thatSpace);
	bool checkBishop(Square* thisKing, Square* thatSpace);
	bool checkKnight(Square* thisKing, Square* thatSpace);
	bool checkRook(Square* thisKing, Square* thatSpace);
	bool checkPawn(Square* thisKing, Square* thatSpace);

	/*void printBoard();
	void printChosenChessBoard(int x, int y);*/
	void checkPromoting(Square* target);
	bool whiteCheck();	//白色被將軍
	bool blackCheck();	//黑色被將軍
	Square* getSquare(int x, int y) { return &square[x][y]; }
	void setSquare(Square* s, int x, int y)
	{
		square[x][y] = *s;
	}

	bool chooseChessToMove(string chosenChess);

	bool chooseDestinationMoveTo(string chooseDestination);

	bool doMove();

	void drawMoveList(int x1, int y1, int x2, int y2);	//移動列表

	void eraseMoveList();	//移動不合法時使用

	void setBoard();

	bool playGame();

	void choseFirstColor();

	bool loadFile();

	//void clockCountDown();

	void setColor(int color);
};

