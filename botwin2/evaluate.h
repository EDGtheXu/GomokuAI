#pragma once

#ifndef EVALUATE
#define EVALUATE




#include<vector>
#include<string>
using namespace std;







class strTree {
public:
	char c;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;

	strTree(int v, char ch);
	int get(char* str, int v[7]);



/*��ʼ���ֵ���*/
	static void setTree(strTree* root, const vector<string>& strs, int value);
	static strTree* build(strTree* root);
	static strTree* build_oppo(strTree* root);
	
	static int readTree(strTree* root, char* strs[], int count, int v[7]);
	static void initRoots();
	static int getScoreG(int* v, int* _v);

	~strTree();
};

/*ȫ�ֵ����ֵ���*/
extern strTree* tree1;
extern strTree* tree2;




#endif // !EVALUATE