#pragma once

enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPOO = -1
};
class board
{
public:
	int chess[15][15];
	pair<int, int> curpos;
private:

public:
	board();
	board(const board& b);
	board(int chess[][15]);
	board* setChess(playerEnum p, pair<int, int> posi);

	bool isWin(playerEnum p, pair<int, int>& pos);
	bool operator==(const board& b);
	board& operator=(const board& b);
	friend ostream& operator<<(ostream& os, const board& b);
	board* reverse();

	pair<int, int> lose();
	int getScoreLose(pair<int, int>& pos, int v0[7], int _v0[7]);
	int getAllPossiblePos(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos0(playerEnum p, int, pair<int, int>* res, int*);
	int getAllPossiblePos1(playerEnum p, int depth, pair<int, int>* res);
	int abSearch(playerEnum p, int depth, int alpha, int beta);

	pair<int, int> policy(playerEnum p);
	int getScoreP(pair<int, int>& pos, int v0[7], int _v0[7]);
	int getScore();

	void getShapes(int* v, int* _v);
	void getShapes4(pair<int, int>& pos, int* v, int* _v);
	int toString4(char* strs[], pair<int, int>& pos);
	int toString(char* strs[]);
};


class strTree {
public:
	char c;
	int valueIndex;
	strTree* l;
	strTree* m;
	strTree* r;
	strTree(int v, char ch) {
		valueIndex = v;
		c = ch;
		l = nullptr;
		m = nullptr;
		r = nullptr;

	}
	static void setTree(strTree* root, const vector<string>& strs, int value) {
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
	static strTree* build(strTree* root);
	static strTree* build_OPPOO(strTree* root);
	int get(char* str, int v[7]) {
		strTree* root = this;
		int count = 0;
		int back = 0;
		int len = strlen(str);
		int va = -1;
		int huosan_single = 0; //避免重复活三
		int chong4_fix = 0;

		for (int i = 0; i < len && back < len - 4; i++) {
			if (str[i] == '/') {
				if (root->l) root = root->l;
				else {
					root = this;
					if (va != -1) back += 1;//已匹配到
					else back++;
					i = back - 1;
					va = -1;
				}
			}
			else if (str[i] == '0') {
				if (root->m) root = root->m;
				else {
					root = this;
					if (va != -1) back += 1;
					else back++;
					i = back - 1;
					va = -1;
				}
			}
			else if (str[i] == '1') {
				if (root->r)  root = root->r;
				else {
					root = this;
					if (va != -1) back += 1;
					else back++;
					i = back - 1;
					va = -1;
				}
			}
			if (root->valueIndex != -1) {
				if (root->valueIndex == 2) {
					huosan_single++;
					if (huosan_single > 1) continue;
				}
				else if (root->valueIndex == 1) {
					chong4_fix++;
					if (chong4_fix > 1) continue;
				}

				va = root->valueIndex;
				v[va] += 1;
				count++;

				//root = this;
				//back += 2;
				//i = back - 1;
			}
		}
		if (huosan_single > 0 && chong4_fix > 0) {
			v[2] -= 1;
		}


		return count;
	}
	~strTree()
	{
		if (l) delete l;
		if (m) delete m;
		if (r) delete r;
	}
};
//三叉字典树
strTree* tree1 = nullptr;
strTree* tree2 = nullptr;
int readTree(strTree* root, int* strs[], int count, int v[7]);
void initRoots();
void btzPolicy();
int getScoreG(int* v, int* _v);

