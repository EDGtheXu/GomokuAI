#include "board.h"
#include "config.h"
#include "evaluate.h"
#include "hashTable.h"


board::board():db(this)
{
	memset(chess, EMPTY, sizeof(chess));
	turnToMove = ME;
	turnToMoveOppo = -turnToMove;
	moveCount = 0;
	selfIndex = 0;
	oppoIndex = 1;

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
	db.init();
}
board::board(const board& b):db(this)
{
	//memcpy(chess, b.chess, sizeof(chess));
}
board::board(int chess[][15]):db(this) {


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
ostream& operator<<(ostream& os, board& b)
{
	//score
	/*
	os << "---------------Score-------------" << endl;
	os << "---  0 -  1 -  2 -  3 -  4 -  5 -  6 -  7 -  8 -  9 -  0 -  1 -  2 -  3 -  4 -" << endl;
	for (int i = 0; i < ROW; i++) {
		os.left;
		os.width(2);

		os << i % 10;

		for (int j = 0; j < COL; j++) {
			if (b.chess[j][i] == 1) {

				os << "| O  ";
			}
			else if (b.chess[j][i] == -1) {
				os.left;

				os << "| X  ";
			}
			else
			{
				int s = b.getLC4(Pos(j, i));
				os << "|";
				os.width(4);
				os << s;
			}

		}
		os << '|';
		os <<
#ifdef STD_OUT_FORM
			STD_OUT_Y(i)
#else
			i % 10
#endif // STD_OUT_FORM
			<< endl;
	}
#ifdef STD_OUT_FORM
	os << "---  A -  B -  C -  D -  E -  F -  G -  H -  I -  J -  K -  L -  M -  N -  O -" << endl;
#else
	os << "---0-1-2-3-4-5-6-7-8-9-0-1-2-3-4-" << endl;
#endif // STD_OUT_FORM

	os << "-------------Shape---------------" << endl;

	*/
	



	//
	os << "---0-1-2-3-4-5-6-7-8-9-0-1-2-3-4-" << endl;
	for (int i = 0; i < ROW; i++) {
		os.left;
		os.width(2);

		os << i % 10 ;

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
		os << '|' ;
		os <<
#ifdef STD_OUT_FORM
			STD_OUT_Y(i)
#else
			i % 10
#endif // STD_OUT_FORM
			<<endl;
	}
#ifdef STD_OUT_FORM
	os << "---A-B-C-D-E-F-G-H-I-J-K-L-M-N-O-" << endl;
#else
	os << "---0-1-2-3-4-5-6-7-8-9-0-1-2-3-4-" << endl;
#endif // STD_OUT_FORM

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

int board::VCFSearch() {

	searchNode++;
	//cout << *this << endl;
	//step 1: 提前胜负判断
	int winFlag = quickWinCheck();
	if (winFlag)
		return MAX_INT * winFlag;


	//step 2: 深度限制
	

	if (VCFdepth == MAX_VCF_DEPTH) return 0;
	//step 3：查找置换表
	Move* tte = TT.find(zobristKey);


	if (tte  && tte->valueType==value_type_VCF) {//命中置换表
		return tte->value;
	}

	VCFdepth++;
	Pos moves[225];
	int winlossFlag = 0;
	Pos best;
	if (turnToMove == vcfAttacker) {//进攻方走法
		int mc = genVCFAttackMove(moves);
		int rc = 0;

		while (mc--) {
			move(moves[rc]);
			//cout << *this << endl;
			winlossFlag = -VCFSearch();

			undo();
			if (winlossFlag > 10000) {
				if (VCFdepth == 1) {
					//cout << *this << endl;
					int aa = 1;
				}
				best = moves[rc];
				break;
			}
			rc++;
		}


	}
	else {//防守方走法
		int mc = genVCFDefendMove(moves);
		if (mc == 0) winlossFlag = MIN_INT;
		int rc = 0;

		while (mc--) {
			move(moves[rc]);
			//cout << *this << endl;
			winlossFlag = -VCFSearch();

			undo();
			if (winlossFlag > -10000)
				if (VCFdepth == 2) {
					//cout << *this << endl;
					int aa = 1;
				}
				break;
			rc++;
		}
	}

	if(!tte)
		tte = new Move();

	//置换表保存
	tte->value = winlossFlag;//可以记录必输的和必胜的
	TT.AddItem(zobristKey,tte);


	//if (vcfAttacker == turnToMove && winlossFlag > 10000) {
		tte->bestMove = best;
		tte->valueType = value_type_VCF;
	//}

	VCFdepth--;


	if (winlossFlag) return winlossFlag;
	return 0;
}




int board::abSearch(int depth, int alpha, int beta, int maxdept)
{
	searchNode++;
#ifdef DEBUG_ABS

#endif // DEBUG_ABS
	//cout << *this << endl;
#ifdef DEBUG
	reachMaxDepth = reachMaxDepth > depth ? reachMaxDepth : depth;
#endif // DEBUG
#ifdef DEBUG_BOTZONE
	reachMaxDepth = reachMaxDepth > depth ? reachMaxDepth : depth;
#endif

	//step 1: 提前胜负判断
	int winFlag = quickWinCheck();
	if (winFlag)
	{
		return MAX_INT * winFlag;
	}

	bool debugLay = (	
		depth == 3&&
		chess[13][7]==1&&
		chess[9][10] == -1&&
		chess[5][6]==1
		// lastMove()->first == 7 && lastMove()->second == 11
		//&& lastMove(2)->first == 9 && lastMove(2)->second == 9
		//&& lastMove(3)->first == 1 && lastMove(3)->second == 10
	);
	if (debugLay) {
		//cout << *this << endl;

		int aa = 1;
	}
	

		int score = getScoreOneStep()		//当前步得分
			//+turnValeDelta				//修正奇数层差值
			//- posScore * posScoreMulti	//位置得分
			;
		score = score * curentMulti - staticValues[depth - 1];
	//step 2： VCF
	if (depth ==maxdept) {
		//return score;
		//cout << *this << endl;
		int turnIndex = piece();
		VCFdepth = 0;
		int posScore = (ABS(7 - lastMove()->first) + ABS(7 - lastMove()->second));




		
		if (turnToMove == policy_turn) {//下一步是我方
			if (oppoShape()[C4]  == 0 && myShape()[H3]+myShape()[C3]+myShape()[Q3]>0) {
				vcfAttacker = turnToMove;

				if (depth == 2 &&
					chess[3][11] == -1 && chess[1][9] == 1) {
					int aa = 1;
				}

				int vcfScore = VCFSearch();//我有VCF
				if (vcfScore > 10000) {
				
					return vcfScore;
				}
					
			}

		}
		else//下一步是对方
		{
			if (myShape()[C4]==0 && oppoShape()[H3]+oppoShape()[Q3]+oppoShape()[C3]>0) {//对方有VCF
				
				vcfAttacker = turnToMove;
				int vcfScore = VCFSearch();

				if (vcfScore >10000) {

					return vcfScore;
				}
					
			}

		}
		

		//vcf未杀，取局面估值

//cout << *this << endl;
		return score;

	}
	else if (depth == maxdept) {
		return score;
	}


	

	int staticValue = getScore();//静态估值
	staticValues[depth] = staticValue;

	//step 3：查找置换表
	Move* tte = TT.find(zobristKey);


	if (!tte ||//未命中置换表
		tte && tte->valueType == 0 ||//值不合理
		tte && tte->valueType== ValueType::value_type_VCF) {//vcf要重新获取moves

		if(!tte) tte = new Move();
		if (tte->valueType == value_type_VCF && tte->value >10000) return tte->value;//vcf有杀直接返回

		int c = genAreaAll(tte->moves);
#ifdef FULLSEARCH
		tte->moveCount = c;
#else
		tte->moveCount  = LC(tte->moves, c);//启发策略
#endif
		tte->value = staticValue;
		tte->valueType = ValueType::value_type_ab;
		TT.AddItem(zobristKey, tte);
	}
	else if(tte ){//命中
		if (tte->valueType!=0 &&( tte->value > 10000 || tte->value < -10000 && tte->turn == turnToMove)) {//必赢必输提前返回(应该加点判断)
			//cout << *this << endl;
			return tte->value;
		}
		if (tte->depth ==maxdept &&tte->step  == moveCount  && tte->valueType!=value_type_unvalid) 
			return tte->value;//同一次决策中重复局面提前返回
	}






	//setp 4: 循环全部着法
	Pos* poss = tte->moves;
	int count = tte->moveCount;
	int rc = -1;
	int branch = 0;
	int maxBranch = getMaxBranch(depth);//每层最大分支数（递减）

	int maxValue = MIN_INT;

	while (count--) {
		rc++;
		Pos& cur = poss[rc];

		//step 5: 启发式剪枝

		if (!checkImportantShapes4(cur) && depth!=maxdept) {//该点无重要棋型
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
		//
		if (depth == 4) {
			//cout << *this << endl;
			int aa = 1;
		}

		int t = -abSearch(depth + 1, -beta, -alpha, maxdept);
		tte->values[rc] = t;
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
			bestMove = poss[rc];

			break;
		}



	}
	if (terminal) return maxValue;



	//step 9: 更新置换表

	tte->value = maxValue;
	tte->valueType = ValueType::value_type_ab;
	tte->depth = maxdept;
	tte->step = moveCount;
	if (tte->value > -10000 && tte->value < 10000) {
		tte->moveCount = TTrefresh(tte->moves, tte->moveCount, tte->values);//重新排序
		tte->turn = turnToMove;
		tte->bestMove = bestMove;
	}

	if (depth == 1) {
		//cout << *this << endl;
		int aa = 1;
	}



	return maxValue<0?maxValue+1: maxValue-1;
}



// 决策
pair<int, int> board::policy()
{
#ifdef TIME_CONTROL
	TIMEBEGIN = clock();

#endif






	//深度优先算杀
	VCFdepth = 0;
	vcfAttacker = turnToMove;
	int dfs = VCTSearch();



	//置换表查询
	TTEntrace* tte = TT.find(zobristKey);
	//Pos dbp = db.readLine(historyMoves, moveCount);
	if (tte) {

		if (tte->valueType == ValueType::value_type_db) {//开局库存在
			Pos bestDbMove = tte->moves[0];
			int eval = 255;

			for (int i = 0;i < tte->moveCount;i++) {
				move(tte->moves[i]);
				
				TTEntrace* temp = TT.find(zobristKey);
				
				if (temp && temp->dbWiner == turnToMove) {
					if (eval > temp->dbEval) {//胜利方选最短值
						eval = temp->dbEval;
						bestDbMove = tte->moves[i];
					}
	
				}
				if (temp && eval == 255 && temp->dbWiner != turnToMove) {
					if ((-eval) < temp->dbEval) {//失败方选最大值
						eval = -temp->dbEval;
						bestDbMove = tte->moves[i];
					}
				}
				undo();
				
			}
			cout << "from database" << endl;
			cout << " best = (" <<
#ifdef STD_OUT_FORM
				STD_OUT_X(bestDbMove.first)
#else
				bestMove.first
#endif // STD_OUT_FORM
				<< ", " <<
#ifdef STD_OUT_FORM
				STD_OUT_Y(bestDbMove.second)
#else
				bestMove.second
#endif // STD_OUT_FORM
				<< ") " << "eval="<< eval << endl;
			return bestDbMove;

		}
		else if (tte->valueType == ValueType::value_type_VCF) {
			if (tte->value > 10000) {
				bestMove = tte->bestMove;

				cout << "from VCF in hashtable" << endl;
				return bestMove;
			}
		}
		else if (tte->valueType == ValueType::value_type_ab) {
			if (tte->value > 10000 || tte->value<-10000) {
				bestMove = tte->bestMove;

				cout << "from ab in hashtable" << endl;
				return bestMove;
			}
		}
		
	}



	terminal = false;

	//生成根节点着法
	Pos poss[225];
	int values[225]{ 0 };
	int count = genRoot(poss, values);//要根节点排序
	int curmax = MIN_INT;
	Pos best = poss[0];
	this->policy_turn = turnToMove;
	int maxv = 0;
	int starttime = clock();

	int rc = 0;
	int depth = 2;


	if (values[0] < -10000) {//下一步提前判断输
		cout << "quick loss" << endl;
		return poss[0];
	}
	







	//迭代加深
	Pos layBest;//保存层结果，bestValue会改变
	Pos laySeq[225];//层排序
	for (depth = START_DEPTH; depth <= MAX_DEPTH && !terminal; depth +=1)
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
			int t = -abSearch(1, -MAX_INT, -curmax, depth);
			values[rc] = t;
			undo();


#ifdef TIME_CONTROL
			if (clock() - TIMEBEGIN > MAX_SEARCH_TIME_MS) terminal = true;
			if (terminal)break;
#endif
			//cout <<"pol:("<< poss[rc].first << " , "<<poss[rc].second << ") , eval:" << t <<endl;
			if (t > curmax)
			{
				curmax = t;
				best = poss[rc];
				maxv = t;
			}
			rc++;


		}

		count = Rootfresh(poss, count, values);

#ifdef TIME_CONTROL
		if (terminal) {
			bestMove = layBest;
			break;
		}
#endif
		//层保存
		bestMove = best;
		bestVelue = curmax;
		layBest = best;
		memcpy(laySeq, poss, sizeof(Pos) * count);
		//输出层结果
#ifdef DEBUG_POLICY
		cout << "depth = " << depth << "-" << reachMaxDepth << ", eval = " << bestVelue << ", best = (" << 
#ifdef STD_OUT_FORM
			STD_OUT_X(bestMove.first)
#else
			bestMove.first
#endif // STD_OUT_FORM
			
			<< ", " << 
#ifdef STD_OUT_FORM
			STD_OUT_Y(bestMove.second)
#else
			bestMove.second
#endif // STD_OUT_FORM
			<< ")" << ", time = " << clock() - steptime << endl;
#endif // DEBUG_POLICY

		if (bestVelue > 10000) {
			depth++;break;
		}

		/*


		if (START_DEPTH == depth && curmax > 10000) {//第一步就赢了
			rc = 0;
			_count = count;
			curmax = 0;
			while (_count--) {

				move(poss[rc]);
				int t = -quickWinScore();
				values[rc] = t;
				undo();

				if (t > curmax)
				{
					curmax = t;
					best = poss[rc];
				}
				rc++;


			}
			if (curmax > 10000)
				break;
		}
		count = TTrefresh(poss, count, values);
		*/
	}










	//输出结果
#ifdef DEBUG_POLICY
	cout << endl << "TOTAL:" << "max depth = " << depth - 1 << ", eval = " << bestVelue <<
		", best = (" << 
#ifdef STD_OUT_FORM
		STD_OUT_X(bestMove.first)
#else
		bestMove.first 
#endif // STD_OUT_FORM
		<< ", " << 
#ifdef STD_OUT_FORM
		STD_OUT_Y(bestMove.second)
#else
		bestMove.second
#endif // STD_OUT_FORM
		<< "), " <<"all time = " << clock()-starttime<<endl;

	cout << "rc = " << rc << endl;
#endif // DEBUG_POLICY


	//五手两打输出
#ifdef STEP5_OUT_N
	if (moveCount == 4)
		for (int i = 0;i < STEP5_OUT_N;i++) {
			cout << "(" << 
#ifdef STD_OUT_FORM
				STD_OUT_X(laySeq[i].first)
#else
				poss[i].first
#endif // STD_OUT_FORM
				<< ", " <<
#ifdef STD_OUT_FORM
				STD_OUT_Y(laySeq[i].second)
#else
				poss[i].second
#endif // STD_OUT_FORM
				<< ")" << endl;
		}
#endif // STEP5_OUT_N


	return bestMove;
}



void board::getShapes4(pair<int, int> pos, int vv[2][SHAPE_TYPES]) {

#ifdef DEBUG
	int t = clock();
	shape4count += 1;
#endif // DEBUG

	char* nstrs[4]{};

	for (int i = 0;i < 4;i++)
		nstrs[i] = strs[i][strIndexs[pos.first][pos.second][i][0]];


#ifdef DEBUG
	int tt = clock();
#endif // DEBUG

	//读取树
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;

		int** vvv = shapeHashTable.getShape(nstrs[i]);

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

	for (int i = 0;i < 4;i++)
		nstrs[i] = strs[i][strIndexs[pos.first][pos.second][i][0]];


#ifdef DEBUG
	int tt = clock();
#endif // DEBUG
	int count = 0;
	//读取树
	for (int i = 0;i < 4;i++) {
		if (!strs[i])continue;

		int** vvv = shapeHashTable.getShape(nstrs[i]);

		for (int j = 0;j < SHAPE_TYPES - 1;j++) {
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
	int scoreMe = strTree::getScoreSide(shapes[0]);
	int scoreOppo = strTree::getScoreSide(shapes[1]);

	if (turnToMove == ME) {
		
		return scoreMe - scoreOppo ;
	}
	else {

		return scoreOppo - scoreMe ;
	}

}

int board::getScoreDelta() {
	int scoreMe = strTree::getScoreSide(shapesChange[0]);
	int scoreOppo = strTree::getScoreSide(shapesChange[1]);
	if (turnToMove == ME) {

		return scoreMe * defendMulti - scoreOppo ;
	}
	else {

		return scoreOppo * defendMulti - scoreMe ;
	}

}

int board::getScoreOneStep() {

	int scoreMe = strTree::getScoreSide(shapesChange[0]);
	int scoreOppo = strTree::getScoreSide(shapesChange[1]);

	if (turnToMove == ME) {

		return scoreMe * defendMulti- scoreOppo ;
	}
	else {

		return scoreOppo  * defendMulti- scoreMe;
	}
}

int board::VCTSearch() {
	searchNode++;
	bool debug =0;
	if(debug) cout << *this << endl;
	//step 1: 提前胜负判断
	int winFlag = quickWinCheck();
	if (winFlag)
		return MAX_INT * winFlag;


	//step 2: 深度限制


	if (VCFdepth >= MAX_VCT_DEPTH) {
		return 0;
	}

	//step 3：查找置换表
	Move* tte = TT.find(zobristKey);

	if (tte  && tte->valueType == value_type_VCF) {//命中置换表

		return tte->value;
	}
	VCFdepth++;
	Pos moves[225];
	Pos best;
	int winlossFlag = 0;
	if (turnToMove == vcfAttacker) {//进攻方走法

		int mc = genVCTAttackMove(moves);

		int rc = 0;

		while (mc--) {
			move(moves[rc]);
			//if(debug) cout << *this << endl;
			//if (
			//	chess[6][14]==-1 &&
			//	
			//	chess[5][13] == 1


			//	) {

			//	int aa = 1;
			//}

			winlossFlag = -VCTSearch();


				if (VCFdepth == 1) {
					cout << *this << endl;
					int aa = 1;
				}
			undo();



			if (winlossFlag > 10000) {//进攻方有一个点能杀即可

				best = moves[rc];
				break;
			}
			rc++;
		}


	}
	else {//防守方走法
		winlossFlag = MIN_INT;
		int mc = genVCTDefendMove(moves);

		int rc = 0;

		while (mc--) {
			move(moves[rc]);
			if(debug)cout << *this << endl;
			winlossFlag = -VCTSearch();

			undo();
			if (winlossFlag > -10000) {//防守方有一个点能防守即可
				if (VCFdepth == 2) {
					//cout << *this << endl;
					int aa = 1;
				}
				break;
			}
			rc++;
		}
	}

	if (!tte)
		tte = new Move();

	tte->value = winlossFlag;
	tte->turn = turnToMove;
	TT.AddItem(zobristKey, tte);

	//置换表保存
	if (vcfAttacker == turnToMove && winlossFlag > 10000) {

		tte->bestMove = best;
		tte->valueType = value_type_VCF;
	}


	VCFdepth--;
	if (winlossFlag) return winlossFlag;
	return 0;


}