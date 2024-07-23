
#include "evaluate.h"


strTree* tree1 = nullptr;
strTree* tree2 = nullptr;


/*获取棋型*/

int strTree::readTree(strTree* root, char* strs[], int count, int v[7])
{
	int c = 0;

	for (int i = 0; i < count; i++) {
		string t = strs[i];
		c += root->get(strs[i], v);
	}
	return c;
}
/*获取单行棋型*/
int strTree::get(const char* str, int v[7]) {
	strTree* root = this;
	int count = 0;
	int back = 0;

	int va = -1;

	int tempv[SHAPE_TYPES]{ 0 };
	int debug = 0;


	//去掉前面的'0'
	int st = 0;
	while (str[st] == '0') st++;
	if (st >= skeepLen) {
		str = str + st - skeepLen;
	}

	//去掉后面的'0'
	int en = strlen(str) - 1;
	int c = 0;
	while (str[en--] == '0') c++;
	en += (2 + (c > skeepLen ? skeepLen : c));

	if (en < 5)//短字符串舍弃
		return 0;
	//获取棋型
	for (int i = 0; str[i] && back <= en - 4; i++) {
		if (str[i] == '/') {
			if (root->l) root = root->l;
			else {
				root = this;
				if (va != -1) {
					back += 1;//已匹配到
					//if(va==C4||va==H3)
				}
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else if (str[i] == '0') {
			if (root->m) root = root->m;
			else {
				root = this;
				if (va != -1) {
					back += 1;
				}
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else if (str[i] == '1') {
			if (root->r)  root = root->r;
			else {
				root = this;
				if (va != -1) {
					back += 1;
				}
				else back++;
				i = back - 1;
				va = -1;
			}
		}
		else {
			root = this;
			if (va != -1) {
				back += 1;
			}
			else back++;
			i = back - 1;
			va = -1;
		}

		if (root->valueIndex != -1) {
			va = root->valueIndex;
			tempv[va] = 1;
			count++;
		}
	}

	v[WIN] += tempv[WIN];
	v[H4] += tempv[H4];
	v[C4] += tempv[C4];
	v[H3] += tempv[C4] ? 0 : tempv[H3];
	v[Q3] += tempv[C4] ? 0 : tempv[Q3];
	v[C3] += tempv[C4] || tempv[H3] || tempv[Q3] ? 0 : tempv[C3];
	v[H2] += tempv[Q3] ? 0 : tempv[H2];
	v[M2] += (tempv[C4] | tempv[C3] | tempv[Q3] | tempv[H3] | tempv[H2]) ? 0 : tempv[M2];

	return count;
}


/*由棋型估值*/
int strTree::getScoreG(int vv[2][SHAPE_TYPES]) {

	const int* values = VALUE_GDEFAULT;
	//我方权值
	int score =
		vv[0][0] * values[0] +
		vv[0][1] * values[1] +
		vv[0][2] * values[2] +
		vv[0][3] * values[3] +
		vv[0][4] * values[4] +
		vv[0][5] * values[5] +
		vv[0][6] * values[6] +
		vv[0][7] * values[7]
		;
	//对方权值
	int _score =
		vv[1][0] * values[0] +
		vv[1][1] * values[1] +
		vv[1][2] * values[2] +
		vv[1][3] * values[3] +
		vv[1][4] * values[4] +
		vv[1][5] * values[5] +
		vv[1][6] * values[6] +
		vv[1][7] * values[7]
		;

	return score  - _score;
}

int strTree::getScoreG(int* v, int* _v) {

	const int* values = VALUE_GDEFAULT;
	//我方权值
	int score =
		v[0] * values[0] +
		v[1] * values[1] +
		v[2] * values[2] +
		v[3] * values[3] +
		v[4] * values[4] +
		v[5] * values[5] +
		v[6] * values[6] +
		v[7] * values[7]
		;
	//对方权值
	int _score =
		_v[0] * values[0] +
		_v[1] * values[1] +
		_v[2] * values[2] +
		_v[3] * values[3] +
		_v[4] * values[4] +
		_v[5] * values[5] +
		_v[6] * values[6] +
		_v[7] * values[7]
		;

	return score  - _score ;
}



int strTree::getScoreSide(int* v) {
	static int changeMap[7][7]{
		{},
		{},
		{},
		{},
		{},
		{},
		{}
	};

//	H2 -> H3:	40		H2 -> M2:	40
//	H2 -> Q3:	35
//	H3 -> H4:	500		H3 -> C3:	500
//	Q3 -> H4:	500		Q3 -> M2:	500
//						Q3 -> C3 :	500
//	 
//	M2 -> C3:	10		M2 -> NULL:	10
//	C3 -> C4:	40		M3 -> NULL:	20

	const int* values = VALUE_GDEFAULT;
	//我方权值
	int score =
		v[0] * values[0] +
		v[1] * values[1] +
		v[2] * values[2] +
		v[3] * values[3] +
		v[4] * values[4] +
		v[5] * values[5] +
		v[6] * values[6] +
		v[7] * values[7]
		;



	return score ;
}

























/*字典树初始化*/
void strTree::setTree(strTree* root, const vector<string>& strs, int value) {
	for (string str : strs) {
		strTree* r = root;
		for (char c : str) {
			if (c == '/') {
				if (!root->l) root->l = new strTree(-1, c);
				root = root->l;
			}
			else if (c == '0') {
				if (!root->m) root->m = new strTree(-1, c);
				root = root->m;
			}
			else if (c == '1') {
				if (!root->r) root->r = new strTree(-1, c);
				root = root->r;
			}
		}
		root->valueIndex = value;
		root = r;
	}
}
strTree* strTree::build(strTree* root) {
	setTree(root, gshaps_win, 0);
	setTree(root, gshaps_huo4, 1);
	setTree(root, gshaps_chong4, 2);
	setTree(root, gshaps_huo3, 3);
	setTree(root, gshaps_qian3, 4);
	setTree(root, gshaps_chong3, 5);
	setTree(root, gshaps_huo2, 6);
	setTree(root, gshaps_ming2, 7);

	return root;
}

strTree* strTree::build_oppo(strTree* root) {
	setTree(root, gshaps_win_oppo, 0);
	setTree(root, gshaps_huo4_oppo, 1);
	setTree(root, gshaps_chong4_oppo, 2);
	setTree(root, gshaps_huo3_oppo, 3);
	setTree(root, gshaps_qian3_oppo, 4);
	setTree(root, gshaps_chong3_oppo, 5);
	setTree(root, gshaps_huo2_oppo, 6);
	setTree(root, gshaps_ming2_oppo, 7);

	return root;
}

void strTree::initRoots() {
	tree1 = new strTree(-1, 0);
	tree2 = new strTree(-1, 0);
	tree1 = strTree::build(tree1);
	tree2 = strTree::build_oppo(tree2);
}

strTree::strTree(int v, char ch) {
	valueIndex = v;
	c = ch;
	l = nullptr;
	m = nullptr;
	r = nullptr;

}
strTree::~strTree()
{
	if (l) delete l;
	if (m) delete m;
	if (r) delete r;
}




