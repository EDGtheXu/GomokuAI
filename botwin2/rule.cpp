#pragma GCC optimize(2)

#include "rule.h"


#include "board.h"
#include "config.h"





void btzrule() {
	int b[15][15] = { 0 };//本方1，对方-1，空白0
	int x, y, n;
	int xf, yf;

	//恢复目前的棋盘信息
	cin >> n;
	cin >> x >> y;
	if (x == -1) {
		if (n == 1) {
			cout << 1 << ' ' << 7 << endl; return;
		}
		else {
			cin >> xf >> yf;
			cin >> x >> y;
			if (x == -1) {
				b[xf][yf] = -1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}
			else {
				b[x][y] = -1;
				b[xf][yf] = 1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}
		}
	}
	else {
		if (n == 1) {
			b[x][y] = -1;
			if (x >= 2 && x <= 12 && y >= 2 && y <= 12) {
				cout << -1 << ' ' << -1 << endl;
				return;
			}
		}
		else {
			cin >> xf >> yf;
			if (xf == -1) {
				b[x][y] = 1;
				cin >> x >> y;
				b[x][y] = -1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}
			else {
				b[x][y] = -1;
				b[xf][yf] = 1;
				cin >> x >> y;
				b[x][y] = -1;
				for (int i = 0; i < n - 2; i++) {
					cin >> x >> y;
					b[x][y] = 1;
					cin >> x >> y;
					b[x][y] = -1;
				}
			}

		}

	}


	board* mb = new board(b);
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



	pair<int, int> p = mb->policy(ME);
	cout << p.first << ' ' << p.second << endl;


#ifdef DEBUG_main



	cout << *mb << endl;
	mb->chess[p.first][p.second] = 1;
	cout << *mb << endl;
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
#endif // DEBUG_main
	return;
}
