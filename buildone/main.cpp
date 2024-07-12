
/*** Start of inlined file: config.cpp ***/

/*** Start of inlined file: config.h ***/
#pragma once
#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <time.h>
#include <vector>
#include<cstring>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY

using namespace std;
extern int MAX_DEPTH;
extern int keepLen;
extern int range;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;

extern int step_INIT;
extern int MAX_DEPTH_INIT;
extern int keepLen_INIT;
extern int range_INIT;

extern int step_FINA;
extern int MAX_DEPTH_FINA;
extern int keepLen_FINA;
extern int range_FINA;

extern int skeepLen;
extern int TIMEBEGIN;
extern const int COL;
extern const int ROW;
extern const int MAX_INT;
extern const int MIN_INT;
extern const int MAX_SEARCH_TIME_MS;
extern const int VALUE_DEFAULT[7];
extern const int VALUE_DEFAULT_OPPO[7];
extern const int VALUE_MUST_WIN;

extern int time1;
extern int tos4count;
extern int toscount;
extern int timescore4;
extern int timescore;
extern int timepos;
extern int timepos1;
extern int timetos;
extern int timetos4;
extern int timetemp;


extern int reachMaxDepth;
extern int searchNode;

extern const vector<string> shaps_win;
extern const vector<string> shaps_huo4;
extern const vector<string> shaps_huo3;
extern const vector<string> shaps_chong3;
extern const vector<string> shaps_huo2;
extern const vector<string> shaps_ming2;
extern const vector<string> shaps_huo1;

extern const vector<string> _shaps_huo4_oppo;
extern const vector<string> _shaps_chong4_oppo;
extern const vector<string> _shaps_huo3;
extern const vector<string> _shaps_chong3;
extern const vector<string> _shaps_huo2;
extern const vector<string> _shaps_ming2;
extern const vector<string> _shaps_huo1;

enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

#endif
/*** End of inlined file: config.h ***/

int MAX_DEPTH = 4;
int keepLen = 20;
int range = 2;
int MAX_VCT_DEPTH = 4;
int MAX_VCF_DEPTH = 11;

int step_INIT = 4;
int MAX_DEPTH_INIT = 4;
int keepLen_INIT = 13;
int range_INIT = 3;

int step_FINA = 40;
int MAX_DEPTH_FINA = 5;
int keepLen_FINA = 20;
int range_FINA = 2;

int skeepLen = 3;
int TIMEBEGIN = 0;
const int COL = 15;
const int ROW = 15;
const int MAX_INT = 0x3f3f3f3f;
const int MIN_INT = -MAX_INT;
const int MAX_SEARCH_TIME_MS = 0.95 * CLOCKS_PER_SEC;
const int VALUE_DEFAULT[7]{ MAX_INT / 1000          ,	  MAX_INT / 2000     ,      2000      ,      600   ,       600     ,     150       ,     150 };
const int VALUE_DEFAULT_OPPO[7]{ MIN_INT / 10000         ,    -2000              ,     -1000       ,     -400   ,      -400      ,    -100       ,    -100 };
const int VALUE_MUST_WIN = -100000;

int time1;
int tos4count = 0;
int toscount = 0;
int timescore4 = 0;
int timescore = 0;
int timepos = 0;
int timepos1 = 0;
int timetos = 0;
int timetos4 = 0;
int timetemp = 0;

int reachMaxDepth = 0;
int searchNode = 0;

const vector<string> shaps_win = { "11111" };
const vector<string> shaps_huo4 = { "011110","10111","11011","11101","11110","01111" };
const vector<string> shaps_huo3 = { "011100","001110","011010","010110" };
const vector<string> shaps_chong3 = { "11100","11010","11001","10110","10101","10011",   "00111","01011","10011","01101","10101","11001",   "01110" };
const vector<string> shaps_huo2 = { "01100","00110","01010","010010" };
const vector<string> shaps_ming2 = { "11000","10100","10010","10001",  "00011","00101","01001","10001" };
const vector<string> shaps_huo1 = { "00100" };

//进攻
//const vector<string> _shaps_win = { "/////" };
//const vector<string> _shaps_huo4 = { "0////0","/0///","//0//","///0/","////0" };
//防守
const vector<string> _shaps_huo4_oppo = { "/0///0/","//0//0//","///0/0///", "0////0","/////" };
const vector<string> _shaps_chong4_oppo = { "////0","0////","///0/","//0//","/0///","///0/" ,"///0/","/0///" };
//公用
const vector<string> _shaps_huo3 = { "0///00","00///0","0//0/0","0/0//0" };
const vector<string> _shaps_chong3 = { "///00","//0/0","//00/","/0//0","/0/0/","/00//",   "00///","0/0//","/00//","0//0/","/0/0/","//00/",   "0///0" };
const vector<string> _shaps_huo2 = { "00//0","0//00","0/0/0","0/00/0" };
const vector<string> _shaps_ming2 = { "//000","/0/00","/00/0","/000/",  "000//","00/0/","0/00/","/000/" };
const vector<string> _shaps_huo1 = { "00/00" };


/*** End of inlined file: config.cpp ***/


/*** Start of inlined file: board.cpp ***/

/*** Start of inlined file: board.h ***/
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

	int abSearch(playerEnum p, int depth, int alpha, int beta, int maxdept);

	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);

	pair<int, int> policy(playerEnum p);
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]);
	int getScore();
	int getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]);

	void getShapes(int* v, int* _v);
	void getShapes4(pair<int, int>& pos, int* v, int* _v);
	int toString(char* strs[]);
	int toString4(char* strs[], pair<int, int>& pos);
	void addShapes(int v[7], int _v[7]);

};

#endif
/*** End of inlined file: board.h ***/


/*** Start of inlined file: config.h ***/
#pragma once
#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <time.h>
#include <vector>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY

using namespace std;
extern int MAX_DEPTH;
extern int keepLen;
extern int range;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;

extern int step_INIT;
extern int MAX_DEPTH_INIT;
extern int keepLen_INIT;
extern int range_INIT;

extern int step_FINA;
extern int MAX_DEPTH_FINA;
extern int keepLen_FINA;
extern int range_FINA;

extern int skeepLen;
extern int TIMEBEGIN;
extern const int COL;
extern const int ROW;
extern const int MAX_INT;
extern const int MIN_INT;
extern const int MAX_SEARCH_TIME_MS;
extern const int VALUE_DEFAULT[7];
extern const int VALUE_DEFAULT_OPPO[7];
extern const int VALUE_MUST_WIN;

extern int time1;
extern int tos4count;
extern int toscount;
extern int timescore4;
extern int timescore;
extern int timepos;
extern int timepos1;
extern int timetos;
extern int timetos4;
extern int timetemp;

extern int reachMaxDepth;
extern int searchNode;

extern const vector<string> shaps_win;
extern const vector<string> shaps_huo4;
extern const vector<string> shaps_huo3;
extern const vector<string> shaps_chong3;
extern const vector<string> shaps_huo2;
extern const vector<string> shaps_ming2;
extern const vector<string> shaps_huo1;

extern const vector<string> _shaps_huo4_oppo;
extern const vector<string> _shaps_chong4_oppo;
extern const vector<string> _shaps_huo3;
extern const vector<string> _shaps_chong3;
extern const vector<string> _shaps_huo2;
extern const vector<string> _shaps_ming2;
extern const vector<string> _shaps_huo1;

enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

#endif
/*** End of inlined file: config.h ***/


/*** Start of inlined file: evaluate.h ***/
#pragma once

#ifndef EVALUATE
#define EVALUATE

#include<vector>
#include<string>
using namespace std;

class strTree {
public:
	char c;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(char* str, int v[7]);

	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);

	static int readTree(strTree* root, char* strs[], int count, int v[7]);
	static void initRoots();
	static int getScoreG(int* v, int* _v);

	~strTree();
};

extern strTree* tree1;
extern strTree* tree2;

#endif
/*** End of inlined file: evaluate.h ***/

board::board()
{
	memset(chess, EMPTY, sizeof(chess));
	curpos = pair<int, int>(8, 8);
}
board::board(const board& b)
{
	memcpy(chess, b.chess, sizeof(chess));
}
board::board(int chess[][15]) {
	memcpy(this->chess, chess, sizeof(this->chess));
}

ostream& operator<<(ostream& os, const board& b)
{
	os << "---0-1-2-3-4-5-6-7-8-9-0-1-2-3-4-" << endl;
	for (int i = 0; i < ROW; i++) {
		os.left;
		os.width(2);
		os << i % 10;
		for (int j = 0; j < COL; j++) {
			if (b.chess[j][i] == 1) {

				os << "|O";
			}
			else if (b.chess[j][i] == -1) {
				os.left;

				os << "|X";
			}
			else
			{
				os << "| ";
			}

		}
		os << '|' << endl;
	}
	os << "---------------------------------" << endl;
	return os;
}
bool board::isWin(playerEnum p, pair<int, int>& pos)
{
	int x = pos.first;
	int y = pos.second;

	int count = 0;
	for (int j = 0; j < COL; j++) {
		if (chess[x][j] == p) {
			count++;
		}
		else {
			count = 0;
		}
		if (count == 5) {
			return true;
		}
	}

	count = 0;
	for (int i = 0; i < ROW; i++) {
		if (chess[i][y] == p) {
			count++;
		}
		else {
			count = 0;
		}
		if (count == 5) {
			return true;
		}
	}

	for (int i = (y - x > 0 ? 0 : x - y); i < ROW; i++) {
		count = 0;
		for (int k = 0; k < 5; k++) {

			if (i + y - x + k >= ROW || i + k >= ROW) break;
			if (chess[i + k][i + y - x + k] == p) {
				count++;
			}
			else {
				count = 0;
			}
			if (count == 5) {
				return true;
			}
		}

	}

	for (int i = (x + y >= ROW ? x + y - 14 : 0); i < ROW; i++) {
		count = 0;
		for (int k = 0; k < 5; k++) {
			if (x + y - i - k >= ROW || i + k >= ROW)break;
			if (chess[i + k][x + y - i - k] == p) {
				count++;
			}
			else {
				count = 0;
			}
			if (count == 5) {
				return true;
			}
		}
	}

	return false;
}
board* board::reverse()
{
#ifdef DEBUG_main
	time_t tt = clock();
#endif
	board* res = new board(*this);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			res->chess[i][j] *= -1;
		}
	}
#ifdef DEBUG_main
	time1 += clock() - tt;
#endif
	return res;
}
int board::getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w) {
#ifdef DEBUG_main
	int t = clock();
#endif
	int sortv[150]{ 0 };
	int index = 0;

	int nb[15][15]{ 0 };
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (chess[i][j] != 0) {
				for (int ii = i - range; ii <= i + range; ii++) {
					for (int jj = j - range; jj <= j + range; jj++) {
						if (ii >= 0 && ii < ROW && jj >= 0 && jj < COL) nb[ii][jj] += 1;
					}
				}
			}
		}
	}
	board* nbb = new board(*this);
	board* nbb2 = nbb->reverse();
	board* curb = nullptr;

	int v0[7]{ 0 };
	int _v0[7]{ 0 };
	if (p == 1) {
		nbb2->getShapes(v0, _v0);
		curb = nbb2;
	}
	else {
		nbb->getShapes(v0, _v0);
		curb = nbb;
	}

	if (_v0[0] || _v0[1]) {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (!chess[i][j] && nb[i][j]) {
					pair<int, int> np = pair<int, int>(i, j);
					curb->chess[i][j] = playerEnum::OPPO;
					if (curb->isWin(playerEnum::OPPO, np)) {
						*w = 1;
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					curb->chess[i][j] = 0;
				}
			}
		}
	}
	if (v0[1]) {
		int count = 0;
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (!chess[i][j] && nb[i][j]) {
					pair<int, int> np = pair<int, int>(i, j);
					curb->chess[i][j] = playerEnum::ME;

					if (curb->isWin(playerEnum::ME, np)) {
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					curb->chess[i][j] = 0;
				}
			}
		}
	}

#ifdef DEBUG_main
	timetemp += clock() - t;
#endif

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (!chess[i][j] && nb[i][j]) {
				pair<int, int> np = pair<int, int>(i, j);

				/*
				nbb->chess[i][j] = p;
				if (nbb->isWin(p,np)) {
					res[0] = np;
					delete nbb;
					delete nbb2;
					return 1;
				}
				nbb->chess[i][j] = 0;
				*/
				int value;
				if (p == 1) {

					value = nbb2->getScoreP(np, v0, _v0);

					if (value < -100000) {
						/*cout << "pos:" << i << ' ' << j << endl;
						nbb2->chess[i][j] = -1;
						cout << *nbb2 << endl;*/
						*w = 1;
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					else if (value < 100000) {
						sortv[index] = value;
						res[index++] = np;
					}
				}
				else {

					value = nbb->getScoreP(np, v0, _v0);

					if (value < -100000) {
						/*cout << "pos:" << i << ' ' << j << endl;
						nbb->chess[i][j] = -1;
						cout << *nbb << endl;*/
						*w = 1;
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					else if (value < 100000) {
						sortv[index] = value;
						res[index++] = np;
					}
				}

#ifdef DEBUG_POSS
				cout << "pos:" << i << ' ' << j << endl;
				nbb->chess[i][j] = p;
				cout << *nbb << endl;
				nbb->chess[i][j] = 0;
				cout << "dept=" << depth << endl;
				cout << "pos=" << np.first << " " << np.second << endl;
				cout << "value=" << value << endl;
#endif

			}
		}
	}

	int temp1, temp2, temp3;
	int min = index > keepLen ? keepLen : index;

	if (index > 0) {
		for (int i = 0; i < min; i++) {
			int m = sortv[i];
			int mi = i;
			for (int j = i + 1; j < index; j++) {
				if (sortv[j] < m) {
					m = sortv[j];
					mi = j;
				}
			}
			if (m < sortv[i]) {
				temp1 = sortv[i];
				sortv[i] = m;
				sortv[mi] = temp1;

				temp2 = res[i].first;
				temp3 = res[i].second;
				res[i].first = res[mi].first;
				res[i].second = res[mi].second;
				res[mi].first = temp2;
				res[mi].second = temp3;
			}

		}
	}

	/*	if (index > 0) {
		for (int i = index-2; i > 0; i--) {
			for (int j = i; j >= 0; j--) {
				if (sortv[j] > sortv[j + 1]
					) {

					temp1 = sortv[j];
					sortv[j + 1] = temp1;
					sortv[j] = temp1;

					temp2 = res[j].first;
					temp3 = res[j].second;
					res[j].first = res[j + 1].first;
					res[j].second = res[j + 1].second;
					res[j + 1].first = temp2;
					res[j + 1].second = temp3;

				}
			}
		}
	}

	*/
#ifdef DEBUG_main

	timepos += clock() - t;
#endif
	return min;
}
int board::getAllPossiblePos0(playerEnum p, int depth, pair<int, int>* res, int* w) {
#ifdef DEBUG_main
	int t = clock();
#endif
	int sortv[150]{ 0 };
	int index = 0;

	int nb[15][15]{ 0 };
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (chess[i][j] != 0) {
				for (int ii = i - range; ii <= i + range; ii++) {
					for (int jj = j - range; jj <= j + range; jj++) {
						if (ii >= 0 && ii < ROW && jj >= 0 && jj < COL) nb[ii][jj] += 1;
					}
				}
			}
		}
	}
	board* nbb = new board(*this);
	board* nbb2 = nbb->reverse();
	board* curb = nullptr;

	int v0[7]{ 0 };
	int _v0[7]{ 0 };
	if (p == 1) {
		nbb2->getShapes(v0, _v0);
		curb = nbb2;
	}
	else {
		nbb->getShapes(v0, _v0);
		curb = nbb;
	}

	if (_v0[0] || _v0[1]) {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (!chess[i][j] && nb[i][j]) {
					pair<int, int> np = pair<int, int>(i, j);
					curb->chess[i][j] = playerEnum::OPPO;
					if (curb->isWin(playerEnum::OPPO, np)) {
						*w = 1;
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					curb->chess[i][j] = 0;
				}
			}
		}
	}
#ifdef DEBUG_main
	timetemp += clock() - t;
#endif

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (!chess[i][j] && nb[i][j]) {
				pair<int, int> np = pair<int, int>(i, j);

				/*
				nbb->chess[i][j] = p;
				if (nbb->isWin(p,np)) {
					res[0] = np;
					delete nbb;
					delete nbb2;
					return 1;
				}
				nbb->chess[i][j] = 0;
				*/
				int value;
				if (p == 1) {

					value = nbb2->getScoreP(np, v0, _v0);

					if (value < -100000) {
						/*cout << "pos:" << i << ' ' << j << endl;
						nbb2->chess[i][j] = -1;
						cout << *nbb2 << endl;*/
						*w = 1;
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					else if (value < 100000) {
						sortv[index] = value;
						res[index++] = np;
					}
				}
				else {

					value = nbb->getScoreP(np, v0, _v0);

					if (value < -100000) {
						/*cout << "pos:" << i << ' ' << j << endl;
						nbb->chess[i][j] = -1;
						cout << *nbb << endl;*/
						*w = 1;
						res[0] = np;
						delete nbb;
						delete nbb2;
						return 1;
					}
					else if (value < 100000) {
						sortv[index] = value;
						res[index++] = np;
					}
				}

#ifdef DEBUG_POSS
				cout << "pos:" << i << ' ' << j << endl;
				nbb->chess[i][j] = p;
				cout << *nbb << endl;
				nbb->chess[i][j] = 0;
				cout << "dept=" << depth << endl;
				cout << "pos=" << np.first << " " << np.second << endl;
				cout << "value=" << value << endl;
#endif

			}
		}
	}

	int temp1, temp2, temp3;

	if (index > 0) {
		for (int i = 0; i < index; i++) {
			int m = sortv[i];
			int mi = i;
			for (int j = i + 1; j < index; j++) {
				if (sortv[j] < m) {
					m = sortv[j];
					mi = j;
				}
			}
			if (m < sortv[i]) {
				temp1 = sortv[i];
				sortv[i] = m;
				sortv[mi] = temp1;

				temp2 = res[i].first;
				temp3 = res[i].second;
				res[i].first = res[mi].first;
				res[i].second = res[mi].second;
				res[mi].first = temp2;
				res[mi].second = temp3;
			}

		}
	}

	/*	if (index > 0) {
		for (int i = index-2; i > 0; i--) {
			for (int j = i; j >= 0; j--) {
				if (sortv[j] > sortv[j + 1]
					) {

					temp1 = sortv[j];
					sortv[j + 1] = temp1;
					sortv[j] = temp1;

					temp2 = res[j].first;
					temp3 = res[j].second;
					res[j].first = res[j + 1].first;
					res[j].second = res[j + 1].second;
					res[j + 1].first = temp2;
					res[j + 1].second = temp3;

				}
			}
		}
	}

	*/
#ifdef DEBUG_main

	timepos += clock() - t;
#endif
	return index;
}
int board::getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res) {
#ifdef DEBUG_main
	int t = clock();
#endif
	int count = 0;

	int nb[15][15]{ 0 };
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (chess[i][j] != 0) {
				for (int ii = i - range; ii <= i + range; ii++) {
					for (int jj = j - range; jj <= j + range; jj++) {
						if (ii >= 0 && ii < ROW && jj >= 0 && jj < COL) nb[ii][jj] += 1;
					}
				}
			}
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (!chess[i][j] && nb[i][j]) {
				pair<int, int> np = pair<int, int>(i, j);
				res[count++] = np;
			}
		}
	}

#ifdef DEBUG_main
	timepos1 += clock() - t;
#endif
	return count;
}

int board::toString(char* strs[]) {
#ifdef DEBUG_main
	toscount++;
	int t = clock();
#endif
	int count = 0;
	int index = 0;

	char bs[15][15]{ 0 };
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			bs[i][j] = chess[i][j] + '0';

	for (int i = 0; i < ROW; i++) {
		bool save = false;
		char str[16]{ 0 };
		index = 0;
		for (int j = 0; j < COL; j++) {
			str[index++] = bs[i][j];
			if (bs[i][j] != '0') save = true;
		}
		if (save) {
			char* nstr = new char[index] { 0 };
			memcpy(nstr, str, index);
			nstr[index] = 0;
			strs[count++] = nstr;
		}
	}
	for (int i = 0; i < COL; i++) {
		bool save = false;
		char str[16]{ 0 };
		index = 0;
		for (int j = 0; j < ROW; j++) {
			str[index++] = bs[j][i];
			if (bs[j][i] != '0') save = true;
		}
		if (save) {
			char* nstr = new char[index] { 0 };
			memcpy(nstr, str, index);
			nstr[index] = 0;
			strs[count++] = nstr;
		}
	}
	for (int i = COL - 1; i > 0; i--) {
		bool save = false;
		char str[16]{ 0 };
		index = 0;
		for (int j = 0; j < COL; j++) {
			if (j + i >= COL)break;
			str[index++] = bs[j][j + i];
			if (bs[j][j + i] != '0') save = true;
		}
		if (save) {
			char* nstr = new char[index] { 0 };
			memcpy(nstr, str, index);
			nstr[index] = 0;
			strs[count++] = nstr;
		}
	}
	for (int i = 0; i < COL; i++) {
		bool save = false;
		char str[16]{ 0 };
		index = 0;
		for (int j = 0; j < COL; j++) {
			if (j + i >= COL)break;
			str[index++] = bs[j + i][j];
			if (bs[j + i][j] != '0') save = true;
		}
		if (save) {
			char* nstr = new char[index] { 0 };
			memcpy(nstr, str, index);
			nstr[index] = 0;
			strs[count++] = nstr;
		}
	}
	for (int i = 0; i < COL; i++) {
		bool save = false;
		char str[16]{ 0 };
		index = 0;
		for (int j = 0; j < COL; j++) {
			if (i - j < 0)break;
			str[index++] = bs[j][i - j];
			if (bs[j][i - j] != '0') save = true;
		}
		if (save) {
			char* nstr = new char[index] { 0 };
			memcpy(nstr, str, index);
			nstr[index] = 0;
			strs[count++] = nstr;
		}
	}
	for (int i = 1; i < COL; i++) {
		bool save = false;
		char str[16]{ 0 };
		index = 0;
		for (int j = 0; j < COL; j++) {
			if (i + j >= COL)break;
			str[index++] = bs[COL - j - 1][i + j];
			if (bs[COL - j - 1][i + j] != '0') save = true;
		}
		if (save) {
			char* nstr = new char[index] { 0 };
			memcpy(nstr, str, index);
			nstr[index] = 0;
			strs[count++] = nstr;
		}
	}

	int _count = count;

	while (count--) {
		int en = strlen(strs[count]) - 1;
		int c = 0;
		while (strs[count][en--] == '0') c++;
		if (c >= skeepLen) {
			strs[count][en + 2 + skeepLen] = 0;
		}

		int st = 0;
		while (strs[count][st] == '0') st++;
		if (st >= skeepLen) {
			strs[count] = strs[count] + st - skeepLen;
		}

	}

#ifdef DEBUG_main
	timetos += clock() - t;
#endif
	return _count;
}

int board::toString4(char* strs[], pair<int, int>& pos) {
#ifdef DEBUG_main
	time_t t = clock();
#endif
	tos4count++;

	int x = pos.first;
	int y = pos.second;

	char* s1 = new char[16]{ 0 };
	char* s2 = new char[16]{ 0 };
	char* s3 = new char[16]{ 0 };
	char* s4 = new char[16]{ 0 };

	int index = 0;
	for (int i = 0; i < ROW; i++) {
		s1[index++] = chess[x][i] + '0';
	}

	index = 0;
	for (int i = 0; i < ROW; i++) {
		s2[index++] = chess[i][y] + '0';
	}

	index = 0;
	for (int i = (y - x > 0 ? 0 : x - y); i < ROW; i++) {
		if (i + y - x >= 15)break;
		s3[index++] = chess[i][i + y - x] + '0';
	}

	index = 0;
	for (int i = (x + y >= ROW ? x + y - 14 : 0); i < ROW; i++) {
		if (x + y - i < 0)break;
		s4[index++] = chess[i][x + y - i] + '0';
	}
	strs[0] = s1;
	strs[1] = s2;
	strs[2] = s3;
	strs[3] = s4;

#ifdef DEBUG_main
	timetos4 += clock() - t;
#endif
	return 4;
}

int board::abSearch(playerEnum p, int depth, int alpha, int beta, int maxdept)
{
#ifdef DEBUG_ABS
	cout << *this << endl;
#endif
#ifdef DEBUG
	reachMaxDepth = max(reachMaxDepth, maxdept);
	searchNode++;
#endif

	if (depth == maxdept - 1) {

		if (depth % 2 == 0) {
			pair<int, int>poss[150];
			int w = 0;
			int count = getAllPossiblePos(p, depth, poss, &w);
			if (w) return (int)p * MAX_INT;

			if (count <= 6 && depth <= MAX_VCT_DEPTH ||
				count == 1 && depth <= MAX_VCF_DEPTH
				) {
				int max = MIN_INT;
				int rc = 0;
				while (count--)
				{
					chess[poss[rc].first][poss[rc].second] = p;

					int t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept + 2);
					chess[poss[rc].first][poss[rc].second] = 0;
					max = t > max ? t : max; alpha = max > alpha ? max : alpha;
					if (alpha >= beta) {
						return max;
					}
					rc++;
				}
				return max;
			}
			else {
				board* nbb = this->reverse();
				int v0[7]{ 0 };
				int _v0[7]{ 0 };
				nbb->getShapes(v0, _v0);
				int max = MIN_INT;
				int rc = 0;
				while (count--) {

					nbb->chess[poss[rc].first][poss[rc].second] = -(int)p;
					chess[poss[rc].first][poss[rc].second] = p;
					if (isWin(p, poss[rc])) { this->chess[poss[rc].first][poss[rc].second] = 0; return ((int)p) * MAX_INT; }

					int t;

					int v[7]{ 0 };
					int _v[7]{ 0 };
					getShapes4(poss[rc], v, _v);
					if (_v[1] && depth <= MAX_VCT_DEPTH) {
						t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept + 1);
						nbb->chess[poss[rc].first][poss[rc].second] = 0;
						chess[poss[rc].first][poss[rc].second] = 0;
					}
					else {
						nbb->chess[poss[rc].first][poss[rc].second] = 0;
						chess[poss[rc].first][poss[rc].second] = 0;
						t = -nbb->getScoreP(poss[rc], v0, _v0);
					}

					max = t > max ? t : max; alpha = max > alpha ? max : alpha;
					if (alpha >= beta) {
						return max;
					}
					rc++;
				}
				return max;
			}

		}
		else {
			pair<int, int>poss[150];
			int w = 0;
			int count = getAllPossiblePos(p, depth, poss, &w);
			if (w) return (int)p * MAX_INT;
			if (count <= 6 && depth <= MAX_VCT_DEPTH ||
				count == 1 && depth <= MAX_VCF_DEPTH
				) {
				int rc = 0;
				int min = MAX_INT;
				while (count--) {
					chess[poss[rc].first][poss[rc].second] = p;
					int t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept + 2);
					chess[poss[rc].first][poss[rc].second] = 0;

					min = t < min ? t : min;
					beta = min < beta ? min : beta;
					if (beta <= alpha) {

						return min;
					}
					rc++;
				}
				return min;

			}
			else {
				int v0[7]{ 0 };
				int _v0[7]{ 0 };
				getShapes(v0, _v0);

				int min = MAX_INT;
				int rc = 0;
				while (count--) {
					chess[poss[rc].first][poss[rc].second] = p;
					if (isWin(p, poss[rc])) { this->chess[poss[rc].first][poss[rc].second] = 0; return ((int)p) * MAX_INT; }

					int t;
					int v[7]{ 0 };
					int _v[7]{ 0 };
					getShapes4(poss[rc], v, _v);
					if (_v[1] && depth <= MAX_VCT_DEPTH) {
						t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept + 1);
						chess[poss[rc].first][poss[rc].second] = 0;
					}
					else {
						chess[poss[rc].first][poss[rc].second] = 0;
						t = getScoreP(poss[rc], v0, _v0);
					}

					min = t < min ? t : min;
					beta = min < beta ? min : beta;
					if (beta <= alpha) {

						return min;
					}
					rc++;
				}
				return min;
			}
		}
	}

	int w = 0;
	pair<int, int>poss[150];
	int count = getAllPossiblePos(p, depth, poss, &w);

	if (w == 1)
		return (int)p * MAX_INT;
	if (count == 0)
		if (p == 1)return MIN_INT;
		else return MAX_INT;

	int rc = 0;
	if (p == 1) {
		int max = MIN_INT;
		while (count--) {
			this->chess[poss[rc].first][poss[rc].second] = p;

			int t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept);

			this->chess[poss[rc].first][poss[rc].second] = 0;
			max = t > max ? t : max; alpha = max > alpha ? max : alpha;
			if (alpha >= beta) {
				return max;
			}
			rc++;

#ifdef TIME_CONTROL
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) break;
#endif
		}
		return max;
	}
	else {
		int min = MAX_INT;
		while (count--) {

			this->chess[poss[rc].first][poss[rc].second] = p;

			int t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept);

			this->chess[poss[rc].first][poss[rc].second] = 0;
			min = t < min ? t : min;
			beta = min < beta ? min : beta;
			if (beta <= alpha) {

				return min;
			}
			rc++;

#ifdef TIME_CONTROL
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) break;
#endif
		}
		return min;
	}

	return 0;
}

pair<int, int> board::policy(playerEnum p)
{
	strTree::initRoots();
	int* w = new int(0);
	pair<int, int> poss[150];
	int count = getAllPossiblePos(p, 0, poss, w);
	if (*w) return poss[0];
	else if (count == 0) {

		return lose();
	}

	int curmax = MIN_INT;
	pair<int, int> best = poss[0];

	int maxv = -MIN_INT * 2;

	int rc = 0;
	range = 1;	while (count--) {

#ifdef DEBUG_POLICY
		int steptime = clock();
#endif

		this->chess[poss[rc].first][poss[rc].second] = p;

#ifdef DEBUG_POLICY
		int x = poss[rc].first;
		int y = poss[rc].second;
		cout << *this << endl;
		cout << "pol:" << x << ' ' << y << endl;
#endif
		int t = abSearch((playerEnum)(-(int)p), 1, curmax, MAX_INT, MAX_DEPTH);
		this->chess[poss[rc].first][poss[rc].second] = 0;

#ifdef DEBUG_POLICY
		cout << "step time:" << clock() - steptime << endl;
#endif 
#ifdef TIME_CONTROL
		if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) break;
#endif

		if (t > curmax)
		{
			curmax = t;
			best = poss[rc];
			maxv = t;
		}
		rc++;
	}
#ifdef DEBUG_POLICY
	cout << "maxv = " << curmax << endl;
	cout << "rc = " << rc << endl;
#endif
	delete tree1;
	delete tree2;
	return best;
}

void board::getShapes(int* v, int* _v) {
	char* strs[88]{ 0 };
	int count = toString(strs);
	strTree::readTree(tree1, strs, count, v);
	strTree::readTree(tree2, strs, count, _v);

}

void board::getShapes4(pair<int, int>& pos, int* v, int* _v) {
	char* strs[4]{ 0 };
	toString4(strs, pos);
	strTree::readTree(tree1, strs, 4, v);
	strTree::readTree(tree2, strs, 4, _v);
}

int board::getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]) {
#ifdef DEBUG_main
	int t = clock();
#endif
	/*
		int v0[7]{ 0 };
	int _v0[7]{ 0 };
	getShapes(v0, _v0);
	*/

	int v[7]{ 0 };
	int _v[7]{ 0 };
	getShapes4(pos, v, _v);

	chess[pos.first][pos.second] = -1;

	int v2[7]{ 0 };
	int _v2[7]{ 0 };
	getShapes4(pos, v2, _v2);

	chess[pos.first][pos.second] = 0;
	int change3 = _v2[2] - _v[2];

	int change4 = _v2[1] - _v[1];

	int change34 = v[3] + v[4] - _v2[4] - v2[3];
	int v3[7]{ 0 };
	int _v3[7]{ 0 };

	for (int i = 0; i < 7; i++) {
		v3[i] = v0[i] - v[i] + v2[i];
		_v3[i] = _v0[i] - _v[i] + _v2[i];
	}

	if (v3[0] || v3[1]) { /*cout << "7=l5/;/3" << pos.first << ',' << pos.second << endl;
	cout << *this << endl;*/
		return MAX_INT / 2;
	}
	else if (_v3[0]) {
		return MIN_INT / 10;
	}
	else if ((change3 + change4) > 1 && (change4)) {
		if ((!v3[2]) && (!v3[3])) return MIN_INT;
		return -50000;

	}
	else if (v3[2] && (!_v3[1])) {
		return MAX_INT / 2;
	}
	else if ((change3 > 1)) {
		if ((!v3[3])) return MIN_INT / 10;
		/*	cout << "6苑=双;
" << pos.first << ',' << pos.second << endl;
			cout << *this << endl; */
		return -50000;
	}
	int score = strTree::getScoreG(v3, _v3);
	if (change34 > 1) score -= 6666;
	return score;
}

int board::getScore() {
#ifdef DEBUG_main
	int t = clock();
#endif
	int v[7]{ 0 };
	int _v[7]{ 0 };
	getShapes(v, _v);

	return strTree::getScoreG(v, _v);
}

int board::getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]) {
#ifdef DEBUG_main
	int t = clock();
#endif
	/*
		int v0[7]{ 0 };
	int _v0[7]{ 0 };
	getShapes(v0, _v0);
	*/

	int v[7]{ 0 };
	int _v[7]{ 0 };
	getShapes4(pos, v, _v);

	chess[pos.first][pos.second] = -1;

	int v2[7]{ 0 };
	int _v2[7]{ 0 };
	getShapes4(pos, v2, _v2);

	chess[pos.first][pos.second] = 0;
	int change3 = _v2[2] - _v[2];

	int change4 = _v2[1] - _v[1];

	int change34 = v[3] + v[4] - _v2[4] - _v2[3];
	int v3[7]{ 0 };
	int _v3[7]{ 0 };

	for (int i = 0; i < 7; i++) {
		v3[i] = v0[i] - v[i] + v2[i];
		_v3[i] = _v0[i] - _v[i] + _v2[i];
	}

	int score = 0;

	if (v3[0] || v3[1]) { /*cout << "7=l5/;/3" << pos.first << ',' << pos.second << endl;
	cout << *this << endl;*/
		score += MAX_INT / 2;
	}
	else if (_v3[0]) {
		score += MIN_INT / 10;
	}
	else if ((change3 + change4) > 1 && (change4)) {
		if ((!v3[2]) && (!v3[3])) score += MIN_INT;
		score -= 50000;

	}
	else if (v3[2] && (!_v3[1])) {
		score += MAX_INT / 2;
	}
	else if ((change3 > 1)) {
		if ((!v3[3])) score += MIN_INT / 10;
		/*	cout << "6苑=双;
" << pos.first << ',' << pos.second << endl;
			cout << *this << endl; */
		score -= 50000;
	}
	score += strTree::getScoreG(v3, _v3);
	if (change34 > 1) score -= 6666;
	return score;
}

pair<int, int> board::lose() {
	int sortv[150]{ 0 };
	int index = 0;

	int nb[15][15]{ 0 };
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (chess[i][j] != 0) {
				for (int ii = i - range; ii <= i + range; ii++) {
					for (int jj = j - range; jj <= j + range; jj++) {
						if (ii >= 0 && ii < ROW && jj >= 0 && jj < COL) nb[ii][jj] += 1;
					}
				}
			}
		}
	}
	int best = MAX_INT;
	board* nbb2 = this->reverse();
	pair<int, int> pos = pair<int, int>(0, 0);
	int v0[7]{ 0 };
	int _v0[7]{ 0 };
	nbb2->getShapes(v0, _v0);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (!chess[i][j] && nb[i][j]) {
				pair<int, int> np = pair<int, int>(i, j);

				/*
				nbb->chess[i][j] = p;
				if (nbb->isWin(p,np)) {
					res[0] = np;
					delete nbb;
					delete nbb2;
					return 1;
				}
				nbb->chess[i][j] = 0;
				*/
				int value;
				value = nbb2->getScoreLose(np, v0, _v0);
				if (value < best) {
					pos = pair<int, int>(i, j);
					best = value;
				}
			}
		}
	}
	return pos;
}
/*** End of inlined file: board.cpp ***/


/*** Start of inlined file: evaluate.cpp ***/

/*** Start of inlined file: evaluate.h ***/
#pragma once

#ifndef EVALUATE
#define EVALUATE

#include<vector>
#include<string>
using namespace std;

class strTree {
public:
	char c;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(char* str, int v[7]);

	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);

	static int readTree(strTree* root, char* strs[], int count, int v[7]);
	static void initRoots();
	static int getScoreG(int* v, int* _v);

	~strTree();
};

extern strTree* tree1;
extern strTree* tree2;

#endif
/*** End of inlined file: evaluate.h ***/


/*** Start of inlined file: config.h ***/
#pragma once
#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <time.h>
#include <vector>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY

using namespace std;
extern int MAX_DEPTH;
extern int keepLen;
extern int range;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;

extern int step_INIT;
extern int MAX_DEPTH_INIT;
extern int keepLen_INIT;
extern int range_INIT;

extern int step_FINA;
extern int MAX_DEPTH_FINA;
extern int keepLen_FINA;
extern int range_FINA;

extern int skeepLen;
extern int TIMEBEGIN;
extern const int COL;
extern const int ROW;
extern const int MAX_INT;
extern const int MIN_INT;
extern const int MAX_SEARCH_TIME_MS;
extern const int VALUE_DEFAULT[7];
extern const int VALUE_DEFAULT_OPPO[7];
extern const int VALUE_MUST_WIN;

extern int time1;
extern int tos4count;
extern int toscount;
extern int timescore4;
extern int timescore;
extern int timepos;
extern int timepos1;
extern int timetos;
extern int timetos4;
extern int timetemp;

extern int reachMaxDepth;
extern int searchNode;

extern const vector<string> shaps_win;
extern const vector<string> shaps_huo4;
extern const vector<string> shaps_huo3;
extern const vector<string> shaps_chong3;
extern const vector<string> shaps_huo2;
extern const vector<string> shaps_ming2;
extern const vector<string> shaps_huo1;

extern const vector<string> _shaps_huo4_oppo;
extern const vector<string> _shaps_chong4_oppo;
extern const vector<string> _shaps_huo3;
extern const vector<string> _shaps_chong3;
extern const vector<string> _shaps_huo2;
extern const vector<string> _shaps_ming2;
extern const vector<string> _shaps_huo1;

enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

#endif
/*** End of inlined file: config.h ***/

strTree* tree1 = nullptr;
strTree* tree2 = nullptr;

int strTree::readTree(strTree* root, char* strs[], int count, int v[7])
{
	int c = 0;

	for (int i = 0; i < count; i++) {
		string t = strs[i];
		c += root->get(strs[i], v);
	}
	return c;
}

int strTree::get(char* str, int v[7]) {
	strTree* root = this;
	int count = 0;
	int back = 0;
	int len = strlen(str);
	int va = -1;
	int huosan_single = 0; 	int chong4_fix = 0;

	for (int i = 0; i < len && back < len - 4; i++) {
		if (str[i] == '/') {
			if (root->l) root = root->l;
			else {
				root = this;
				if (va != -1) back += 1;				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else if (str[i] == '0') {
			if (root->m) root = root->m;
			else {
				root = this;
				if (va != -1) back += 1;
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else if (str[i] == '1') {
			if (root->r)  root = root->r;
			else {
				root = this;
				if (va != -1) back += 1;
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		if (root->valueIndex != -1) {
			if (root->valueIndex == 2) {
				huosan_single++;
				if (huosan_single > 1) continue;
			}
			else if (root->valueIndex == 1) {
				chong4_fix++;
				if (chong4_fix > 1) continue;
			}

			va = root->valueIndex;
			v[va] += 1;
			count++;

		}
	}
	if (huosan_single > 0 && chong4_fix > 0) {
		v[2] -= 1;
	}

	return count;
}

int strTree::getScoreG(int* v, int* _v) {
#ifdef DEBUG_main
	int t = clock();
#endif
	const int* values = nullptr, * _values = nullptr;

	values = VALUE_DEFAULT;
	_values = VALUE_DEFAULT_OPPO;

	int score =
		v[0] * values[0] +
		v[1] * values[1] +
		v[2] * values[2] +
		v[3] * values[3] +
		v[4] * values[4] +
		v[5] * values[5] +
		v[6] * values[6]
		;

	int _score =
		_v[0] * _values[0] +
		_v[1] * _values[1] +
		_v[2] * _values[2] +
		_v[3] * _values[3] +
		_v[4] * _values[4] +
		_v[5] * _values[5] +
		_v[6] * _values[6]
		;

	int rs = score + _score;
#ifdef DEBUG_main
	timescore += clock() - t;
#endif
	return rs;
}

void strTree::setTree(strTree* root, const vector<string>& strs, int value) {
	for (string str : strs) {
		strTree* r = root;
		for (char c : str) {
			if (c == '/') {
				if (!root->l) root->l = new strTree(-1, c);
				root = root->l;
			}
			else if (c == '0') {
				if (!root->m) root->m = new strTree(-1, c);
				root = root->m;
			}
			else if (c == '1') {
				if (!root->r) root->r = new strTree(-1, c);
				root = root->r;
			}
		}
		root->valueIndex = value;
		root = r;
	}
}
strTree* strTree::build(strTree* root) {
	setTree(root, shaps_win, 0);
	setTree(root, shaps_huo4, 1);
	setTree(root, shaps_huo3, 2);
	setTree(root, shaps_chong3, 3);
	setTree(root, shaps_huo2, 4);
	setTree(root, shaps_ming2, 5);
	setTree(root, shaps_huo1, 6);
	return root;
}

strTree* strTree::build_oppo(strTree* root) {
	setTree(root, _shaps_huo4_oppo, 0);
	setTree(root, _shaps_chong4_oppo, 1);
	setTree(root, _shaps_huo3, 2);
	setTree(root, _shaps_chong3, 3);
	setTree(root, _shaps_huo2, 4);
	setTree(root, _shaps_ming2, 5);
	setTree(root, _shaps_huo1, 6);
	return root;
}

void strTree::initRoots() {
	tree1 = new strTree(-1, 0);
	tree2 = new strTree(-1, 0);
	tree1 = strTree::build(tree1);
	tree2 = strTree::build_oppo(tree2);
}

strTree::strTree(int v, char ch) {
	valueIndex = v;
	c = ch;
	l = nullptr;
	m = nullptr;
	r = nullptr;

}
strTree::~strTree()
{
	if (l) delete l;
	if (m) delete m;
	if (r) delete r;
}
/*** End of inlined file: evaluate.cpp ***/


/*** Start of inlined file: rule.cpp ***/
#pragma GCC optimize(2)


/*** Start of inlined file: rule.h ***/
#pragma once

void btzrule();

/*** End of inlined file: rule.h ***/


/*** Start of inlined file: board.h ***/
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

	int abSearch(playerEnum p, int depth, int alpha, int beta, int maxdept);

	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);

	pair<int, int> policy(playerEnum p);
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]);
	int getScore();
	int getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]);

	void getShapes(int* v, int* _v);
	void getShapes4(pair<int, int>& pos, int* v, int* _v);
	int toString(char* strs[]);
	int toString4(char* strs[], pair<int, int>& pos);
	void addShapes(int v[7], int _v[7]);

};

#endif
/*** End of inlined file: board.h ***/


/*** Start of inlined file: config.h ***/
#pragma once
#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <time.h>
#include <vector>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY

using namespace std;
extern int MAX_DEPTH;
extern int keepLen;
extern int range;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;

extern int step_INIT;
extern int MAX_DEPTH_INIT;
extern int keepLen_INIT;
extern int range_INIT;

extern int step_FINA;
extern int MAX_DEPTH_FINA;
extern int keepLen_FINA;
extern int range_FINA;

extern int skeepLen;
extern int TIMEBEGIN;
extern const int COL;
extern const int ROW;
extern const int MAX_INT;
extern const int MIN_INT;
extern const int MAX_SEARCH_TIME_MS;
extern const int VALUE_DEFAULT[7];
extern const int VALUE_DEFAULT_OPPO[7];
extern const int VALUE_MUST_WIN;

extern int time1;
extern int tos4count;
extern int toscount;
extern int timescore4;
extern int timescore;
extern int timepos;
extern int timepos1;
extern int timetos;
extern int timetos4;
extern int timetemp;

extern int reachMaxDepth;
extern int searchNode;

extern const vector<string> shaps_win;
extern const vector<string> shaps_huo4;
extern const vector<string> shaps_huo3;
extern const vector<string> shaps_chong3;
extern const vector<string> shaps_huo2;
extern const vector<string> shaps_ming2;
extern const vector<string> shaps_huo1;

extern const vector<string> _shaps_huo4_oppo;
extern const vector<string> _shaps_chong4_oppo;
extern const vector<string> _shaps_huo3;
extern const vector<string> _shaps_chong3;
extern const vector<string> _shaps_huo2;
extern const vector<string> _shaps_ming2;
extern const vector<string> _shaps_huo1;

enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

#endif
/*** End of inlined file: config.h ***/

void btzrule() {
	int b[15][15] = { 0 };	int x, y, n;
	int xf, yf;

	cin >> n;
	cin >> x >> y;
	if (x == -1) {
		if (n == 1) {
			cout << 1 << ' ' << 7 << endl; return;
		}
		else {
			cin >> xf >> yf;
			cin >> x >> y;
			if (x == -1) {
				b[xf][yf] = -1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}
			else {
				b[x][y] = -1;
				b[xf][yf] = 1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}
		}
	}
	else {
		if (n == 1) {
			b[x][y] = -1;
			if (x >= 2 && x <= 12 && y >= 2 && y <= 12) {
				cout << -1 << ' ' << -1 << endl;
				return;
			}
		}
		else {
			cin >> xf >> yf;
			if (xf == -1) {
				b[x][y] = 1;
				cin >> x >> y;
				b[x][y] = -1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}
			else {
				b[x][y] = -1;
				b[xf][yf] = 1;
				cin >> x >> y;
				b[x][y] = -1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}

		}

	}

	board* mb = new board(b);
#ifdef DEBUG_main
	time_t t = clock();
#endif
	if (n <= step_INIT) {

		range = range_INIT;
		keepLen = keepLen_INIT;
		MAX_DEPTH = MAX_DEPTH_INIT;
	}
	if (n >= step_FINA) {
		range = range_FINA;
		keepLen = keepLen_FINA;
		MAX_DEPTH = MAX_DEPTH_FINA;
	}
#ifdef TIME_CONTROL
	TIMEBEGIN = clock();
#endif

	pair<int, int> p = mb->policy(ME);
	cout << p.first << ' ' << p.second << endl;

#ifdef DEBUG_main

	cout << *mb << endl;
	mb->chess[p.first][p.second] = 1;
	cout << *mb << endl;
	cout << "timescore4=" << timescore4 << endl;
	cout << "timescore=" << timescore << endl;
	cout << "timestos=" << timetos << "   toscount=" << toscount << endl;
	cout << "timestos4=" << timetos4 << "   tos4count=" << tos4count << endl;
	cout << "aiitime=" << clock() - t << endl;
	cout << "timepos=" << timepos << endl;
	cout << "timepos1=" << timepos1 << endl;

	cout << "timetemp=" << timetemp << endl;

	cout << "search node:" << searchNode << endl;
	cout << "max depth:" << reachMaxDepth << endl;
	cout << "nps:" << searchNode * 1000.0 / (clock() - t) << endl;
#endif 	return;
}

/*** End of inlined file: rule.cpp ***/


/*** Start of inlined file: main.cpp ***/
#include <memory.h>


/*** Start of inlined file: config.h ***/
#pragma once
#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <time.h>
#include <vector>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY

using namespace std;
extern int MAX_DEPTH;
extern int keepLen;
extern int range;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;

extern int step_INIT;
extern int MAX_DEPTH_INIT;
extern int keepLen_INIT;
extern int range_INIT;

extern int step_FINA;
extern int MAX_DEPTH_FINA;
extern int keepLen_FINA;
extern int range_FINA;

extern int skeepLen;
extern int TIMEBEGIN;
extern const int COL;
extern const int ROW;
extern const int MAX_INT;
extern const int MIN_INT;
extern const int MAX_SEARCH_TIME_MS;
extern const int VALUE_DEFAULT[7];
extern const int VALUE_DEFAULT_OPPO[7];
extern const int VALUE_MUST_WIN;

extern int time1;
extern int tos4count;
extern int toscount;
extern int timescore4;
extern int timescore;
extern int timepos;
extern int timepos1;
extern int timetos;
extern int timetos4;
extern int timetemp;

extern int reachMaxDepth;
extern int searchNode;

extern const vector<string> shaps_win;
extern const vector<string> shaps_huo4;
extern const vector<string> shaps_huo3;
extern const vector<string> shaps_chong3;
extern const vector<string> shaps_huo2;
extern const vector<string> shaps_ming2;
extern const vector<string> shaps_huo1;

extern const vector<string> _shaps_huo4_oppo;
extern const vector<string> _shaps_chong4_oppo;
extern const vector<string> _shaps_huo3;
extern const vector<string> _shaps_chong3;
extern const vector<string> _shaps_huo2;
extern const vector<string> _shaps_ming2;
extern const vector<string> _shaps_huo1;

enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

#endif
/*** End of inlined file: config.h ***/


/*** Start of inlined file: rule.h ***/
#pragma once

void btzrule();

/*** End of inlined file: rule.h ***/


/*** Start of inlined file: evaluate.h ***/
#pragma once

#ifndef EVALUATE
#define EVALUATE

#include<vector>
#include<string>
using namespace std;

class strTree {
public:
	char c;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(char* str, int v[7]);

	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);

	static int readTree(strTree* root, char* strs[], int count, int v[7]);
	static void initRoots();
	static int getScoreG(int* v, int* _v);

	~strTree();
};

extern strTree* tree1;
extern strTree* tree2;

#endif
/*** End of inlined file: evaluate.h ***/

int main()
{

	strTree::initRoots();

	/*
	int arr[15][15]{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,-1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0,-1, 0,-1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0,-1, 1, 1, 1, 1,-1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,-1,-1,-1,-1, 1, 0, 0, 0,
		0, 0, 0, 0, 0,-1, 0, 1,-1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	board* mb = new board(arr);
		cout << *mb << endl;

	int v[7]{ 0 };
	int _v[7]{ 0 };
	pair<int, int> pqos =pair<int,int>(1, 1);
	mb->getShapes(v, _v);
	mb->getScoreP(pqos,v,_v);

	pair<int, int> pos = mb->policy(playerEnum::ME);
	cout << pos.first << ' ' << pos.second << endl;

	*/

	btzrule();

#ifdef DEBUG

#endif
	system("pause");
	return 0;
}
/*** End of inlined file: main.cpp ***/
