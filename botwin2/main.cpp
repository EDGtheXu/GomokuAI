#include <memory.h>

#include "config.h"
#include "rule.h"
#include "evaluate.h"
#include"board.h"
#include"hashTable.h"

int main()
{

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

	*/



	/*
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

	/*
int tttt = clock();
	strTree::initRoots();
	hashTable ht;
	ht.init();

	cout << ht.getsize() << endl;
cout << "tttt=" << clock() - tttt << endl;

	char str[16] = "010111/0";
	int**vv = ht.getShape(str);
	for (int i = 0;i < 7;i++)
		cout << vv[0][i] << " " ;
	cout << endl;
	for (int i = 0;i < 7;i++)
		cout << vv[1][i] << " ";
	cout <<endl<< ht.getstate() << endl;


	char str2[16] = "010///010";
	vv = ht.getShape(str2);
	for (int i = 0;i < 7;i++)
		cout << vv[0][i] << " ";
	cout << endl;
	for (int i = 0;i < 7;i++)
		cout << vv[1][i] << " ";
	cout << endl << ht.getstate() << endl;


	hash<string> h;
	tttt = clock();
	for (int i = 850000;i > 0;i--) {
		//ht.getShape(str);
		
	}
	cout << "tttt=" << clock() - tttt << endl;


	tttt = clock();
	int  v[7]{ 0 };
	int _v[7]{ 0 };
	pair<int, int>pos(7,7);
	char* strs[4];
	for (int i = 850000;i > 0;i--) {
		//mb->getShapes4(pos, v, _v);
		mb->toString4(strs, pos);
	}
	cout << "tttt=" << clock() - tttt << endl;
	*/


	btzrule();

#ifdef DEBUG

#endif // DEBUG





	delete tree1;
	delete tree2;
	return 0;
}