#pragma GCC optimize(2)
#include <future>
#include "rule.h"
#include "board.h"


#ifdef TIMER_CLOCK
#include <easyx.h>
#endif // TIMER_CLOCK





void btzrule() {
	//初始化字典树
	strTree::initRoots();
	//shapeHashTable.init();
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
	//开局设置
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
#endif // 



	pair<int, int> p = mb.policy();
	cout << p.first << ' ' << p.second << endl;


#ifdef DEBUG_BOTZONE
	cout << "depth:" << reachMaxDepth << " value:" << mb.bestVelue << " time:" << clock() - t << endl;
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
	cout << "nps:" << TT.getsize() * 1000.0/ (clock() - t)  << endl;

	cout << "timeshape=" << timeshape << endl;
	cout << "timeshape4=" << timeshape4 << endl;
	cout << "shape4Count=" << shape4count << endl;
	cout << "shapehash hit/unhit:" << shapeHashTable.hitCount << "/" << shapeHashTable.unHitCount << endl;
	cout << "TTE hit/unhit:" << TT.hitCount << "/" << TT.unHitCount << endl;

	cout <<"lc count : " << lcCount << endl;
#endif // DEBUG_main

	delete tree1;
	delete tree2;
	return;
}


bool pauseTime = true;
#ifdef TIMER_CLOCK
void timerThread() {
	initgraph(250, 100);
	settextstyle(60, 30,"宋体");
	settextcolor(RGB(255, 255, 0));
	cout << "init timer" << endl;
	int mm = 15;
	int begin = clock();
	int tempClock = begin;
	int lastss = 0;
	
	while (1) {

		if (pauseTime) {
			tempClock = clock();
			while (pauseTime) {

				Sleep(100);
			}
			begin += (clock() - tempClock);
		}
		int nowms = clock() - begin;
		int ss = (nowms / CLOCKS_PER_SEC);
		if (ss <= lastss) {
			Sleep(100);
			continue;
		}
		lastss = ss;
		int mm = ss / 60;
		ss %= 60;
		char str[20]{ 0 };
		if (mm < 10) str[0] = '0';
		char tempstr[3]{ 0 };
		strcat(str, itoa(mm, tempstr, 10));
		strcat(str, " : ");
		if (ss < 10) strcat(str, "0");
		strcat(str, itoa(ss, tempstr, 10));

		outtextxy(20, 20, str);

		//cout << str << endl;
	}


}
#endif


void game() {




	//初始化字典树
	strTree::initRoots();
	initZobrist();
	//shapeHashTable.init();
	timereadtree = 0;
	timeshape4 = 0;
	shapeHashTable.hitCount = 0;
	shapeHashTable.unHitCount = 0;

	board mb;
	

#ifdef TIMER_CLOCK
	future<void> ttt = async(timerThread);
#endif

	
	board mmb = mb;	
	char r = '0';
	int h = 0;
	while (true)
	{

		cin >> r;
		if (r >= 'a') r -= 32;

		if (r == 'T') {
			if (!mb.checkBoard()) {
				continue;
			}
			int t = clock();
			Pos p;
			if (mb.moveCount == 0)
				p = Pos(7, 7);
			else {
				pauseTime = false;
				p = mb.policy();
				pauseTime = true;
			}
			mb.move(p);
			cout << mb << endl;
			cout << STD_OUT_X(p.first) << ", " << STD_OUT_Y(p.second) << endl;
			
			/*

#ifdef DEBUG_main
			cout << "timemove=" << timemove << endl;
			cout << "movecount=" << movecount << endl;
			cout << "timeReadTree=" << timereadtree << endl;
			cout << "timetemp=" << timetemp << endl;
			cout << "search node:" << searchNode << endl;
			cout << "max depth:" << reachMaxDepth << endl;
			cout << "nps:" << searchNode * 1000.0 / (clock() - t) << endl;
			cout << "timeshape4=" << timeshape4 << endl;
			cout << "shape4Count=" << shape4count << endl;
			cout << "shapehash hit/unhit:" << shapeHashTable.hitCount << "/" << shapeHashTable.unHitCount << endl;
			cout << "TTE hit/unhit:" << TT.hitCount << "/" << TT.unHitCount << endl;
			cout << "all time:" << clock() - t << endl;
			cout << "lc count : " << lcCount << endl;

			timemove = 0;
			movecount = 0;
			TT.hitCount = 0;
			TT.unHitCount = 0;
			searchNode = 0;
			timeshape4 = 0;
			shape4count = 0;
			timetemp = 0;
			lcCount = 0;
#endif // DEBUG_main			

			*/
		}
		else if (r == 'U') {
			mb.undo();
			cout << mb << endl;
		}
		else if (r == 'Z') {
			string s=mb.stdHistoryMove();
			continue;
		}
		else if (r == 'P') {
			pauseTime = !pauseTime;
			continue;
		}
		else if (r=='S') {
			cout << "start 五手n打" << endl;
			cin >> r;
			cin >> h;

#ifdef STEP5_OUT_N
			if (mb.moveCount == 4) {

				Pos* t_pos = new Pos[STEP5_OUT_COUNT];
				int t = 0;
				int t_v = MIN_INT;
				int i = 0;
				while (1) {
					if (h <= 0 || h > 15)continue;
					if (r > 'O' || r < 'A') continue;//输入不合法

					t_pos[i] = Pos(r - 'A', 15 - h);
					mb.move(t_pos[i]);
					int tt = -mb.getScore();
					cout << tt << endl;
					mb.undo();
					if (t_v > tt) {
						t_v = tt;
						t = i;
					}

					i++;
					if (i >= STEP5_OUT_COUNT) break;

					cin >> r;
					cin >> h;
				}
				cout << "五手n打" << endl;
				cout << "选择：(" <<
#ifdef STD_OUT_FORM
					STD_OUT_X(t_pos[t].first)
#else
					t_pos[t].first
#endif // STD_OUT_FORM
					<< ", " <<
#ifdef STD_OUT_FORM
					STD_OUT_Y(t_pos[t].second)
#else
					t_pos[t].second
#endif // STD_OUT_FORM
					<< ")" << endl;
				mb.move(t_pos[t]);
				cout << mb << endl;
				delete t_pos;
				continue;
			}
#endif // STEP5_OUT_N
			if (h <= 0 || h > 15)continue;
			if (r > 'O' || r < 'A') continue;//输入不合法
			Pos p = Pos(r - 'A', 15 - h);
			cout << "end s" << endl;
			mb.move(p);
		}

		else {
			if (r > 'O' || r < 'A') {
				cout << "invalid char" << endl;
				continue;//输入不合法
			}
			cin >> h;
			if (h <= 0 || h > 15) {
				cout << "invalid int" << endl;
				continue;
			}
			if (mb.chess[r - 'A'][15 - h]) {
				cout << "exist" << endl;
				continue;
			}
			

			mb.move(r-'A',15-h);
			cout << mb << endl;
		}
		

		mb.checkBoard();
	}

}