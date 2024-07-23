#pragma once

#ifndef EVALUATE
#define EVALUATE




#include<vector>
#include<string>
#include<unordered_map>
#include"config.h"
using namespace std;







class strTree {
public:
	char c;
	char pumpChar = 0;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(const char* str, int v[SHAPE_TYPES]);
	//int getArea()



//初始化字典树
	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);
	
	static int readTree(strTree* root, char* strs[], int count, int v[SHAPE_TYPES]);
	static void initRoots();
	static int getScoreG(int vv[2][SHAPE_TYPES]);
	static int getScoreG(int *v,int*_v);
	static int getScoreSide(int* v);

	~strTree();
};

//全局敌我字典树
extern strTree* tree1;
extern strTree* tree2;






#endif // !EVALUATE