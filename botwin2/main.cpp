#include <memory.h>

#include "config.h"
#include "rule.h"
#include "evaluate.h"
#include"board.h"
#include"hashTable.h"

int main()
{

	
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

	strTree::initRoots();

	int v[7]{ 0 };
	int _v[7]{ 0 };
	mb->getShapes(v, _v);
	pair<int, int> p(7, 7);

	int tttt=clock();
	char* strs[4];
	
	char str[16] = "010011//01/1110";
	for (int i = 0;i < 850000;i++) {
		//mb->getShapes4(p, v, _v);
		mb->toString4(strs, p);
		//tree1->get(str, v);
	}
		
	cout << clock() - tttt;
		return 0;



	btzrule();

#ifdef DEBUG

#endif // DEBUG





	delete tree1;
	delete tree2;
	return 0;
}