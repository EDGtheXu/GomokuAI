#pragma once
#ifndef BOARD
#define BOARD


#include <iostream>
#include <random>
#include "config.h"



using namespace std;
static std::mt19937_64 random(time(NULL));




enum playerEnum;
class board
{
public:
	int chess[15][15];
	pair<int, int> curpos;

private:

public:
	int lastValue;
	int lastRc;
	playerEnum turnToMove;
	playerEnum turnToMoveOppo;


	board();
	board(const board& b);
	board(int chess[][15]);


	bool isWin(playerEnum p, pair<int, int>& pos);
	bool operator==(const board& b);
	board& operator=(const board& b);
	friend ostream& operator<<(ostream& os, const board& b);
	board* reverse();

//搜索
	int abSearch(playerEnum p, int depth, int alpha, int beta, int maxdept);

//找可能落子点
	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);

//获取最佳点
	pair<int, int> policy(playerEnum p);
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]);
	inline int getScore();
	int getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]);

//获取棋型和字符串
	void getShapes(int* v, int* _v);
	inline void getShapes4(pair<int, int>& pos, int* v, int* _v);
	int toString(char* strs[]);
	inline int toString4(char* strs[], pair<int, int>& pos);
	void addShapes(int v[7], int _v[7]);

//VCF


	//置换表
	Pos historyMoves[225];
	int moveCount;
	U64 zobristKey;
	U64 zobrist[2][15][15];

	void initZobrish() {
		for (int i = 0; i < 15; i++) 
			for (int j = 0; j < 15; i++)
				zobrist[0][i][j] = random();

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; i++)
				zobrist[1][i][j] = random();
		zobristKey = random();
	}

	inline void setChess(playerEnum p, Pos pos) {
		this->chess[pos.first][pos.second] = p;

	}
	inline void move(Pos pos) {
		setChess(turnToMove,pos);
		zobristKey ^= zobrist[turnToMove][pos.first][pos.second];
		historyMoves[moveCount] = pos;


		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		moveCount++;
	}
	inline void move(int x,int y) {
		Pos pos(x, y);
		setChess(turnToMove, pos);
		zobristKey ^= zobrist[turnToMove][pos.first][pos.second];
		historyMoves[moveCount] = pos;


		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		moveCount++;
	}


	inline void undo() {
		moveCount--;
		Pos p = historyMoves[moveCount];
		setChess(EMPTY,p);
		zobristKey ^= zobrist[turnToMove][p.first][p.second];

		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;

	}

	
};

#endif // !BOARD