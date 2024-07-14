#include <memory.h>

#include "config.h"
#include "rule.h"
#include "evaluate.h"
#include"board.h"
#include"hashTable.h"

int main()
{

	board b;
	b.move(10, 0);
	b.move(10, 1);
	b.move(11, 0);
	b.move(11, 1);

	b.move(12, 1);
	b.move(13, 1);
	b.move(12, 2);
	b.move(14, 5);
	b.move(12, 3);

	cout << b << endl;
	
	for (int i = 0;i < 29;i++) {
		cout << b.strs[3][i] << endl;;
	}
	


	/*
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
	pair<int, int> p(5, 0);


	int v[7]{ 0 };
	int _v[7]{ 0 };


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




	/*
	strTree::initRoots();
	btzrule();
	delete tree1;
	delete tree2;
	*/

	return 0;
}