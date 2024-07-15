
#include "evaluate.h"
#include "config.h"

strTree* tree1 = nullptr;
strTree* tree2 = nullptr;


/*��ȡ����*/

int strTree::readTree(strTree* root, char* strs[], int count, int v[7])
{
	int c = 0;

	for (int i = 0; i < count; i++) {
		string t = strs[i];
		c += root->get(strs[i], v);
	}
	return c;
}
/*��ȡ��������*/
int strTree::get(const char* str, int v[7]) {
	strTree* root = this;
	int count = 0;
	int back = 0;
	int len = strlen(str);
	int va = -1;
	int huosan_single = 0; //�����ظ�����
	int chong4_fix = 0;

	for (int i = 0; i < len && back < len - 4; i++) {
		if (str[i] == '/') {
			if (root->l) root = root->l;
			else {
				root = this;
				if (va != -1) back += 1;//��ƥ�䵽
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


/*�����͹�ֵ*/
int strTree::getScoreG(int vv[2][7]) {
#ifdef DEBUG_main
	int t = clock();
#endif
	const int* values = VALUE_GDEFAULT;
	//�ҷ�Ȩֵ
	int score =
		vv[0][0] * values[0] +
		vv[0][1] * values[1] +
		vv[0][2] * values[2] +
		vv[0][3] * values[3] +
		vv[0][4] * values[4] +
		vv[0][5] * values[5] +
		vv[0][6] * values[6]
		;
	//�Է�Ȩֵ
	int _score =
		vv[1][0] * values[0] +
		vv[1][1] * values[1] +
		vv[1][2] * values[2] +
		vv[1][3] * values[3] +
		vv[1][4] * values[4] +
		vv[1][5] * values[5] +
		vv[1][6] * values[6]
		;
#ifdef DEBUG_main
	timescore += clock() - t;
#endif
	return score - _score;
}

int strTree::getScoreG(int* v,int* _v) {
#ifdef DEBUG_main
	int t = clock();
#endif
	const int* values = VALUE_GDEFAULT;
	//�ҷ�Ȩֵ
	int score =
		v[0] * values[0] +
		v[1] * values[1] +
		v[2] * values[2] +
		v[3] * values[3] +
		v[4] * values[4] +
		v[5] * values[5] +
		v[6] * values[6]
		;
	//�Է�Ȩֵ
	int _score =
		_v[0] * values[0] +
		_v[1] * values[1] +
		_v[2] * values[2] +
		_v[3] * values[3] +
		_v[4] * values[4] +
		_v[5] * values[5] +
		_v[6] * values[6]
		;
#ifdef DEBUG_main
	timescore += clock() - t;
#endif
	return score - _score;
}


























/*�ֵ�����ʼ��*/
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




