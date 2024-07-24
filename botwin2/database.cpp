#include "database.h"
#include "board.h"

int rot[4][2]{
	1,0,
	0,1,
	-1,0,
	0,-1
};


Pos rotate(Pos ori,int dir) {

	int x = ori.first;
	int y = ori.second;

	int xo = 7;
	int yo = 7;

	int xe = (x - xo) * rot[dir][0] - (y - yo) * rot[dir][1] + xo;
	int ye = (y - yo) * rot[dir][0] + (x - xo) * rot[dir][1] + yo;

	return Pos(xe, ye);
}

Pos rotHor(Pos ori) {
	ori.first = 14 - ori.first;
	return ori;
}

Pos rotVer(Pos ori) {
	ori.second = 14 - ori.second;
	return ori;
}

void database::genLine(string str) {



	int index = 0;
	int eval = 0;
	while (str[index])
	{
		if (str[index] >= 'a' && str[index] <= 'z') eval++;
		index++;
	}
	index = 0;
	int yr = 15 - atoi(str.c_str() + index + 1);
	if (yr <= 5) index += 3;
	else index += 2;
	int initIndex = index;
	int winPiece = (eval % 2==0);//0 黑    1白


/*
	mb->move(7, 7);
	
	Move* movesR = TT.find(mb->zobristKey);
	if (!movesR)//未命中
	{
		movesR = new Move();
		movesR->valueType = ValueType::value_type_db;
		movesR->value = MAX_INT;
		movesR->dbWiner = (winPiece == 0 ? ME : OPPO);
		TT.AddItem(mb->zobristKey, movesR);
	}
	int& cR = movesR->moveCount;
	movesR->moves[cR] = p;
	movesR->dbEval = eval;
	cR++;
	*/

	for (int i = 0;i < 8;i++) {
		dataNode* cur = root;
		dataNode* last = cur;
		index = 0;

		while (str[index]) {
			int x = str[index] - 'a';
			int y = 15 - atoi(str.c_str() + index + 1);
			Pos p = Pos(x, y);
			if (i < 4) {
				p = rotate(p, i);
			}
			else if (i == 4) {
				p = rotHor(p);
			}
			else if(i==5){
				p = rotVer(p);
			}
			else if (i == 6) {
				p = rotate(rotHor(p), 1);
			}
			else {
				p = rotate(rotHor(p), 3);
			}

			
			Move* moves = TT.find(mb->zobristKey);
			if (!moves)//未命中
			{
				moves = new Move();
				moves->valueType = ValueType::value_type_db;
				moves->value = MAX_INT;
				moves->dbWiner = (winPiece == 0 ? ME : OPPO);
				TT.AddItem(mb->zobristKey, moves);
			}
			int& c = moves->moveCount;
			bool exist = false;

			for (int i = 0;i < c;i++) {
				if (moves->moves[i] == p) {
					exist = true;
				}
					
			}
			if (!exist) {
				moves->moves[c] = p;
				c++;
			}
			moves->dbEval = min( eval,moves->dbEval);
			mb->move(p);
			dataNode* next = cur->findNext(p);
			if (!next) {
				dataNode* nn = new dataNode(p);
				cur->next.insert(make_pair(p, nn));
				next = nn;
			}
			if(last->eval < eval){
				last->ans = p;
				last->eval = eval;
			}
			last = next;
			//cout << x <<' ' << y << endl;

			cur = next;

			if (y <= 5) index += 3;
			else index += 2;
		}

		for (int j = mb->moveCount;j > 0;j--)
			mb->undo();

	}
}

Pos database::readLine(Pos* ps, int count)
{
	dataNode* cur = root;
	if (cur->p != ps[0]) return Pos(-1, -1);
	if (count == 1) return cur->ans;
	for (int i = 1; i < count; i++) {

		cur = cur->findNext(ps[i]);
		if (!cur) return Pos(-1, -1);

	}
	if (cur->ans.first != -1)
		return cur->ans;
	else return Pos(-1, -1);
}


vector<string> datas{
//直开
	//花月
	"h8h9i9g7j8i10j10j9k7l6i7g8j11k8l7h11g12f7e6m7k9l10g9j6i11h12h10g11f8j12e7",



//斜开
		//峡月
	"h8g7g6i6f7e8j8h7i7g8f9g9j5k7k6l7j4g10g11h5f8f10g5h6f6f5h4i3j6j7l4k5i4k4g4f4g2h3g3",


};

void database::init()
{
	int len = datas.size();
	for (int i = 0;i < len;i++) {
		genLine(datas[i].c_str());
	}
}

