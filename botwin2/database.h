#pragma once
#ifndef DATABASE
#define DATABASE




#include<map>
#include"config.h"


class dataNode
{
public:
	dataNode(Pos pos):p(pos),ans(Pos(-1,-1)) {};
	~dataNode() {};

	Pos p;
	Pos ans;
	int eval = 0;

	map<Pos,dataNode*> next;

	dataNode* findNext(Pos& p) {
		auto it =  next.find(p);
		if (it != next.end())return it->second;
		return nullptr;
	}
};
class board;

class database
{

private:
	dataNode* root;


public:
	database(board*b) {
		root = new dataNode(Pos(7, 7));
		mb = b;
	};
	board* mb;
	void genLine(string str);

	Pos readLine(Pos* ps,int count);
	void init();




};








#endif // !DATABASE