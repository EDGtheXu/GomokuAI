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

			strsHash[0][i] |= (3 << j);
			strsHash[1][i] |= (3 << j);

			

		}
		for (int j = 0; j <= i; j++)
		{
			strs[2][i][j] = '0';
			strs[3][i][j] = '0';

			strs[2][28-i][j] = '0';
			strs[3][28-i][j] = '0';


			strsHash[2][i] |= (3 << j);
			strsHash[3][i] |= (3 << j);

			strsHash[2][28 - i] |= (3 << j);
			strsHash[3][28 - i] |= (3 << j);
		}
		endIndex[0][i] = 14;
		endIndex[1][i] = 14;
		endIndex[2][i] = i;
		endIndex[3][i] = i;
		endIndex[2][28-i] = i;
		endIndex[3][28-i] = i;

	}

	initStrIndexs();
	initZobrish();
}
board::board(const board& b)
{
	//memcpy(chess, b.chess, sizeof(chess));
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
	
	if (tte->depth == maxdept) return tte->value;//重复局面提前返回

	if (tte->value > 10000 || tte->value < -10000) {//必赢必输提前返回(应该加点判断)
		//cout << *this << endl;
		return tte->value;
	}



	//setp 4: 循环全部着法
	Pos* poss = tte->moves;
	int count = tte->moveCount;
	int rc = 0;
	int branch = 0;
	int maxBranch = getMaxBranch(depth);//每层最大分支数（递减）

	int maxValue = MIN_INT;
	int values[150]{ 0 };
	while (count--) {
		Pos& cur = poss[rc];
		//step 5: 启发式剪枝
		
		int vv[2][8]{ 0 };
		getShapes4(cur, vv);
		if (!checkImportantShapes4(cur) && depth<maxdept-1) {//该点无重要棋型
			int distance1 = distance(cur, *lastMove());
			int distance2 = distance(cur, *lastMove(2));
			bool isNear1 = distance1 <= 2 || isInLine(cur, *lastMove()) && distance1 <= 4;
			bool isNear2 = distance2 <= 2 || isInLine(cur, *lastMove(2)) && distance2 <= 4;

			if (maxValue > -10000) {// 超过最大分支数时
				if (branch > maxBranch) continue;
			}
			else {//失败局面检查更多分支
				if (branch > MAX(maxBranch, 50)) {
					bool isNear3 = distance(cur, *lastMove(3)) <= 4;
					if (!(isNear1 && isNear3)) 
						continue;
				}
			}

		}	 

		
		branch++;
		

		//step 6: ab
		move(poss[rc]);
		//cout << *this << endl;
		int t = -abSearch( depth + 1,  -beta,-alpha, maxdept);
		values[rc] = t;
		undo();


		//step 7: 时间控制
#ifdef TIME_CONTROL
		static int cmt = 7000;
		if (cmt-- < 0) {
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) terminal = true;
			cmt = 7000;
		}
		if (terminal) break;
#endif

		//step 8: ab剪枝
		maxValue = t > maxValue ? t : maxValue; 
		alpha = maxValue > alpha ? maxValue : alpha;

		if (maxValue >= beta) {
			
			break;
		}

		rc++;


	}
	if (terminal) return maxValue;



	//step 9: 更新置换表
	tte->value = maxValue;
	tte->depth = maxdept;
	if (tte->value > -10000 && tte->value < 10000) {
		tte->moveCount = TTrefresh(tte->moves, tte->moveCount, values);//重新排序
	}
	




	return maxValue;
}



// 决策
pair<int, int> board::policy()
{
	cout << *this << endl;
	//生成根节点着法
	pair<int, int> poss[150];
	int values[150]{ 0 };
	int count = genRoot(poss,values);
	int curmax = MIN_INT;
	Pos best = poss[0];
	Pos last = best;
	int maxv = -MIN_INT * 2;


	int rc = 0;
	int depth = 2;

	//迭代加深
	for (depth = START_DEPTH; depth <=MAX_DEPTH && !terminal; depth+=2)
	{
		int _count = count;
		rc = 0;
		curmax = MIN_INT;
		reachMaxDepth = 0;

#ifdef DEBUG_POLICY
			int steptime = clock();
#endif // DEBUG_POLICY
		while (_count--) {

			move(poss[rc]);

			//cout << *this << endl;
			int t = -abSearch(1, -MAX_INT , -curmax, depth);
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
		cout << "depth = " << depth <<"-" <<reachMaxDepth<< ", eval = " << curmax << ", best = (" << last.first << ", " << last.second << ")" << ", time = " << clock() - steptime << endl;
#endif // DEBUG_POLICY
		TTrefresh(poss, count, values);

	}

	
#ifdef DEBUG_POLICY
	cout << endl << "TOTAL:" << "max depth = " << min(depth,MAX_DEPTH) << ", eval = " << curmax << ", best = (" << last.first << ", " << last.second << ")" << endl;
	cout << "rc = " << rc << endl;
#endif // DEBUG_POLICY

	return best;
}


void board::getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]) {

#ifdef DEBUG
	int t = clock();
	shape4count += 1;
#endif // DEBUG

	char* nstrs[4]{};
	uint32_t hashstr[4]{ 0 };
	
	for (int i = 0;i < 4;i++) {
		int* ins = strIndexs[pos.first][pos.second][i];
		nstrs[i] = strs[i][ins[0]];
		hashstr[i] = strsHash[i][ins[0]];
	}


#ifdef DEBUG
	int tt = clock();
#endif // DEBUG

//读取树
	for (int i = 0;i < 4;i++) {
		int* ins = strIndexs[pos.first][pos.second][i];
		int indexStr = ins[0];
		int index = ins[1];
		int s = index > 5 ? index - 5 : 0;
		int e = endIndex[i][indexStr]-index>5?index+5: endIndex[i][indexStr];
		int len = e - s;
		int l = (endIndex[i][indexStr] - e)*2;
		int r = (2 * s + l);

		uint32_t mask = 0;
		for (int j = index-1;j >= s;j--) {
			if (nstrs[i][j] == '/')break;
mask <<= 2;
			mask &= 3;
			
		}
		for (int j = index + 1;j <= e;j++) {
			if (nstrs[i][j] == '/')break;
mask <<= 2;
			mask &= 3;
			
		}

		hashstr[i] <<= l;
		hashstr[i] >>= r;



		int** vvv = shapeHashTable.getShape(nstrs[i]+s,hashstr[i],len+1);

		for (int j = 0;j < SHAPE_TYPES;j++) {
			vv[0][j] += vvv[0][j];
			vv[1][j] += vvv[1][j];
		}
	}


#ifdef DEBUG
	timeshape4 += clock() - t;
	timereadtree += clock() - tt;
#endif // DEBUG
}

bool board::checkImportantShapes4(pair<int, int> pos) {

#ifdef DEBUG
	int t = clock();
	shape4count += 1;
#endif // DEBUG

	char* nstrs[4]{};
	uint32_t hashstr[4]{ 0 };

	for (int i = 0;i < 4;i++) {
		int* ins = strIndexs[pos.first][pos.second][i];
		nstrs[i] = strs[i][ins[0]];
		hashstr[i] = strsHash[i][ins[0]];
	}


#ifdef DEBUG
	int tt = clock();
#endif // DEBUG

	//读取树
	for (int i = 0;i < 4;i++) {
		int* ins = strIndexs[pos.first][pos.second][i];
		int indexStr = ins[0];
		int index = ins[1];
		int s = index > 5 ? index - 5 : 0;
		int e = endIndex[i][indexStr] - index > 5 ? index + 5 : endIndex[i][indexStr];
		int len = e - s;
		int l = (endIndex[i][indexStr] - e) * 2;
		int r = (2 * s + l);
		hashstr[i] <<= l;
		hashstr[i] >>= r;



		int** vvv = shapeHashTable.getShape(nstrs[i] + s, hashstr[i], len+1);

		for (int j = 0;j < SHAPE_TYPES - 1 ;j++) {
			if (vvv[0][j] || vvv[1][j]) {
#ifdef DEBUG
				timeshape4 += clock() - t;
				timereadtree += clock() - tt;
#endif // DEBUG
				return  true;
			}
		}
	}


#ifdef DEBUG
	timeshape4 += clock() - t;
	timereadtree += clock() - tt;
#endif // DEBUG
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



