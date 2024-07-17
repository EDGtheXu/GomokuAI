#include "board.h"
#include "config.h"
#include "evaluate.h"
#include "hashTable.h"


board::board()
{
	memset(chess, EMPTY, sizeof(chess));
	memset(rchess, EMPTY, sizeof(rchess));
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

// 重载输出
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
	
#endif // DEBUG_ABS
//cout << *this << endl;
#ifdef DEBUG
	reachMaxDepth = reachMaxDepth > depth ? reachMaxDepth : depth;
#endif // DEBUG

	
	//step 1: 提前胜负判断
	int winFlag = quickWinCheck();
	if (winFlag)
		return MAX_INT * winFlag;

	

	//step 2： VCF
	if (depth == maxdept) {
		//cout << *this << endl;



		return getScore();

		/*
			board* nbb = this->reverse();
			int v0[7]{ 0 };
			int _v0[7]{ 0 };
			nbb->getShapes(v0, _v0);//冲四或活四直接赢 
			if (_v0[0] || _v0[1]) {
				return ((int)p) * MAX_INT;

			}
			if (v0[1]) return -((int)p) * MAX_INT;  //对方活四 


			pair<int, int>poss[150];
			int count = getAllPossiblePos1(p, depth, poss);

			//估值

				 //int min = MAX_INT;
			int max = MIN_INT;
			int rc = 0;
			while (count--) {

				nbb->chess[poss[rc].first][poss[rc].second] = -(int)p;
				chess[poss[rc].first][poss[rc].second] = p;


				int t;


				//进攻方走冲四活三，扩展1层
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

			*/

	}






	//step 3：查找置换表
	Move* tte = TT.find(zobristKey);
	

	if (!tte) {//未命中置换表
		tte = new Move();
		int staticValue = getScore();//静态估值
		int c = genAreaAll(tte->moves);
#ifdef FULLSEARCH

		tte->moveCount = c;
#else
		tte->moveCount = LC(tte->moves, c);//启发策略
#endif
		tte->value = staticValue;
		TT.AddItem(zobristKey, tte);
	}
	if (tte->value > 10000 || tte->value < -10000) {//必赢必输提前返回
		//cout << *this << endl;
		return tte->value;
	}

	//setp 4: 循环全部着法
	Pos* poss = tte->moves;
	int count = tte->moveCount;
	int rc = 0;

	int max = MIN_INT;
	int values[150]{ 0 };
	while (count--) {

		//step 5: 启发式剪枝

		Pos& cur = poss[rc];
		move(poss[rc]);

		//step 6: ab
		
		int t = -abSearch( depth + 1,  -beta,-alpha, maxdept);
		values[rc] = t;
		undo();


		//step 7: 时间控制
#ifdef TIME_CONTROL
		if (terminal) break;
#endif

		//step 8: ab剪枝
		max = t > max ? t : max; 
		alpha = max > alpha ? max : alpha;

		if (max >= beta) {
			//cout << *this << endl;
			break;
		}

		rc++;


	}
	if (terminal) return max;



	//step 9: 更新置换表
	tte->value = max;
	if (tte->value > -10000 && tte->value < 10000) {
		tte->moveCount = TTrefresh(tte->moves, tte->moveCount, values);
	}
	if (max<1000 && max>-1000) {
		
	}




	return max;
}



// 决策
pair<int, int> board::policy()
{
	
	//生成根节点着法
	pair<int, int> poss[150];
	int values[150]{ 0 };
	int count=genAreaAll(poss);
	
	count = LC(poss, count);
	
	int curmax = MIN_INT;
	pair<int, int> best = poss[0];
	int maxv = -MIN_INT * 2;


	int rc = 0;
	int depth = 2;
	//迭代加深
	for (depth = START_DEPTH; depth <=MAX_DEPTH; depth++)
	{
		int _count = count;
		rc = 0;
		curmax = MIN_INT;
		reachMaxDepth = 0;
#ifdef DEBUG_POLICY
			int steptime = clock();
#endif // DEBUG_POLICY
		while (_count--) {
			/*
			if (values[rc] < -10000) {//必输点
				rc++;
				//cout << *this << endl;
				continue;
			}
			else if (values[rc] > 10000) {//必胜点
				rc++;
				//cout << *this << endl;
				continue;
			}
			*/
			move(poss[rc]);

			//cout << *this << endl;
			int t = -abSearch(1, -MAX_INT , -curmax, depth);
			values[rc] = t;
			undo();


#ifdef TIME_CONTROL
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) terminal = true;
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
		cout << "depth = " << depth <<"-" <<reachMaxDepth<< ", eval = " << curmax << ", best = (" << best.first << ", " << best.second << ")" << ", time = " << clock() - steptime << endl;
#endif // DEBUG_POLICY

	}

	
#ifdef DEBUG_POLICY
	cout << endl << "TOTAL:" << "max depth = " << min(depth,MAX_DEPTH) << ", eval = " << curmax << ", best = (" << best.first << ", " << best.second << ")" << endl;
	cout << "rc = " << rc << endl;
#endif // DEBUG_POLICY

	//cout<<"time1:"<<time1<<endl;

	return best;
}


void board::getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]) {
#ifdef DEBUG
	int t = clock();
	shape4count+=1;
#endif // DEBUG

	uint32_t indexs = getStrIndexs(pos);

	char* nstrs[4]{};
	
	nstrs[3] = strs[3][indexs & 255];
	indexs >>= 8;
	nstrs[2] = strs[2][indexs & 255];
	indexs >>= 8;
	uint8_t x2 = indexs & 255;
	nstrs[1] = strs[1][x2];
	indexs >>= 8;
	uint8_t x1 = indexs & 255;
	nstrs[0] = strs[0][x1];

#ifdef DEBUG
	int tt = clock();
#endif // DEBUG

	uint8_t inds[4]{ x2,x1,x1 > x2 ? x2 : x1,x1 + x2 < 14 ? x1 : 14 - x2 };
//读取树
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;
		DoubleShape vvv = shapeHashTable.getShape(nstrs[i],inds[i]);
		for (int i = 0;i < SHAPE_TYPES;i++) {
			vv[0][i] += vvv[0][i];
			vv[1][i] += vvv[1][i];
		}
	}


#ifdef DEBUG
	timeshape4 += clock() - t;
	timereadtree += clock() - tt;
#endif // DEBUG
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



