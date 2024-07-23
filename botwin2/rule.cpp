#pragma GCC optimize(2)

#include "rule.h"


#include "board.h"
#include "config.h"





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


void game() {

	//初始化字典树
	strTree::initRoots();
	//shapeHashTable.init();
	timereadtree = 0;
	timeshape4 = 0;
	shapeHashTable.hitCount = 0;
	shapeHashTable.unHitCount = 0;

	board mb;

	
	char r = '0';
	int h = 0;
	while (true)
	{

		cin >> r;
		if (r > 'a') r -= 32;

		if (r == 'T') {
			int t = clock();
			Pos p;
			if (mb.moveCount == 0)
				p = Pos(7, 7);
			else {
				p = mb.policy();

			}
			mb.move(p);

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
#endif // DEBUG_main
			timemove = 0;
			movecount = 0;
			TT.hitCount = 0;
			TT.unHitCount = 0;
			searchNode = 0;
			timeshape4 = 0;
			shape4count = 0;
			timetemp = 0;
			lcCount = 0;
		}
		else if (r == 'S')
		{
			cout <<"score : "<< mb.getScore() << endl;
		}
		else if (r == 'U') {
			mb.undo();
		}
		else {
			cin >> h;
			if (h <= 0 || h>15)continue;
			if (r > 'O' || r < 'A') continue;//输入不合法
			Pos p = Pos(r - 'A', 15 - h);
			mb.move(p);
		}


		cout << mb << endl;


	}



}