#pragma once
#ifndef BOARD
#define BOARD


#include <iostream>
#include <random>
#include "config.h"
#include "hashTable.h"

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


	//���ͣ�ME  OPPO
	int shapes[2][SHAPE_TYPES]{ 0 };

	//�ַ�������  ��  ��  ��
	char strs[4][29][16]{ '0' };

	char historyStr[512]{ 0 };
	

	Pos bestMove;
	int bestVelue =-10000;
	int VCFdepth = 0;
	playerEnum vcfAttacker;
	playerEnum policy_turn = EMPTY;
	int staticValues[100]{ 0 };

private:
	//�к� �к� ���� �ַ�������/�ַ�����
	int strIndexs[15][15][4][2]{ 0 };
	bool terminal = false;
	int shapesChange[2][SHAPE_TYPES]{ 0 };
	int moveTag = 0;//1 Ϊmove   0 Ϊundo
	int selfIndex;//�ҷ���������
	int oppoIndex;//�Է���������

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
	friend ostream& operator<<(ostream& os, board& b);
	board* reverse();

	//���ͺ��ַ����任

	void initStrIndexs() {
		for (int i = 0;i < 15;i++) {
			for (int j = 0;j < 15;j++) {


				//��
				strIndexs[i][j][0][0] = i;
				strIndexs[i][j][0][1] = j;
				//��
				strIndexs[i][j][1][0] = j;
				strIndexs[i][j][1][1] = i;
				//��
				strIndexs[i][j][2][0] = (i - j + 14);
				strIndexs[i][j][2][1] = i > j ? j : i;
				//��
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

		for (int k = 0;k < 4;k++) {

			int* ins = strIndexs[i][j][k];
			strs[k][ins[0]][ins[1]] = p + '0';

		}
	}

	inline void undoChangeStr(Pos pos) {
		int i = pos.first;
		int j = pos.second;

		for (int k = 0;k < 4;k++) {

			int* ins = strIndexs[i][j][k];
			strs[k][ins[0]][ins[1]] = '0';

		}
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
	//��ǰ������������
	inline int piece() {
		return turnToMove == ME ? 0 : 1;
	}
	inline int piece(playerEnum p) {
		return p == ME ? 0 : 1;
	}

	//����
	int abSearch(int depth, int alpha, int beta, int maxdept);
	int VCFSearch();

	//�ҿ������ӵ�
	int getAllPossiblePos(playerEnum p, int depth, pair<int, int>* res, int* w);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);


	int genAreaAll(Pos* ps) {//�������п��ܵ�
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

	/*
	int checkPattenLine(playerEnum p,char* str,int index) {
		int count = 0;
		char oppo = (p == OPPO ? '1' : '/');
		int s = index - 1;
		int e = index + 1;
		for ( ;s >= index-5 && s>=0 && str[s]!=oppo;s--) {
			if (str[s]!='0') count++;
		}
		for ( ;e <= index+5 && str[e] && str[e] != oppo;e--) {
			if (str[e] != '0') count++;
		}



	}*/

	int DIR[4][2]{//��������仯
		0, 1,
		1, 0,
		1, 1,
		1,-1
	};

	int genRangeLine4(Pos*ps,Pos p) {//���ɸõ�4�������Ͼ���4���ڵĿհ׵�
		int x = p.first;
		int y = p.second;
		int count = 0;
		for (int i = 0;i < 4;i++) {

			int strins = strIndexs[x][y][i][0];
			int offset = strIndexs[x][y][i][1];

			for (int j = (offset - 4 > 0 ? offset - 4 : 0);j <= offset + 4 && strs[i][strins][j];j++) {
				if (strs[i][strins][j] == '0') {
					ps[count].first = x + (j-offset ) * DIR[i][0];
					ps[count++].second = y + (j-offset) * DIR[i][1];
					int a = 1;
				}
			}

		}

		return count;
	}
	int genRoot(Pos* ps, int* values) {
		int count = genAreaAll(ps);

		for (int i = 0;i < count;i++) {
			move(ps[i]);
			int flag = -quickWinScore();
			if (flag) values[i] = flag;
			else values[i] = -getScore();

			undo();
		}

		int min = count;

		int temp1, temp2, temp3;
		//ѡ������
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

	int genVCFDefendMove(Pos* ps) {//���� ���������ͳ���


		int c = genRangeLine4(ps, *lastMove());
		int validIndex = 0;
		for (int i = 0;i < c;i++) {
			move(ps[i]);
			if (shapesChange[piece(vcfAttacker)][C4] < 0 ) {
				ps[validIndex].first = ps[i].first;
				ps[validIndex++].second = ps[i].second;
			}

			undo();
		}
		return validIndex;
	}
	int genVCFAttackMove(Pos* ps) {//���� ���������ͳ���
		int c = genAreaAll(ps);
		int validIndex = 0;
		//cout << *this << endl;
		for (int i = 0;i < c;i++) {
			move(ps[i]);
			if (shapesChange[piece(vcfAttacker)][C4]+ shapesChange[piece(vcfAttacker)][H4] > 0) {
				//cout << *this << endl;
				ps[validIndex].first = ps[i].first;
				ps[validIndex++].second = ps[i].second;
			}

			undo();
		}

		return validIndex;
	}
	int quickWinCheck() {//���� 1 win    0 δ֪     -1 ��

		if (oppoShape()[WIN])//�Է��Ѿ���5
			return -1;
		else if (myShape()[H4] || myShape()[C4] || myShape()[WIN]) {//�ҷ��� ��4 ��4 ������ֱ�� ��5 �� �ҷ�ʤ
			//cout << *this << endl;
			return 1;
		}
		else if (oppoShape()[H4]) {//�Է��� ��4 ���Է�ʤ
			//cout << *this << endl;
			return -1;
		}/*
		else if (shapesChange[oppoIndex][C4]&&shapesChange[oppoIndex][H3]) {//�Է� ��3 ��4���Է�ʤ//�³���ͬʱ�Լ��γɻ����Լ�ʤ
			//cout << *this << endl;
			return -1;
		}*/
		else if ((myShape()[H3] || myShape()[Q3]) && !oppoShape()[C4]) {//�ҷ� ��3 �� �Է� �޳�4�� �ҷ�ʤ

			//cout << *this << endl;
			return 1;
		}
		else if (!myShape()[H3] && !myShape()[Q3] && !myShape()[C3] && shapesChange[oppoIndex][H3] + shapesChange[oppoIndex][Q3] > 1) {//�ҷ� ��3 �� �Է� ˫3�� �Է�ʤ
			//cout << *this << endl;
			return -1;
		}
		return 0;
	}
	int quickWinScore() {
		if (oppoShape()[WIN])//�Է��Ѿ���5
			return -MAX_INT;
		else if (myShape()[H4] || myShape()[WIN]) {//�ҷ��� ��4 ��4 ������ֱ�� ��5 �� �ҷ�ʤ
			//cout << *this << endl;
			return MAX_INT;
		}
		else if (myShape()[C4]) {
			return MAX_INT - 1;
		}
		else if (oppoShape()[H4]) {//�Է��� ��4 ���Է�ʤ
			//cout << *this << endl;
			return -MAX_INT+1;
		}/*
		else if (oppoShape()[C4] && oppoShape()[H3]) {//�Է� ��3 ��4���Է�ʤ
			//cout << *this << endl;
			return -MAX_INT+2;
		}*/
		else if ((myShape()[H3] || myShape()[Q3]) && !oppoShape()[C4]) {//�ҷ� ��3 �� �Է� �޳�4�� �ҷ�ʤ

			//cout << *this << endl;
			return MAX_INT-2;
		}
		else if (!myShape()[H3] && !myShape()[Q3] && !myShape()[C3] && oppoShape()[H3] + oppoShape()[Q3] > 1) {//�ҷ� ��3 �� �Է� ˫3�� �Է�ʤ
			//cout << *this << endl;
			return -MAX_INT+3;
		}
		return 0;
	}

	//��������
	int LC(Pos* ps, int count) {
		if (count <= 0) return 0;
		int values[225]{ 0 };
		for (int i = 0;i < count;i++) {
			values[i] = getLC4(ps[i]);
		}
		int min = count > LC_KEEP ? LC_KEEP : count;

		int temp1, temp2, temp3;
		//ѡ������
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
			if (m < LC_LOW //�����
				//|| 
				//i>0 && values[0] - m > LC_DELTA //�����ֵ�Ƚϵ�
				) {
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
	int TTrefresh(Pos* ps, int count, int* values) {//�û������
		if (count <= 0) return 0;
#ifdef FULLSEARCH
		int min = count;
#else
		int min = count > TT_KEEP ? TT_KEEP : count;
#endif // FULLSEARCH


		int temp1, temp2, temp3;
		//ѡ������
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
			if (m < LC_LOW //�����
				|| i>0 && (values[0] - m > LC_DELTA)  //�� ��ǰ�� �������ֵ�Ƚϵ�
					
				) {
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
	int Rootfresh(Pos* ps, int count, int* values) {//���ڵ����
		if (count <= 0) return 0;
#ifdef FULLSEARCH
		int min = count;
#else
		int min = count;
#endif // FULLSEARCH


		int temp1, temp2, temp3;
		//ѡ������
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
			if (m < LC_LOW //�����
				) {
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

	inline int getMaxBranch(int ply) {// �������֧��
		return MAX(keepLen - 2 * ply, keepLenMin);
	}
	//����
	Pos policy();
	Pos lose();


	//��ֵ
	int getScoreP(pair<int, int>& pos);
	inline int getScore(); //��ȡ��ǰ��������player��ֵ
	int getLC4(Pos p) {//��ȡ��ǰλ�õ��ĸ��������LC(���ܼ�������ֵ����ΪҪ����˫������)
		/*
		lcCount++;
		int flag = quickWinCheck();
		if (flag)
			return MAX_INT * flag;

		int vv[2][SHAPE_TYPES]{ 0 };
		getShapes4(p, vv);
		int res = 0;
		for (int i = 0;i < SHAPE_TYPES;i++) {
			res += (vv[0][i] + vv[1][i]) * VALUE_GDEFAULT[i];
		}
		*/
		move(p);
		int res = -getScoreDelta();
		undo();
		return res;
	}
	int getScoreDelta();//������Ĺ�ֵ
	int getScoreOneStep();//ĩ�����һ���Ĺ�ֵ

	//��ȡ���ͺ��ַ���
	void getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]);
	bool checkImportantShapes4(pair<int, int> pos);



	//�û���
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

	void save(Pos* ps, int pcount, int v) {
		TTEntrace* tte = new TTEntrace(ps, pcount, v);
		TT.AddItem(zobristKey, tte);
	}



	//�ƶ�
	inline void setChess(playerEnum p, Pos pos) {
		chess[pos.first][pos.second] = p;
		changeStr(p, pos);
	}

	inline void move(Pos pos) {
#ifdef DEBUG
		int t = clock();
		movecount++;
#endif // DEBUG

		removeMoveShape(pos);
		setChess(turnToMove, pos);
		addMoveShape(pos);
		zobristKey ^= zobrist[turnToMove == ME ? 0 : 1][pos.first][pos.second];
		historyMoves[moveCount] = pos;

		turnToMove = -turnToMove;
		turnToMoveOppo = -turnToMoveOppo;
		selfIndex = (selfIndex + 1) % 2;
		oppoIndex = (oppoIndex + 1) % 2;
		moveCount++;
		moveTag = 1;


#ifdef DEBUG
		timemove += clock() - t;
#endif // DEBUG
	}

	inline void move(int x, int y) {
		Pos pos(x, y);
		move(pos);
	}


	inline void undo() {
#ifdef DEBUG
		int t = clock();
		movecount++;
#endif // debug

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
#endif // DEBUG
	}


	inline	Pos* lastMove(int n = 1) {
		if (moveCount >= n)return historyMoves + (moveCount - n);
		else return nullptr;
	}

};

#endif // !BOARD