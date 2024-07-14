#include "board.h"
#include "config.h"
#include "evaluate.h"
#include "hashTable.h"


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

			strs[2][28-i][j] = '0';
			strs[3][28-i][j] = '0';
		}
	}

	initStrIndexs();
	initZobrish();
}
board::board(const board& b)
{
	memcpy(chess, b.chess, sizeof(chess));
}
board::board(int chess[][15]) {
	memcpy(this->chess, chess, sizeof(this->chess));
}

// �������
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
	// �ж���

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

	// �ж���

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

	// �ж϶Խ���
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

	// �жϷ��Խ���
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


	//�ҷ���4��ǰӮ
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
	//�Է��г��ı����
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

	//�����ֵ
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


	//ѡ������
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

	/*//ð������
	if (index > 0) {
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
	//cout<<"***"<<endl;
	//if (STEP_COUNT == 1) res->push_back(make_pair(7, 7));
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


	//ѡ������
	int temp1, temp2, temp3;
	//	int min = index > keepLen ? keepLen : index;

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

	/*//ð������
	if (index > 0) {
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
	//cout<<"***"<<endl;
	//if (STEP_COUNT == 1) res->push_back(make_pair(7, 7));
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
	//ð������


	//cout<<"***"<<endl;
	//if (STEP_COUNT == 1) res->push_back(make_pair(7, 7));

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
	for (int i = COL - 1; i > 0; i--) {// �K
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
	for (int i = 0; i < COL; i++) {// /
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
	for (int i = 0; i < ROW; i++) {// -
		s1[index++] = chess[x][i] + '0';
	}


	index = 0;
	for (int i = 0; i < ROW; i++) {// |
		s2[index++] = chess[i][y] + '0';
	}

	index = 0;
	for (int i = (y - x > 0 ? 0 : x - y); i < ROW; i++) {// 
		if (i + y - x >= 15)break;
		s3[index++] = chess[i][i + y - x] + '0';
	}

	index = 0;
	for (int i = (x + y >= ROW ? x + y - 14 : 0); i < ROW; i++) {// /
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
#endif // DEBUG_ABS

#ifdef DEBUG
	reachMaxDepth = max(reachMaxDepth, maxdept);
	searchNode++;
#endif // DEBUG


	//������� 
	if (depth == maxdept - 1) {

		if (depth % 2 == 0) {//�ҷ�



			board* nbb = this->reverse();
			int v0[7]{ 0 };
			int _v0[7]{ 0 };
			nbb->getShapes(v0, _v0);//���Ļ����ֱ��Ӯ 
			if (_v0[0] || _v0[1]) {
				return ((int)p) * MAX_INT;

			}
			if (v0[1]) return -((int)p) * MAX_INT;  //�Է����� 


			pair<int, int>poss[150];
			int count = getAllPossiblePos1(p, depth, poss);

			//��ֵ

				 //int min = MAX_INT;
			int max = MIN_INT;
			int rc = 0;
			while (count--) {

				nbb->chess[poss[rc].first][poss[rc].second] = -(int)p;
				chess[poss[rc].first][poss[rc].second] = p;


				int t;


				//�������߳��Ļ�������չ1��
				int v[7]{ 0 };
				int _v[7]{ 0 };
				nbb->getShapes4(poss[rc], v, _v);
				if ((_v[1] || _v[0]) && depth <= MAX_VCF_DEPTH) {
					int count = 0;int i = 0;int j = 0;
					for (; i < 15; i++) {
						int flag = 0;
						for (; j < 15; j++) {
							if (!chess[i][j]) {
								pair<int, int> np = pair<int, int>(i, j);
								chess[i][j] = p;

								if (isWin(p, np)) {
									flag = 1;
									chess[i][j] = -(int)p;
									break;
								}
								chess[i][j] = 0;
							}
						}
						if (flag) break;
					}
					t = abSearch(p, depth + 2, alpha, beta, maxdept + 2);
					nbb->chess[poss[rc].first][poss[rc].second] = 0;
					chess[i][j] = 0;
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
		else {//�Է�
			pair<int, int>poss[150];
			int w = 0;
			int count = getAllPossiblePos(p, depth, poss, &w);
			if (w) return (int)p * MAX_INT;
			if (count <= 10 && depth <= MAX_VCT_DEPTH ||
				count == 1 && depth <= MAX_VCF_DEPTH
				) {//���ط��س��Ļ�������չ1��
				int rc = 0;
				int min = MAX_INT;
				while (count--) {
					chess[poss[rc].first][poss[rc].second] = p;
					int t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept + 1);
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
			else {//��ֵ
				int v0[7]{ 0 };
				int _v0[7]{ 0 };
				getShapes(v0, _v0);

				int min = MAX_INT;
				int rc = 0;
				while (count--) {
					chess[poss[rc].first][poss[rc].second] = p;
					if (isWin(p, poss[rc])) { this->chess[poss[rc].first][poss[rc].second] = 0; return ((int)p) * MAX_INT; }
					
					int t;
					//�������߳��Ļ�������չ1��
					int v[7]{ 0 };
					int _v[7]{ 0 };
					getShapes4(poss[rc], v, _v);
					//cout << *this << endl;
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








	//�м��

	int w = 0;
	pair<int, int>poss[150];
	int count = getAllPossiblePos(p, depth, poss, &w);

	if (w==1)
		return (int)p * MAX_INT;
	//if (count == 1) depth -= 2;
	if (count == 0)
		if (p == 1)return MIN_INT;
		else return MAX_INT;




	int rc = 0;
	if (p == 1) {
		int max = MIN_INT;
		while (count--) {
			//if (depth == 4 && rc == 0&&poss[0].first==1&&poss[0].second==6) {
			//	cout << "2 7" << endl;
			//}
			this->chess[poss[rc].first][poss[rc].second] = p;
			//if (isWin(p, poss[rc])) { this->chess[poss[rc].first][poss[rc].second] = 0; return ((int)p) * MAX_INT; }

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
			//if (isWin(p, poss[rc])) { this->chess[poss[rc].first][poss[rc].second] = 0; return ((int)p) * MAX_INT; }

			int t = abSearch((playerEnum)(-(int)p), depth + 1, alpha, beta, maxdept);

			this->chess[poss[rc].first][poss[rc].second] = 0;

			if (depth == 1)
				t = t;
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
		//if(STEP_COUNT==-1) cout << "min = " << min << endl;
		return min;
	}


	return 0;
}



// ����
pair<int, int> board::policy(playerEnum p)
{
	strTree::initRoots();
	//shapeHashTable.init();

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

	while (count--) {

#ifdef DEBUG_POLICY
		int steptime = clock();
#endif // DEBUG_POLICY

		
		this->chess[poss[rc].first][poss[rc].second] = p;


#ifdef DEBUG_POLICY
		int x = poss[rc].first;
		int y = poss[rc].second;
		//if (x == 4 && y == 8)
		//{
			cout << *this << endl;

		//}
#endif // DEBUG_POLICY

		int t = abSearch((playerEnum)(-(int)p), 1, curmax, MAX_INT, MAX_DEPTH);
		this->chess[poss[rc].first][poss[rc].second] = 0;




#ifdef DEBUG_POLICY
		cout << "pol:" << x << ' ' << y << endl;
		cout << "value:" <<t<<endl;
		cout << "step time:"<< clock()-steptime<< endl;
#endif // DEBUG_POLICY
#ifdef TIME_CONTROL
		if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) break;
#endif
		
		if (t > curmax)
		{
			curmax = t;
			best = poss[rc];
			maxv = t;
			lastValue = t;
		}
		rc++;
		lastRc = rc;
	}
#ifdef DEBUG_POLICY
	cout << "maxv = " << curmax << endl;
	cout << "rc = " << rc << endl;
#endif // DEBUG_POLICY

	//cout<<"time1:"<<time1<<endl;



	return best;
}

void board::getShapes(int* v, int* _v) {
	int t = clock();
	char* strs[88]{ 0 };
	int count = toString(strs);
	//��ȡ��

	for (int i = 0;i < 88;i++) {
		if (!strs[i])continue;
		int** vv = shapeHashTable.getShape(strs[i]);
		for (int i = 0;i < 7;i++) {
			v[i] += vv[0][i];
			_v[i] += vv[1][i];
		}
	}
	/*
	strTree::readTree(tree1, strs, count, v);
	strTree::readTree(tree2, strs, count, _v);
	*/
	timeshape += clock() - t;
}

void board::getShapes4(pair<int, int>& pos, int vv[2][7]) {
#ifdef DEBUG
	int t = clock();
#endif // DEBUG
	uint32_t indexs = getStrIndexs(pos);

	char* nstrs[4]{};
	nstrs[3] = strs[3][indexs & 255];
	indexs >>= 8;
	nstrs[2] = strs[1][indexs & 255];
	indexs >>= 8;
	nstrs[1] = strs[1][indexs & 255];
	indexs >>= 8;
	nstrs[0] = strs[3][indexs & 255];

//��ȡ��
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;
		int** vvv = shapeHashTable.getShape(nstrs[i]);
		for (int i = 0;i < 7;i++) {
			vv[0][i] += vvv[0][i];
			vv[1][i] += vvv[1][i];
		}
	}

#ifdef DEBUG
	timeshape4 += clock() - t;
#endif // DEBUG
}

int board::getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]) {

#ifdef DEBUG_main
	int t = clock();
#endif
	/*
	//����ǰ
	int v0[7]{ 0 };
	int _v0[7]{ 0 };
	getShapes(v0, _v0);
	*/


	//ǰ
	int v[7]{ 0 };
	int _v[7]{ 0 };
	getShapes4(pos, v, _v);

	chess[pos.first][pos.second] = -1;






	//��
	int v2[7]{ 0 };
	int _v2[7]{ 0 };
	getShapes4(pos, v2, _v2);

	//cout << *this << endl;

	chess[pos.first][pos.second] = 0;
	int change3 = _v2[2] - _v[2];

	int change4 = _v2[1] - _v[1];

	int change34 = v[3] + v[4] - _v2[4] - v2[3];
	//����
	int v3[7]{ 0 };
	int _v3[7]{ 0 };

	for (int i = 0; i < 7; i++) {
		v3[i] = v0[i] - v[i] + v2[i];
		_v3[i] = _v0[i] - _v[i] + _v2[i];
	}

	if (v3[0] || v3[1]) { /*cout << "�ҷ���5/��4/��4" << pos.first << ',' << pos.second << endl;
	cout << *this << endl;*/
		return MAX_INT / 2;
	} //�ҷ���5/��4/��4
	else if (_v3[0]) {
		//cout << "�Է���4 " << pos.first << ',' << pos.second << endl;
		//cout << *this << endl; 
		return MIN_INT / 10;
	}//�Է���4
	else if ((change3 + change4) > 1 && (change4)) {
		if ((!v3[2]) && (!v3[3])) return MIN_INT;
		return -50000;
		//cout << "�Է�34 " << pos.first << ',' << pos.second<< endl;
		//cout << change3 << ' ' << change4 << endl;
		//
		//cout << *this << endl;

	} //�Է�34
	else if (v3[2] && (!_v3[1])) {
		//cout << "�ҷ����� " << pos.first << ',' << pos.second << endl;
		//cout << *this << endl;
		return MAX_INT / 2;
	}//�ҷ�����
	else if ((change3 > 1)) {
		if ((!v3[3])) return MIN_INT / 10;
		/*	cout << "�Է�˫���� " << pos.first << ',' << pos.second << endl;
			cout << *this << endl; */
		return -50000;
	} //�Է�˫����

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
	//����ǰ
	int v0[7]{ 0 };
	int _v0[7]{ 0 };
	getShapes(v0, _v0);
	*/


	//ǰ
	int v[7]{ 0 };
	int _v[7]{ 0 };
	getShapes4(pos, v, _v);

	chess[pos.first][pos.second] = -1;

	//��
	int v2[7]{ 0 };
	int _v2[7]{ 0 };
	getShapes4(pos, v2, _v2);

	//cout << *this << endl;

	chess[pos.first][pos.second] = 0;
	int change3 = _v2[2] - _v[2];

	int change4 = _v2[1] - _v[1];

	int change34 = v[3] + v[4] - _v2[4] - _v2[3];
	//����
	int v3[7]{ 0 };
	int _v3[7]{ 0 };

	for (int i = 0; i < 7; i++) {
		v3[i] = v0[i] - v[i] + v2[i];
		_v3[i] = _v0[i] - _v[i] + _v2[i];
	}


	int score = 0;

	if (v3[0] || v3[1]) { /*cout << "�ҷ���5/��4/��4" << pos.first << ',' << pos.second << endl;
	cout << *this << endl;*/
		score += MAX_INT / 2;
	} //�ҷ���5/��4/��4
	else if (_v3[0]) {
		//cout << "�Է���4 " << pos.first << ',' << pos.second << endl;
		//cout << *this << endl; 
		score += MIN_INT / 10;
	}//�Է���4
	else if ((change3 + change4) > 1 && (change4)) {
		if ((!v3[2]) && (!v3[3])) score += MIN_INT;
		score -= 50000;
		//cout << "�Է�34 " << pos.first << ',' << pos.second<< endl;
		//cout << change3 << ' ' << change4 << endl;
		//
		//cout << *this << endl;

	} //�Է�34
	else if (v3[2] && (!_v3[1])) {
		//cout << "�ҷ����� " << pos.first << ',' << pos.second << endl;
		//cout << *this << endl;
		score += MAX_INT / 2;
	}//�ҷ�����
	else if ((change3 > 1)) {
		if ((!v3[3])) score += MIN_INT / 10;
		/*	cout << "�Է�˫���� " << pos.first << ',' << pos.second << endl;
			cout << *this << endl; */
		score -= 50000;
	} //�Է�˫����

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


void board::getShapes4(pair<int, int>& pos, int* v, int* _v) {
#ifdef DEBUG
	int t = clock();
#endif // DEBUG

	char* strs[4]{ 0 };
	toString4(strs, pos);
	//��ȡ��
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;
		int** vvv = shapeHashTable.getShape(strs[i]);
		for (int i = 0;i < 7;i++) {
			v[i] += vvv[0][i];
			_v[i] += vvv[1][i];
		}
	}

#ifdef DEBUG
	timeshape4 += clock() - t;
#endif // DEBUG
}