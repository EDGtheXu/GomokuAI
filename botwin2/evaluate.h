#pragma once

#ifndef EVALUATE
#define EVALUATE




#include<vector>
#include<string>
#include<unordered_map>
using namespace std;







class strTree {
public:
	char c;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(const char* str, int v[7]);



/*初始化字典树*/
	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);
	
	static int readTree(strTree* root, char* strs[], int count, int v[7]);
	static void initRoots();
	static int getScoreG(int vv[2][7]);
	static int getScoreG(int *v,int*_v);

	~strTree();
};

/*全局敌我字典树*/
extern strTree* tree1;
extern strTree* tree2;






#endif // !EVALUATE