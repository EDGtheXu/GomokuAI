#include <memory.h>

#include "config.h"
#include "database.h"
#include "evaluate.h"
#include "hashTable.h"
#include "board.h"
#include "rule.h"





int main()
{








	/*
	strTree::initRoots();
	database db;

	db.init();

	board b;
	b.move(7, 7);
	b.move(7, 8);
	//b.move(7, 9);

	Pos res = db.readLine(b.historyMoves, b.moveCount);
	cout << res.first << ' ' << res.second << endl;


	return 0;

	*/

	/*
	strTree::initRoots();
	board b;
	b.move(1, 3);
	int vv[2][8]{ 0 };
	b.getShapes4(Pos(1, 3),vv);
	b.undo();
	*/


	/*
	strTree::initRoots();
	



	int arr[15][15]{
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1,-1, 1, 1,-1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0,-1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0,-1, 1, 1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 0, 0,
		0,-1,-1, 1, 1, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0,
		0,-1, 1,-1,-1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1,-1, 0, 1, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};



	for (int i = 0;i < 14;i++)
		for (int j = i+1;j < 15;j++) {
			//swap(arr[i][j], arr[j][i]);
			arr[i][j] += arr[j][i];
			arr[j][i] = arr[i][j] - arr[j][i];
			arr[i][j] -= arr[j][i];
			arr[i][j] = arr[i][j];
		}
			

	board* mb = new board(arr);
	cout << *mb << endl;
	strTree::initRoots();
	pair<int, int> p(5, 5);

	int vv[2][8]{ 0 };

	mb->getShapes4(p, vv);


	return 0;
	*/


	/*
	int tttt=clock();
	char* strs[4];
	
	char str[16] = "00000000000000";
	for (int i = 0;i < 1850000;i++) {
		mb->getShapes4(p, v, _v);
		//mb->toString4(strs, p);
		//tree1->get(str, v);
	}
		
	cout << clock() - tttt;
		
	
	return 0;
	*/

	/*

	board b;
	b.move(0, 0);
	
	cout << b << endl;;
	cout << b.turnToMove << endl;
	b.move(0, 1);
	cout << b << endl;;
	cout << b.turnToMove << endl;
	*/



	
	
	//btzrule();
	game();

	//shapeHashTable;
	//int t = clock();
	//char s[16] = "0111100//100";
	//for (int i = 0;i < 8500000;i++) {
	//	shapeHashTable.hashFunction(s);
	//	//strlen(s);
	//}
	//cout << clock() - t;
	return 0;
}