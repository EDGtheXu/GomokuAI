#include <memory.h>

#include "config.h"
#include "rule.h"
#include "evaluate.h"

int main()
{

	strTree::initRoots();

	/*
	int arr[15][15]{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,-1, 0, 0, 0,-1,-1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,-1, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 0,-1, 0,-1, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0,-1, 1, 1, 1, 1,-1, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 1,-1,-1,-1,-1, 1, 0, 0, 0,
		0, 0, 0, 0, 0,-1, 0, 1,-1, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
	board* mb = new board(arr);
	//mb = mb->reverse();
	cout << *mb << endl;


	int v[7]{ 0 };
	int _v[7]{ 0 };
	pair<int, int> pqos =pair<int,int>(1, 1);
	mb->getShapes(v, _v);
	mb->getScoreP(pqos,v,_v);



	pair<int, int> pos = mb->policy(playerEnum::ME);
	cout << pos.first << ' ' << pos.second << endl;


	*/

	btzrule();

#ifdef DEBUG

#endif // DEBUG

	cout << "timeshape=" << timeshape << endl;
	cout << "timeshape4=" << timeshape4 << endl;
	return 0;
}