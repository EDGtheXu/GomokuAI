#pragma once
#ifndef BOARD
#define BOARD


#include <iostream>
#include <random>
#include "config.h"
#include "hashTable.h"



using namespace std;
static std::mt19937_64 random(time(NULL));


typedef TTEntrace Move;

enum playerEnum;
class board
{
public:
	int chess[15][15];
	int rchess[15][15];

	//棋型：ME  OPPO
	int shapes[2][7]{0};

	//字符串：行  列  主  副
	char strs[4][29][16] { '0' };

private:

	uint32_t strIndexs[15][15];
	bool terminal = false;

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

	//棋型和字符串变换

	void initStrIndexs() {
		for (uint16_t i = 0;i < 15;i++) {
			for (uint16_t j = 0;j < 15;j++) {

				//行
				uint32_t res = i;

				//列
				res <<= 8;
				res |= j;

				//主
				res <<= 8;
				res |= (i - j + 14);

				//副
				res <<= 8;
				res |= (i + j);

				strIndexs[i][j] = res;

			}
		}
	}

	inline uint32_t getStrIndexs(Pos pos) {
		return strIndexs[pos.first][pos.second];
	}

	inline void changeStr(playerEnum p,Pos pos) {
		uint32_t indexs = getStrIndexs(pos);
		uint8_t x2 = (indexs>>16) & 255;
		uint8_t x1 = (indexs>>24) & 255;

		strs[3][indexs & 255][x1+x2<14?x1:14-x2] = p + '0';
		indexs >>= 8;
		strs[2][indexs & 255][x1>x2?x2:x1] = p + '0';
		indexs >>= 8;
		strs[1][x2][indexs>>8] = p + '0';
		indexs >>= 8;
		strs[0][indexs][x2] = p + '0';
	}

	inline void addMoveShape(Pos pos) {
		int vv[2][7]{ 0 };

		getShapes4(pos, vv);

		for (int i = 0;i < 7;i++) {
			shapes[0][i] += vv[0][i];
			shapes[1][i] += vv[1][i];
		}
	}
	inline void removeMoveShape(Pos pos) {
		int vv[2][7]{ 0 };

		getShapes4(pos, vv);

		for (int i = 0;i < 7;i++) {
			shapes[0][i] -= vv[0][i];
			shapes[1][i] -= vv[1][i];
		}
	}

	inline int* myShapes() {
		return shapes[turnToMoveOppo == ME ? 0 : 1];
	}
	inline int* oppoShape() {
		return shapes[turnToMoveOppo == ME ? 1 : 0];
	}

//搜索
	int abSearch(int depth, int alpha, int beta, int maxdept);

//找可能落子点
	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);


	int genAreaAll(Pos*ps) {
		int mask[15][15]{ 0 };
		for (int i = 0;i < moveCount;i++) {
			Pos& p = historyMoves[i];
			int x = p.first;
			int y = p.second;
			mask[x][y] = -255;
			for (int ii = x - range; ii <= x + range; ii++) {
				for (int jj = y - range; jj <= y + range; jj++) {
					if (ii >= 0 && ii < ROW && jj >= 0 && jj < COL) 
						mask[ii][jj] += 1;
				}
			}
		}
		int count = 0;
		for(int i=0;i<15;i++)
			for (int j = 0;j < 15;j++) {
				if (mask[i][j] > 0) {
					ps[count++] = Pos(i, j);
				}
			}


		return count;
	}


//获取最佳点
	pair<int, int> policy();
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos);
	inline int getScore(); //获取当前player估值
	int getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]);

//获取棋型和字符串
	void getShapes(int* v, int* _v);
	void getShapes4(pair<int, int> pos, int vv[2][7]);


	int toString(char* strs[]);


	void addShapes(int v[7], int _v[7]);

//VCF
	void VCFDefend() {

	}
	void VCFAttack() {

	}
	void genVCFDefendMove() {

	}
	void genVCFAttackMove() {

	}

//置换表
	Pos historyMoves[225];
	int moveCount;
	U64 zobristKey;
	U64 zobrist[2][15][15];

	void initZobrish() {
		for (int i = 0; i < 15; i++) 
			for (int j = 0; j < 15; j++)
				zobrist[0][i][j] = random();

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				zobrist[1][i][j] = random();
		zobristKey = random();
	}

	void save(Pos*ps,int pcount,int v) {
		TTEntrace* tte = new TTEntrace(ps, pcount, v);
		TT.AddItem(zobristKey, tte);
	}



	//移动
	inline void setChess(playerEnum p, Pos pos) {
		chess[pos.first][pos.second] = p;
		rchess[pos.first][pos.second] = -p;
		changeStr(p, pos);
		
	}
	inline void move(Pos pos) {

		removeMoveShape(pos);
		setChess(turnToMove,pos);
		addMoveShape(pos);
		zobristKey ^= zobrist[turnToMove==ME?0:1][pos.first][pos.second];
		historyMoves[moveCount] = pos;


		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		moveCount++;
	}
	inline void move(int x,int y) {
		Pos pos(x, y);
		move(pos);
	}


	inline void undo() {
		moveCount--;
		Pos p = historyMoves[moveCount];

		removeMoveShape(p);
		setChess(EMPTY,p);
		addMoveShape(p);
		zobristKey ^= zobrist[turnToMoveOppo==ME?0:1][p.first][p.second];


		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;

	}

	inline	Pos lastMove() {
		if (moveCount)return historyMoves[moveCount - 1];
		else return Pos(-1, -1);
	}

	
};

#endif // !BOARD