#pragma GCC optimize(2)

#include "rule.h"


#include "board.h"
#include "config.h"





void btzrule() {
	//初始化字典树
	strTree::initRoots();
	shapeHashTable.init();
	timereadtree = 0;
	shapeHashTable.hitCount = 0;
	shapeHashTable.unHitCount = 0;


	cout << "over" << endl;

	board mb;
	int x, y, n;

	//恢复目前的棋盘信息
	cin >> n;
	
	
	for (int i = 0;i < n * 2 - 1;i++) {
		cin >> x >> y;
		if (!(x == -1 && y == -1)) {
			mb.move(x, y);
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
	cout << "value:" << mb->lastValue << endl;
	cout << "time:"<<clock() - t << endl;
#endif // DEBUG_BOTZONE


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
#endif // DEBUG_main

	delete tree1;
	delete tree2;
	return;
}
