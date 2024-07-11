#pragma once
#ifndef BOARD
#define BOARD


#include<iostream>


using namespace std;

enum playerEnum;
class board
{
public:
	int chess[15][15];
	pair<int, int> curpos;

private:

public:
	board();
	board(const board& b);
	board(int chess[][15]);
	void setChess(playerEnum p, pair<int, int> posi);

	bool isWin(playerEnum p, pair<int, int>& pos);
	bool operator==(const board& b);
	board& operator=(const board& b);
	friend ostream& operator<<(ostream& os, const board& b);
	board* reverse();

/*搜索*/
	int abSearch(playerEnum p, int depth, int alpha, int beta, int maxdept);

/*找可能落子点*/
	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);

/*获取最佳点*/
	pair<int, int> policy(playerEnum p);
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]);
	int getScore();
	int getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]);

/*获取棋型和字符串*/
	void getShapes(int* v, int* _v);
	void getShapes4(pair<int, int>& pos, int* v, int* _v);
	int toString(char* strs[]);
	int toString4(char* strs[], pair<int, int>& pos);
	void addShapes(int v[7], int _v[7]);

//VCF
	
};

#endif // !BOARD