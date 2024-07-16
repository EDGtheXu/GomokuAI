#pragma once
#ifndef BOARD
#define BOARD


#include <iostream>
#include <random>
#include "config.h"
#include "hashTable.h"



using namespace std;
static std::mt19937_64 random(time(NULL));

typedef uint8_t  DIR;
const DIR D[4]{
	1,

};


typedef TTEntrace Move;

enum playerEnum;
class board
{
public:
	int chess[15][15];
	int rchess[15][15];

	//棋型：ME  OPPO
	int shapes[2][SHAPE_TYPES]{0};

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
		int vv[2][SHAPE_TYPES]{ 0 };

		getShapes4(pos, vv);

		for (int i = 0;i < SHAPE_TYPES;i++) {
			shapes[0][i] += vv[0][i];
			shapes[1][i] += vv[1][i];
		}
	}
	inline void removeMoveShape(Pos pos) {
		int vv[2][SHAPE_TYPES]{ 0 };

		getShapes4(pos, vv);

		for (int i = 0;i < SHAPE_TYPES;i++) {
			shapes[0][i] -= vv[0][i];
			shapes[1][i] -= vv[1][i];
		}
	}

	inline int* myShape() {
		return shapes[turnToMove == ME ? 0 : 1];
	}
	inline int* oppoShape() {
		return shapes[turnToMove == ME ? 1 : 0];
	}

//搜索
	int abSearch(int depth, int alpha, int beta, int maxdept);
	int VCFSearch() {

	}

//找可能落子点
	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);


	int genAreaAll(Pos*ps) {//生成所有可能点
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
	void genVCFDefendMove() {//生成 防御活三和冲四

	}
	void genVCFAttackMove() {//生成 进攻活三和冲四

	}
	int quickWinCheck() {//返回 1 win    0 未知     -1 输
		if (myShape()[H4] || myShape()[C4]) {//我方有 活4 冲4 ，可以直接 连5 ， 我方胜
			//cout << *this << endl;
			return true;
		}
		else if (oppoShape()[H4]) {//对方有 活4 ，对方胜
			//cout << *this << endl;
			return false;
		}
		else if (oppoShape()[C4] && oppoShape()[H3]) {//对方 活3 冲4，对方胜
			//cout << *this << endl;
			return false;
		}
		else if ((myShape()[H3] || myShape()[Q3]) && !oppoShape()[C4]) {//我方 有3 且 对方 无冲4， 我方胜

			//cout << *this << endl;
			return true;
		}
		else if (!myShape()[H3] && !myShape()[Q3] && !myShape()[C3] && oppoShape()[H3] + oppoShape()[Q3] > 1) {//我方 无3 且 对方 双3， 对方胜
			//cout << *this << endl;
			return false;
		}
		return 0;
	}

//启发策略
	int LC(Pos* ps, int count) {
		if (count <= 0) return 0;
		int values[150]{ 0 };
		for (int i = 0;i < count;i++) {
			values[i] = -getLC4(ps[i]);

		}
		int min = count > keepLen ? keepLen : count;

		int temp1, temp2, temp3;
		//选择排序
		int i;
		for (i = 0; i < min; i++) {
			int m = values[i];
			int mi = i;
			for (int j = i + 1; j < count; j++) {
				if (values[j] > m) {
					m = values[j];
					mi = j;
				}
			}
			if (m < -10000)
				break;
			if (m > values[i]) {
				temp1 = values[i];
				values[i] = m;
				values[mi] = temp1;

				temp2 = ps[i].first;
				temp3 = ps[i].second;
				ps[i].first = ps[mi].first;
				ps[i].second = ps[mi].second;
				ps[mi].first = temp2;
				ps[mi].second = temp3;
			}

		}

		return i;
	}
	int TTrefresh(Pos* ps, int count, int*values) {//置换表更新
		if (count <= 0) return 0;
#ifdef FULLSEARCH
		int min = count;
#else
		int min = count > keepLen ? keepLen : count;
#endif // FULLSEARCH

		
		int temp1, temp2, temp3;
		//选择排序
		int i;
		for (i = 0; i < min; i++) {
			int m = values[i];
			int mi = i;
			for (int j = i + 1; j < count; j++) {
				if (values[j] > m) {
					m = values[j];
					mi = j;
				}
			}
			if (m < -10000)
				break;
			if (m > values[i]) {
				temp1 = values[i];
				values[i] = m;
				values[mi] = temp1;

				temp2 = ps[i].first;
				temp3 = ps[i].second;
				ps[i].first = ps[mi].first;
				ps[i].second = ps[mi].second;
				ps[mi].first = temp2;
				ps[mi].second = temp3;
			}

		}

		return i;
	}
//获取最佳点
	pair<int, int> policy();
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos);
	inline int getScore(); //获取当前player估值
	inline int getLC4(Pos p) {//获取当前位置的四个方向计算LC

		
		move(p);
		int flag = quickWinCheck();
		
		int res = getScore();
		undo();
		if (flag) return MAX_INT*flag;
		return res;
		

		/*
		int vv[2][SHAPE_TYPES]{ 0 };
		getShapes4(p, vv);
		int res = 0;
		for (int i = 0;i < SHAPE_TYPES;i++) {
			res += vv[0][i];
			res += vv[1][i];
		}
		return res;*/
	}


//获取棋型和字符串
	void getShapes(int* v, int* _v);
	void getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]);

	int toString(char* strs[]);








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
#ifdef DEBUG
		int t = clock();
		movecount++;
#endif // DEBUG

		removeMoveShape(pos);
		setChess(turnToMove,pos);
		addMoveShape(pos);
		zobristKey ^= zobrist[turnToMove==ME?0:1][pos.first][pos.second];
		historyMoves[moveCount] = pos;


		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		moveCount++;

#ifdef DEBUG
		timemove += clock() - t;
#endif // DEBUG

	}
	inline void move(int x,int y) {
		Pos pos(x, y);
		move(pos);
	}


	inline void undo() {
#ifdef DEBUG
		int t = clock();
		movecount++;
#endif // DEBUG
		moveCount--;
		Pos p = historyMoves[moveCount];

		removeMoveShape(p);
		setChess(EMPTY,p);
		addMoveShape(p);
		zobristKey ^= zobrist[turnToMoveOppo==ME?0:1][p.first][p.second];


		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
#ifdef DEBUG
		timemove += clock() - t;
#endif // DEBUG
	}

	inline	Pos lastMove() {
		if (moveCount)return historyMoves[moveCount - 1];
		else return Pos(-1, -1);
	}

	
};

#endif // !BOARD