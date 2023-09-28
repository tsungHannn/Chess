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

class Square //�ѽL��� class
{
	Piece piece;  //���Ѥl����
	Color color;  //���Ѥl�C��
	int x, y;     //���X�l�y��

public:
	void setSpace(Square*);
	void setEmpty();         //set�Ӯ欰�Ů�
	void setPieceAndColor(Piece, Color); //�]�w�Ӯ�Ѥl���� �M �C��
	Piece getPiece();		 //���o�Ӯ�Ѥl����	
	Color getColor();		 //���o�Ӯ�Ѥl�C��
	void setX(int ex) { x = ex; }	//set�Ӯ檺x�y��
	void setY(int ey) { y = ey; } //set�Ӯ檺y�y��
	int getX() { return x; }  //���o�Ӯ檺x�y��
	int getY() { return y; }  //���o�Ӯ檺y�y��
	Square();
};

class GameManager
{
public:
	Player* players[2];				//��W���a
	Color turn = WHITE;				//�{�b�@�ʪ����a default white
	Square square[8][8];			//�ѽL
	Viewer viewer;					//��X
	Player player;
	vector<vector<int> > moveList;	//���ʹL�{
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
	//������  �ˬdcheckMate�Ϊ�(�ˬd�Ӯ�O�_���ʦX�k)
	bool checkKing(Square* thisKing, Square* thatSpace);
	bool checkQueen(Square* thisKing, Square* thatSpace);
	bool checkBishop(Square* thisKing, Square* thatSpace);
	bool checkKnight(Square* thisKing, Square* thatSpace);
	bool checkRook(Square* thisKing, Square* thatSpace);
	bool checkPawn(Square* thisKing, Square* thatSpace);

	/*void printBoard();
	void printChosenChessBoard(int x, int y);*/
	void checkPromoting(Square* target);
	bool whiteCheck();	//�զ�Q�N�x
	bool blackCheck();	//�¦�Q�N�x
	Square* getSquare(int x, int y) { return &square[x][y]; }
	void setSquare(Square* s, int x, int y)
	{
		square[x][y] = *s;
	}

	bool chooseChessToMove(string chosenChess);

	bool chooseDestinationMoveTo(string chooseDestination);

	bool doMove();

	void drawMoveList(int x1, int y1, int x2, int y2);	//���ʦC��

	void eraseMoveList();	//���ʤ��X�k�ɨϥ�

	void setBoard();

	bool playGame();

	void choseFirstColor();

	bool loadFile();

	//void clockCountDown();

	void setColor(int color);
};

