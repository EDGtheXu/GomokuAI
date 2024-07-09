
#include "evaluate.h"
#include "config.h"

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
int strTree::get(char* str, int v[7]) {
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


/*由棋型估值*/
int strTree::getScoreG(int* v, int* _v) {
#ifdef DEBUG_main
	int t = clock();
#endif
	//p=ME:计算我方权值，下一步对方
	const int* values = nullptr, * _values = nullptr;

	values = VALUE_DEFAULT;
	_values = VALUE_DEFAULT_OPPO;


	//我方权值
	int score =
		v[0] * values[0] +
		v[1] * values[1] +
		v[2] * values[2] +
		v[3] * values[3] +
		v[4] * values[4] +
		v[5] * values[5] +
		v[6] * values[6]
		;

	//对方权值
	int _score =
		_v[0] * _values[0] +
		_v[1] * _values[1] +
		_v[2] * _values[2] +
		_v[3] * _values[3] +
		_v[4] * _values[4] +
		_v[5] * _values[5] +
		_v[6] * _values[6]
		;


	//优先级  我方先手


	int rs = score + _score;
#ifdef DEBUG_main
	timescore += clock() - t;
#endif
	return rs;
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
	setTree(root, shaps_win, 0);
	setTree(root, shaps_huo4, 1);
	setTree(root, shaps_huo3, 2);
	setTree(root, shaps_chong3, 3);
	setTree(root, shaps_huo2, 4);
	setTree(root, shaps_ming2, 5);
	setTree(root, shaps_huo1, 6);
	return root;
}

strTree* strTree::build_oppo(strTree* root) {
	setTree(root, _shaps_huo4_oppo, 0);
	setTree(root, _shaps_chong4_oppo, 1);
	setTree(root, _shaps_huo3, 2);
	setTree(root, _shaps_chong3, 3);
	setTree(root, _shaps_huo2, 4);
	setTree(root, _shaps_ming2, 5);
	setTree(root, _shaps_huo1, 6);
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