#include <random>
#include <cstring>
#include <iostream>
#include <time.h>
#include <vector>
#include <cstring>
#include <memory>

//#define FULLSEARCH

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY

#define DEBUG_BOTZONE
// #define TIME_CONTROL
using namespace std;

typedef pair<int, int> Pos;
typedef uint64_t U64;
#define SHAPE_TYPES 8



int START_DEPTH = 1;
int MAX_DEPTH = 9;

int range = 2;

int LC_DELTA = 800;
int LC_LOW = -10000;

int LC_KEEP = 30;
int TT_KEEP = 30;
int keepLen = 64;
int keepLenMin = 25;//最小保留分支数




int MAX_VCT_DEPTH = 7;
int MAX_VCF_DEPTH = 25;

int step_INIT = -1;
int MAX_DEPTH_INIT = 8;
int keepLen_INIT = 15;
int range_INIT = 2;

int step_FINA = 100;
int MAX_DEPTH_FINA = 5;
int keepLen_FINA = 5;
int range_FINA = 2;

int skeepLen = 3;
int TIMEBEGIN = 0;
const int COL = 15;
const int ROW = 15;
const int MAX_INT = 0x3f3f3f3f;
const int MIN_INT = -MAX_INT;
const int MAX_SEARCH_TIME_MS = 0.95 * CLOCKS_PER_SEC;

const int VALUE_GDEFAULT[SHAPE_TYPES]
{
	1000	,
	500	,		150  	,
	100 	,      	100   	, 	60   ,
	60		,    	15
};

int time1;
int tos4count = 0;
int toscount = 0;
int shape4count = 0;
int timemove = 0;
int movecount = 0;
int timepos = 0;
int timereadtree = 0;
int timetos = 0;
int timetos4 = 0;
int timetemp = 0;
int timeshape = 0;
int timeshape4 = 0;

int reachMaxDepth = 0;
int searchNode = 0;
int testCount = 0;

const vector<string> gshaps_win = { "11111" };
const vector<string> gshaps_huo4 = { "011110" };
const vector<string> gshaps_chong4 = { "10111","11011","11101","11110","01111" };
const vector<string> gshaps_huo3 = { "011100","001110" };
const vector<string> gshaps_qian3 = { "011010","010110" };
const vector<string> gshaps_chong3 = { "11100","11010","11001","10110","10101","10011",   "00111","01011","01101","01110" };
const vector<string> gshaps_huo2 = { "001100","010100","001010","010010" };
const vector<string> gshaps_ming2 = { "11000","10100","10010",  "00011","00101","01001" ,"01010","01100" ,"00110" };

const vector<string> gshaps_win_oppo = { "/////" };
const vector<string> gshaps_huo4_oppo = { "0////0" };
const vector<string> gshaps_chong4_oppo = { "/0///","//0//","///0/","////0","0////" };
const vector<string> gshaps_huo3_oppo = { "0///00","00///0" };
const vector<string> gshaps_qian3_oppo = { "0//0/0","0/0//0" };
const vector<string> gshaps_chong3_oppo = { "///00","//0/0","//00/","/0//0","/0/0/","/00//",   "00///","0/0//","0//0/",  "0///0" };
const vector<string> gshaps_huo2_oppo = { "00//00","00/0/0","0/0/00","0/00/0" };
const vector<string> gshaps_ming2_oppo = { "//000","/0/00","/00/0",  "000//","00/0/","0/00/","0/0/0","0//00" ,"00//0" };


enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

playerEnum operator-(playerEnum p);

enum shapeEnum {
	WIN = 0, H4, C4, H3, Q3, C3, H2, M2
};

class hashTable;
class TransitionTable;

extern hashTable shapeHashTable;
extern TransitionTable TT;


/*** End of inlined file: config.h ***/


static std::mt19937_64 mrandom(time(NULL));



playerEnum operator-(playerEnum p) {
	return p == ME ? OPPO : (p == OPPO ? ME : EMPTY);
};

U64 zobristInitRandom = mrandom();

#ifndef BOARD
#define BOARD

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <cstdlib>
#include <string>



/*** Start of inlined file: evaluate.h ***/

#ifndef EVALUATE
#define EVALUATE

#include<vector>
#include<string>
#include<unordered_map>


class strTree {
public:
	char c;
	char pumpChar = 0;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(const char* str, int v[7]);

	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);

	static int readTree(strTree* root, char* strs[], int count, int v[SHAPE_TYPES]);
	static void initRoots();
	static int getScoreG(int vv[2][SHAPE_TYPES]);
	static int getScoreG(int* v, int* _v);

	~strTree();
};

extern strTree* tree1;
extern strTree* tree2;

#endif
/*** End of inlined file: evaluate.h ***/

using namespace std;

template <typename K, typename V>
class basehashTable
{
protected:
	struct item
	{
		K key;
		V value;
		item* next;

		item(K k, V v) : key(k), value(v), next(nullptr) {}
	};
	const int tableSize;      item** HashTable;

	int size;

public:
	int hitCount = 0;
	int unHitCount = 0;
	inline basehashTable(int s) :tableSize(s) {

		HashTable = new item * [tableSize];
		for (int i = 0; i < tableSize; ++i)
			HashTable[i] = new item(keyNull(), valueNull());
		state = -1;
		size = 0;

	}
	inline virtual ~basehashTable() {};
	inline void AddItem(K str, V vv) {
		int index = hashFunction(str);

		if (keyEmpty(HashTable[index]->key))
		{
			HashTable[index]->key = str;
			HashTable[index]->value = vv;
			size++;
		}
		else
		{
			item* p = HashTable[index];
			item* n = new item(str, vv);
			bool exist = false;
			while (p->next != nullptr && !(exist = !keyCmp(p->key, str)))
			{
				p = p->next;
			}
			if (exist)
				return;

			size++;
			p->next = n;
		}
	}
	inline void remove(K str)
	{
		int index = hashFunction(str);

		item* delPtr;
		item* p1;
		item* p2;

		if (keyEmpty(HashTable[index]->key))
		{
			return;
		}
		else if (keyEmpty(HashTable[index]->key, str) == 0 && HashTable[index]->next == nullptr)
		{
			HashTable[index]->key = nullptr;
			size--;
		}
		else if (keyCmp(HashTable[index]->key, str) == 0)
		{
			delPtr = HashTable[index];
			HashTable[index] = HashTable[index]->next;
			delete delPtr;
			size--;
		}
		else
		{
			p1 = HashTable[index]->next;
			p2 = HashTable[index];
			while (p1 != nullptr && keyCmp(p1->key, str))
			{
				p2 = p1;
				p1 = p1->next;
			}
			if (p1 == nullptr)
			{
				return;
			}
			else
			{
				delPtr = p1;
				p1 = p1->next;
				p2->next = p1;
				delete delPtr;
				size--;
			}
		}
	}
	inline int NumberOfItemsInIndex(int index)
	{
		int count = 0;
		if (keyEmpty(HashTable[index]->key))
		{
			return count;
		}
		else
		{
			count++;
			item* p = HashTable[index];
			while (p->next != nullptr)
			{
				count++;
				p = p->next;
			}
		}
		return count;
	}
	inline V find(K str)
	{
		int index = hashFunction(str);
		bool FindName = false;

		V v = valueNull();
		item* p = HashTable[index];

		state = -1;
		while (p != nullptr)
		{
			state++;
			if (!keyEmpty(p->key) && !keyCmp(p->key, str))
			{
				FindName = true;
				v = p->value;
				break;
			}
			p = p->next;
		}
		if (!FindName) {
			state = -1;
			unHitCount++;
		}
		else {
			hitCount++;
		}

		return v;
	}
	inline int getsize() { return size; }
	inline int getstate() { return state; }
	virtual inline bool keyEmpty(K k) { return !keyCmp(k, keyNull()); }
	inline bool valueEmpty(V v) { return valueEqual(v, valueNull()); };
virtual int hashFunction(K str) = 0;protected:
	int state;

	virtual int keyCmp(K k1, K k2) { return k1 != k2; }
	virtual int valueEqual(V v1, V v2) { return v1 == v2; }
	virtual V valueNull() { return nullptr; }
	virtual K keyNull() { return K{}; }

};

class DoubleShape {
public:
	int* v;
	int* _v;

	DoubleShape(int* v1, int* v2) :v(v1), _v(v2) {}
	int*& operator[](int index) {
		return index == 0 ? v : _v;
	}
};

class hashTable :public basehashTable<char*, int**>
{
public:

	inline hashTable() :basehashTable<char*, int**>(100000) {};
	inline ~hashTable() {};
	int hashFunction(char* str);
	int hashFunction(char* str, int len);

protected:

	inline bool keyEmpty(char* k) { return k == nullptr; }
	inline char* keyNull() { return nullptr; }
	int keyCmp(char* k1, char* k2) { return strcmp(k1, k2); }

public:
	void PrintTable();
	void PrintItemsInIndex(int index);
	void init();
	int** getShape(char* str);
	void generateStrings(string current, int len, int maxLength, int samecount);
};

extern U64 zobristInitRandom;

class TTEntrace
{
public:
	TTEntrace(Pos* ps, int c, int v) : value(v)
	{
		for (int i = 0; i < moveCount; i++)
		{
			moves[i] = ps[i];
		}
	};
	TTEntrace() : moveCount(0), value(0) {
		memset(moves, 0, sizeof(Pos));
	}
	~TTEntrace();

	Pos moves[150];
	int moveCount;
	int value;
	int depth;

private:
};

class TransitionTable :public basehashTable<U64, TTEntrace*> {
public:

	inline TransitionTable() :basehashTable<U64, TTEntrace*>(1000000) {};
	inline ~TransitionTable() {};

protected:
	inline int hashFunction(U64 zobristkey) {
		return zobristkey % tableSize;
	}
	inline U64 keyNull() { return zobristInitRandom; };

public:

};

#endif
/*** End of inlined file: hashTable.h ***/

template<class T1, class T2>
inline auto _max(const T1 a, const T2 b) {
	return (a > b) ? a : b;
}

template<class T1, class T2>
inline auto _min(const T1 a, const T2 b) {
	return (a < b) ? a : b;
}

template<class T>
inline auto _abs(const T a) {
	return (a < 0) ? -a : a;
}

#define MAX(a,b) _max(a,b)
#define MIN(a,b) _min(a,b)
#define ABS(a) _abs(a)



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

	int shapes[2][SHAPE_TYPES]{ 0 };

	char strs[4][29][16]{ '0' };

private:
	int strIndexs[15][15][4][2]{ 0 };
	bool terminal = false;
	int shapesChange[2][SHAPE_TYPES]{ 0 };
	int moveTag = 0;
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

	void initStrIndexs() {
		for (int i = 0;i < 15;i++) {
			for (int j = 0;j < 15;j++) {

				strIndexs[i][j][0][0] = i;
				strIndexs[i][j][0][1] = j;
				strIndexs[i][j][1][0] = j;
				strIndexs[i][j][1][1] = i;
				strIndexs[i][j][2][0] = (i - j + 14);
				strIndexs[i][j][2][1] = i > j ? j : i;
				strIndexs[i][j][3][0] = (i + j);
				strIndexs[i][j][3][1] = i + j < 14 ? i : 14 - j;

			}
		}
	}

	class FIFINT {
	public:
		int a1;
		int a2;int a3;int a4;
		FIFINT(int c1, int c2, int c3, int c4) :a1(c1), a2(c2), a3(c3), a4(c4) {}
	};

	inline void changeStr(playerEnum p, Pos pos) {
		int i = pos.first;
		int j = pos.second;
		for (int k = 0;k < 4;k++)
			strs[k][strIndexs[i][j][k][0]][strIndexs[i][j][k][1]] = p + '0';

	}

	inline void addMoveShape(Pos pos) {
		int vv[2][SHAPE_TYPES]{ 0 };

		getShapes4(pos, vv);

		for (int i = 0;i < SHAPE_TYPES;i++) {
			shapes[0][i] += vv[0][i];
			shapes[1][i] += vv[1][i];

			shapesChange[0][i] += vv[0][i];
			shapesChange[1][i] += vv[1][i];
		}
	}
	inline void removeMoveShape(Pos pos) {
		int vv[2][SHAPE_TYPES]{ 0 };

		getShapes4(pos, vv);

		for (int i = 0;i < SHAPE_TYPES;i++) {
			shapes[0][i] -= vv[0][i];
			shapes[1][i] -= vv[1][i];

			shapesChange[0][i] = -vv[0][i];
			shapesChange[1][i] = -vv[1][i];
		}
	}

	inline int* myShape() {
		return shapes[turnToMove == ME ? 0 : 1];
	}
	inline int* oppoShape() {
		return shapes[turnToMove == ME ? 1 : 0];
	}

	int abSearch(int depth, int alpha, int beta, int maxdept);
	int VCFSearch() {
		return 0;
	}

	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);

	int genAreaAll(Pos* ps) {
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
		for (int i = 0;i < 15;i++)
			for (int j = 0;j < 15;j++) {
				if (mask[i][j] > 0) {
					ps[count++] = Pos(i, j);
				}
			}

		return count;
	}
	void genVCFDefendMove() {
	}
	void genVCFAttackMove() {
	}
	int quickWinCheck() {
		if (myShape()[H4] || myShape()[C4]) {
			return true;
		}
		else if (oppoShape()[H4]) {
			return false;
		}
		else if (oppoShape()[C4] && oppoShape()[H3]) {
			return false;
		}
		else if ((myShape()[H3] || myShape()[Q3]) && !oppoShape()[C4]) {
			return true;
		}
		else if (!myShape()[H3] && !myShape()[Q3] && !myShape()[C3] && oppoShape()[H3] + oppoShape()[Q3] > 1) {
			return false;
		}
		return 0;
	}

	int LC(Pos* ps, int count) {
		if (count <= 0) return 0;
		int values[150]{ 0 };
		for (int i = 0;i < count;i++) {
			values[i] = -getLC4(ps[i]);
		}
		int min = count > LC_KEEP ? LC_KEEP : count;

		int temp1, temp2, temp3;
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
			if (m < LC_LOW || i>0 && values[0] - m > LC_DELTA) {
				break;
			}

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
	int TTrefresh(Pos* ps, int count, int* values) {
		if (count <= 0) return 0;
#ifdef FULLSEARCH
		int min = count;
#else
		int min = count > TT_KEEP ? TT_KEEP : count;
#endif

		int temp1, temp2, temp3;
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
			if (m < LC_LOW || i>0 && values[0] - m > LC_DELTA) {
				break;
			}
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
	int distance(Pos& p1, Pos& p2) {
		return MAX(ABS(p1.first - p2.first), ABS(p1.second - p2.second));
	}
	bool isInLine(Pos& p1, Pos& p2) {
		if (p1.first == p2.first || p1.second == p2.second) return true;
		return ABS(p1.first - p2.first) == ABS(p1.second - p2.second);
	}

	inline int getMaxBranch(int ply) {
		return MAX(keepLen - 2 * ply, keepLenMin);
	}
	pair<int, int> policy();
	pair<int, int> lose();
	int getScoreP(pair<int, int>& pos);
	inline int getScore(); 	inline int getLC4(Pos p) {

		move(p);
		int flag = quickWinCheck();

		int res = getScore();
		undo();
		if (flag) return MAX_INT * flag;
		return res;
	}

	void getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]);
	bool checkImportantShapes4(pair<int, int> pos);

	Pos historyMoves[225];
	int moveCount;
	U64 zobristKey;
	U64 zobrist[2][15][15];

	void initZobrish() {
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				zobrist[0][i][j] = mrandom();

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				zobrist[1][i][j] = mrandom();
		zobristKey = mrandom();
	}

	void save(Pos* ps, int pcount, int v) {
		TTEntrace* tte = new TTEntrace(ps, pcount, v);
		TT.AddItem(zobristKey, tte);
	}

	inline void setChess(playerEnum p, Pos pos) {
		chess[pos.first][pos.second] = p;
		changeStr(p, pos);
	}

	inline void move(Pos pos) {
#ifdef DEBUG
		int t = clock();
		movecount++;
#endif
		removeMoveShape(pos);
		setChess(turnToMove, pos);
		addMoveShape(pos);
		zobristKey ^= zobrist[turnToMove == ME ? 0 : 1][pos.first][pos.second];
		historyMoves[moveCount] = pos;
		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		moveCount++;
		moveTag = 1;

#ifdef DEBUG
		timemove += clock() - t;
#endif 	
	}

	inline void move(int x, int y) {
		Pos pos(x, y);
		move(pos);
	}

	inline void undo() {
#ifdef DEBUG
		int t = clock();
		movecount++;
#endif
		moveCount--;
		Pos p = historyMoves[moveCount];
		removeMoveShape(p);
		setChess(EMPTY, p);
		addMoveShape(p);
		zobristKey ^= zobrist[turnToMoveOppo == ME ? 0 : 1][p.first][p.second];
		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		moveTag = 0;

#ifdef DEBUG
		timemove += clock() - t;
#endif 	
	}

	inline	Pos* lastMove(int n = 1) {
		if (moveCount >= n)return historyMoves + (moveCount - n);
		else return nullptr;
	}

};

#endif

board::board()
{
	memset(chess, EMPTY, sizeof(chess));
	turnToMove = ME;
	turnToMoveOppo = -turnToMove;
	moveCount = 0;

	for (int i = 0;i < 15;i++) {
		for (int j = 0;j < 15;j++) {
			strs[0][i][j] = '0';
			strs[1][i][j] = '0';

		}
		for (int j = 0; j <= i; j++)
		{
			strs[2][i][j] = '0';
			strs[3][i][j] = '0';

			strs[2][28 - i][j] = '0';
			strs[3][28 - i][j] = '0';
		}
	}

	initStrIndexs();
	initZobrish();
}
board::board(const board& b)
{
}
board::board(int chess[][15]) {

	turnToMove = ME;
	turnToMoveOppo = -turnToMove;
	moveCount = 0;

	for (int i = 0;i < 15;i++) {
		for (int j = 0;j < 15;j++) {
			strs[0][i][j] = '0';
			strs[1][i][j] = '0';

		}
		for (int j = 0; j <= i; j++)
		{
			strs[2][i][j] = '0';
			strs[3][i][j] = '0';

			strs[2][28 - i][j] = '0';
			strs[3][28 - i][j] = '0';
		}
	}

	initStrIndexs();
	initZobrish();

	int mask[15][15]{ 0 };
	bool ex = true;
	while (ex) {
		ex = false;
		for (int i = 0;i < 15;i++)
			for (int j = 0;j < 15;j++) {

				if (chess[i][j] == 1 && turnToMove == ME && !mask[i][j] ||
					chess[i][j] == -1 && turnToMove == OPPO && !mask[i][j]
					) {
					mask[i][j] = 1;
					ex = true;
					move(i, j);
				}
			}
	}

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

board* board::reverse()
{
	board* res = new board(*this);
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			res->chess[i][j] *= -1;
		}
	}

	return res;
}

int board::abSearch(int depth, int alpha, int beta, int maxdept)
{
#ifdef DEBUG_ABS

#endif
#ifdef DEBUG

#endif
	reachMaxDepth = reachMaxDepth > depth ? reachMaxDepth : depth;
	int winFlag = quickWinCheck();
	if (winFlag)
		return MAX_INT * winFlag;

	if (depth == maxdept)
	{

		return getScore();
	}

	Move* tte = TT.find(zobristKey);

	if (!tte)
	{
		tte = new Move();
		int staticValue = getScore();
		int c = genAreaAll(tte->moves);
#ifdef FULLSEARCH
		tte->moveCount = c;
#else
		tte->moveCount = LC(tte->moves, c);
#endif
		tte->value = staticValue;
		TT.AddItem(zobristKey, tte);
	}

	if (tte->depth == maxdept)
		return tte->value;

	if (tte->value > 10000 || tte->value < -10000)
	{
		//return tte->value;
	}

	Pos* poss = tte->moves;
	int count = tte->moveCount;
	int rc = 0;
	int branch = 0;
	int maxBranch = getMaxBranch(depth);
	int maxValue = MIN_INT;
	int values[150]{ 0 };
	while (count--)
	{
		Pos& cur = poss[rc];

		int vv[2][8]{ 0 };
		getShapes4(cur, vv);

		if (!checkImportantShapes4(cur))
		{
			int distance1 = distance(cur, *lastMove());
			int distance2 = distance(cur, *lastMove(2));
			bool isNear1 = distance1 <= 2 || isInLine(cur, *lastMove()) && distance1 <= 4;
			bool isNear2 = distance2 <= 2 || isInLine(cur, *lastMove(2)) && distance2 <= 4;

			if (maxValue > LC_LOW)
			{
				if (branch > maxBranch)
					continue;
			}
			else
			{
				if (branch > keepLen)
				{
					bool isNear3 = distance(cur, *lastMove(3)) <= 4;
					if (!(isNear1 && isNear3))
						continue;
				}
			}
		}

		branch++;

		move(poss[rc]);
		int t = -abSearch(depth + 1, -beta, -alpha, maxdept);
		values[rc] = t;
		undo();

#ifdef TIME_CONTROL
		static int cmt = 5000;
		if (cmt-- < 0)
		{
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS)
				terminal = true;
			cmt = 5000;
		}
		if (terminal)
			goto TERMINAL;
#endif

		maxValue = t > maxValue ? t : maxValue;
		alpha = maxValue > alpha ? maxValue : alpha;

		if (maxValue >= beta)
		{

			break;
		}

		rc++;
	}

TERMINAL:
	if (terminal)
		return maxValue;
	tte->value = maxValue;
	tte->depth = maxdept;
	if (tte->value > -10000 && tte->value < 10000)
	{
		tte->moveCount = TTrefresh(tte->moves, tte->moveCount, values);
	}

	return maxValue;
}

pair<int, int> board::policy()
{

	pair<int, int> poss[150];
	int values[150]{ 0 };
	int count = genAreaAll(poss);

	int curmax = MIN_INT;
	Pos best = poss[0];
	Pos last = best;
	int maxv = -MIN_INT * 2;

	int rc = 0;
	int depth = 2;

	for (depth = START_DEPTH; depth <= MAX_DEPTH && !terminal; depth += 2)
	{
		int _count = count;
		rc = 0;
		curmax = MIN_INT;
		reachMaxDepth = 0;
#ifdef DEBUG_POLICY
		int steptime = clock();
#endif 		
		while (_count--) {

			move(poss[rc]);

			int t = -abSearch(1, -MAX_INT, -curmax, depth);
			values[rc] = t;
			undo();

#ifdef TIME_CONTROL
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) terminal = true;
			if (terminal)break;
#endif

			if (t > curmax)
			{
				curmax = t;
				best = poss[rc];
				maxv = t;
			}
			rc++;

		}

#ifdef TIME_CONTROL
		if (terminal) break;
#endif
		last = best;
		lastValue = curmax;
#ifdef DEBUG_POLICY
		cout << "depth = " << depth << "-" << reachMaxDepth << ", eval = " << curmax << ", best = (" << last.first << ", " << last.second << ")" << ", time = " << clock() - steptime << endl;
#endif 		
		TTrefresh(poss, count, values);

	}

#ifdef DEBUG_POLICY
	cout << endl << "TOTAL:" << "max depth = " << min(depth, MAX_DEPTH) << ", eval = " << curmax << ", best = (" << last.first << ", " << last.second << ")" << endl;
	cout << "rc = " << rc << endl;
#endif
	return best;
}

void board::getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]) {

#ifdef DEBUG
	int t = clock();
	shape4count += 1;
#endif
	char* nstrs[4]{};

	for (int i = 0;i < 4;i++)
		nstrs[i] = strs[i][strIndexs[pos.first][pos.second][i][0]];

#ifdef DEBUG
	int tt = clock();
#endif
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;

		int** vvv = shapeHashTable.getShape(nstrs[i]);

		for (int i = 0;i < SHAPE_TYPES;i++) {
			vv[0][i] += vvv[0][i];
			vv[1][i] += vvv[1][i];
		}
	}

#ifdef DEBUG
	timeshape4 += clock() - t;
	timereadtree += clock() - tt;
#endif 
}

bool board::checkImportantShapes4(pair<int, int> pos) {

#ifdef DEBUG
	int t = clock();
	shape4count += 1;
#endif
	char* nstrs[4]{};

	for (int i = 0;i < 4;i++)
		nstrs[i] = strs[i][strIndexs[pos.first][pos.second][i][0]];

#ifdef DEBUG
	int tt = clock();
#endif 	
	int count = 0;
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;

		int** vvv = shapeHashTable.getShape(nstrs[i]);

		for (int j = 0;j < SHAPE_TYPES - 1;j++) {
			if (vvv[0][j] || vvv[1][j]) {
#ifdef DEBUG
				timeshape4 += clock() - t;
				timereadtree += clock() - tt;
#endif 				
				return  true;
			}
		}
	}

#ifdef DEBUG
	timeshape4 += clock() - t;
	timereadtree += clock() - tt;
#endif 	
	return false;
}

int board::getScoreP(pair<int, int>& pos) {

#ifdef DEBUG_main
	int t = clock();
#endif

	int vv[2][SHAPE_TYPES];
	getShapes4(pos, vv);

	int score = strTree::getScoreG(vv);

	return score;
}

int board::getScore() {
	if (turnToMove == ME) {
		return strTree::getScoreG(shapes);
	}
	else {
		return -strTree::getScoreG(shapes);
	}

}

/*** End of inlined file: board.cpp ***/


/*** Start of inlined file: hashTable.cpp ***/


int hashTable::hashFunction(char* str)
{
	int len = strlen(str);
	int index = 0;
	int mul = 1;
	for (int i = len - 1;i >= 0;i--) {
		index += mul * (str[i] + 2 - '0');

		mul *= 3;
	}
	index = index % tableSize;

	/*
	cout << "key[0] = " << key[0] << endl;
	cout << "key[0] = " << static_cast<int>(key[0]) << endl;
	cout << "key[1] = " << key[1] << endl;
	cout << "key[2] = " << key[2] << endl;
	cout << "sum = " << sum << endl;
	cout << "index = " << index << endl << endl;
	*/
	return index;
}

int hashTable::hashFunction(char* str, int len)
{
	int index = 0;
	int mul = 1;
	for (int i = len - 1;i >= 0;i--) {
		index += mul * (str[i] == '0' ? 1 : (str[i] == '1' ? 2 : 3));

		mul *= 3;
	}
	index = index % tableSize;

	return index;
}

void hashTable::PrintTable()
{

}

void hashTable::PrintItemsInIndex(int index)
{
	item* p = HashTable[index];
	if (p->key == 0)
	{
		cout << "index = " << index << "is empty";
	}
	else
	{
		cout << "index " << index << " contains the following items \n";
		while (p != nullptr)
		{
			cout << p->key << ", " << p->value << endl;
			p = p->next;
		}
	}
}

int** hashTable::getShape(char* str)
{

	int** ans = find(str);
	if (ans) {

		return ans;
	}

	int* v = new int[7]{ 0 };
	int* _v = new int[7]{ 0 };
	int** vv = new int* [2]{ v,_v };

	tree1->get(str, v);
	tree2->get(str, _v);

	AddItem(str, vv);
	state = -1;
	return vv;
}

void hashTable::init()
{
	for (int length = 1; length <= 12; ++length) {
		generateStrings("", 0, length, 1);
	}
	return;
}

void hashTable::generateStrings(string current, int len, int maxLength, int samecount) {
	if (len == maxLength) {
		if (maxLength > 3 && current[len - 1] == '0' && current[len - 2] == '0' && current[len - 3] == '0' && current[len - 4] == '0') return;

		int* v = new int[7]{ 0 };
		int* _v = new int[7]{ 0 };
		int** vv = new int* [2]{ v,_v };
		tree1->get(current.c_str(), v);
		tree2->get(current.c_str(), _v);

		char* nstr = new char[maxLength + 1]{ 0 };
		strcpy(nstr, current.c_str());

		return;
	}
	for (char c : {'0', '1', '/'}) {

		if (len == 3 && c == '0' && current[0] == '0' && current[1] == '0' && current[2] == '0')
			continue;
		bool ifsame = (len == 0 ? false : current[len - 1] == c);
		if (samecount > 4 && ifsame && c != '0') {
			continue;
		}
		generateStrings(current + c, len + 1, maxLength, ifsame ? samecount + 1 : 1);
	}
}

hashTable shapeHashTable;
TransitionTable TT;


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

int strTree::get(const char* str, int v[7]) {
	strTree* root = this;
	int count = 0;
	int back = 0;

	int va = -1;

	int tempv[SHAPE_TYPES]{ 0 };
	int debug = 0;

	int st = 0;
	while (str[st] == '0') st++;
	if (st >= skeepLen) {
		str = str + st - skeepLen;
	}

	int en = strlen(str) - 1;
	int c = 0;
	while (str[en--] == '0') c++;
	en += (2 + (c > skeepLen ? skeepLen : c));

	if (en < 5)		return 0;
	for (int i = 0; str[i] && back <= en - 4; i++) {
		if (str[i] == '/') {
			if (root->l) root = root->l;
			else {
				root = this;
				if (va != -1) {
					back += 1;
				}
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else if (str[i] == '0') {
			if (root->m) root = root->m;
			else {
				root = this;
				if (va != -1) {
					back += 1;
				}
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else if (str[i] == '1') {
			if (root->r)  root = root->r;
			else {
				root = this;
				if (va != -1) {
					back += 1;
				}
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else {
			root = this;
			if (va != -1) {
				back += 1;
			}
			else back++;
			i = back - 1;
			va = -1;
		}

		if (root->valueIndex != -1) {
			va = root->valueIndex;
			tempv[va] = 1;
			count++;
		}
	}

	v[WIN] += tempv[WIN];
	v[H4] += tempv[H4];
	v[C4] += tempv[C4];
	v[H3] += tempv[C4] ? 0 : tempv[H3];
	v[Q3] += tempv[C4] ? 0 : tempv[Q3];
	v[C3] += tempv[C4] ? 0 : tempv[C3];
	v[H2] += tempv[Q3] ? 0 : tempv[H2];
	v[M2] += (tempv[C4] | tempv[C3] | tempv[Q3] | tempv[H3] | tempv[H2]) ? 0 : tempv[M2];

	return count;
}

int strTree::getScoreG(int vv[2][SHAPE_TYPES]) {

	const int* values = VALUE_GDEFAULT;
	int score =
		vv[0][0] * values[0] +
		vv[0][1] * values[1] +
		vv[0][2] * values[2] +
		vv[0][3] * values[3] +
		vv[0][4] * values[4] +
		vv[0][5] * values[5] +
		vv[0][6] * values[6] +
		vv[0][7] * values[7]
		;
	int _score =
		vv[1][0] * values[0] +
		vv[1][1] * values[1] +
		vv[1][2] * values[2] +
		vv[1][3] * values[3] +
		vv[1][4] * values[4] +
		vv[1][5] * values[5] +
		vv[1][6] * values[6] +
		vv[1][7] * values[7]
		;

	return score - _score;
}

int strTree::getScoreG(int* v, int* _v) {

	const int* values = VALUE_GDEFAULT;
	int score =
		v[0] * values[0] +
		v[1] * values[1] +
		v[2] * values[2] +
		v[3] * values[3] +
		v[4] * values[4] +
		v[5] * values[5] +
		v[6] * values[6] +
		v[7] * values[7]
		;
	int _score =
		_v[0] * values[0] +
		_v[1] * values[1] +
		_v[2] * values[2] +
		_v[3] * values[3] +
		_v[4] * values[4] +
		_v[5] * values[5] +
		_v[6] * values[6] +
		_v[7] * values[7]
		;

	return score - _score;
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
	setTree(root, gshaps_win, 0);
	setTree(root, gshaps_huo4, 1);
	setTree(root, gshaps_chong4, 2);
	setTree(root, gshaps_huo3, 3);
	setTree(root, gshaps_qian3, 4);
	setTree(root, gshaps_chong3, 5);
	setTree(root, gshaps_huo2, 6);
	setTree(root, gshaps_ming2, 7);

	return root;
}

strTree* strTree::build_oppo(strTree* root) {
	setTree(root, gshaps_win_oppo, 0);
	setTree(root, gshaps_huo4_oppo, 1);
	setTree(root, gshaps_chong4_oppo, 2);
	setTree(root, gshaps_huo3_oppo, 3);
	setTree(root, gshaps_qian3_oppo, 4);
	setTree(root, gshaps_chong3_oppo, 5);
	setTree(root, gshaps_huo2_oppo, 6);
	setTree(root, gshaps_ming2_oppo, 7);

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


void btzrule() {


	strTree::initRoots();
	timereadtree = 0;
	timeshape4 = 0;
	shapeHashTable.hitCount = 0;
	shapeHashTable.unHitCount = 0;

	board mb;
	int x, y, n;

	cin >> n;

	for (int i = 0;i < n * 2 - 1;i++) {
		cin >> x >> y;
		if (!(x == -1 && y == -1)) {
			mb.move(x, y);
		}
		else {
			if (n == 1) {
				cout << 7 << ' ' << 7;
				return;
			}

		}
	}

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
#ifdef DEBUG_BOTZONE
	int botTime = clock();
#endif
	pair<int, int> p = mb.policy();
	cout << p.first << ' ' << p.second << endl;

#ifdef DEBUG_BOTZONE
	cout << "depth:" << reachMaxDepth << " " << "value:" << mb.lastValue << ", time:" << clock() - botTime << endl;
#endif

#ifdef DEBUG_main
	cout << mb << endl;
	mb.move(p);
	cout << mb << endl;

	cout << "timemove=" << timemove << endl;
	cout << "movecount=" << movecount << endl;
	cout << "timestos=" << timetos << "   toscount=" << toscount << endl;
	cout << "timestos4=" << timetos4 << "   tos4count=" << tos4count << endl;
	cout << "aiitime=" << clock() - t << endl;
	cout << "timepos=" << timepos << endl;
	cout << "timeReadTree=" << timereadtree << endl;

	cout << "timetemp=" << timetemp << endl;

	cout << "search node:" << TT.getsize() << endl;
	cout << "max depth:" << reachMaxDepth << endl;
	cout << "nps:" << TT.getsize() * 1000.0 / (clock() - t) << endl;

	cout << "timeshape=" << timeshape << endl;
	cout << "timeshape4=" << timeshape4 << endl;
	cout << "shape4Count=" << shape4count << endl;
	cout << "shapehash hit/unhit:" << shapeHashTable.hitCount << "/" << shapeHashTable.unHitCount << endl;
	cout << "TTE hit/unhit:" << TT.hitCount << "/" << TT.unHitCount << endl;
#endif


	return;
}


int main()
{

	btzrule();
	system("pause");
	return 0;
}
/*** End of inlined file: main.cpp ***/
