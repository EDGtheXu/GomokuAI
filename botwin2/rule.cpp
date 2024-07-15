#pragma GCC optimize(2)

#include "rule.h"


#include "board.h"
#include "config.h"





void btzrule() {
	strTree::initRoots();

	board mb;
	int x, y, n;
	int xf, yf;

	//恢复目前的棋盘信息
	cin >> n;
	
	
	for (int i = 0;i < n * 2 - 1;i++) {
		cin >> x >> y;
		if (!(x == -1 && y == -1)) {
			mb.move(x, y);

			cout<<mb.
			cout << mb << endl;
			cout << endl;
		}
	}

	strTree::initRoots();

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
#endif // 


cout << mb << endl;
	pair<int, int> p = mb.policy();
	cout << p.first << ' ' << p.second << endl;
	
	mb.move(p);
	cout << mb << endl;

#ifdef DEBUG_BOTZONE
	cout << "value:" << mb->lastValue << endl;
	cout << "time:"<<clock() - t << endl;
#endif // DEBUG_BOTZONE


#ifdef DEBUG_main
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
	cout << "nps:" << searchNode * 1000.0/ (clock() - t)  << endl;

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
