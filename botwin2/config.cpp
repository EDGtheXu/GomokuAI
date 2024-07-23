#include <random>
#include"config.h"

static std::mt19937_64 random(time(NULL));

const int VALUE_GDEFAULT[SHAPE_TYPES]{	//	权重
			1000		,					//	WIN
			250		,	150	,			//	H4		C4
			100		,	60	,	70	,   //	H3		Q3		C3
			20		,	10				//	H2		M2
};

//	NULL -> H2:	10
//	MULL -> M2:	5
//	
// 
//	H2 -> H3:	40		H2 -> M2:	40
//	H2 -> Q3:	35
//	H3 -> H4:	500		H3 -> C3:	500
//	Q3 -> H4:	500		Q3 -> M2:	500
//						Q3 -> C3 :	500
//	 
//	M2 -> C3:	10		M2 -> NULL:	10
//	C3 -> C4:	40		M3 -> NULL:	20
//


//总体设置
int START_DEPTH =1;
int MAX_DEPTH = 10;

int range = 2;

int LC_DELTA = VALUE_GDEFAULT[H3]*2;//坏点与最大估值的差值
int LC_LOW = -10000;//坏点必输值

int LC_KEEP = 30;//LC保留分支数
int TT_KEEP =30;//置换表保留分支数
int keepLen = 30;//最大保留分支数(按层递减)
int keepLenMin = 25;//最小保留分支数


int MAX_VCT_DEPTH = 7;//VCT可扩展层数
int MAX_VCF_DEPTH =10;//VCF可扩展层数

int posScoreMulti = 1;//位置得分系数
float defendMulti = 1;//防御系数;
float curentMulti = 1;
int turnValeDelta = 0;//VALUE_GDEFAULT[H3] * defendMulti;







//开局设置
int step_INIT = -1;
int MAX_DEPTH_INIT = 2;
int keepLen_INIT = 13;
int range_INIT = 2;

//僵局设置
int step_FINA = 100;
int MAX_DEPTH_FINA = 5;
int keepLen_FINA = 20;
int range_FINA = 2;

int skeepLen = 3;
int TIMEBEGIN = 0;
const int COL = 15;
const int ROW = 15;
const int MAX_INT = 0x3f3f3f3f;
const int MIN_INT = -MAX_INT;
const int MAX_SEARCH_TIME_MS = 3 * CLOCKS_PER_SEC;



int time1;
int tos4count = 0;
int toscount = 0;
int shape4count = 0;
int timemove = 0;
int movecount = 0;
int timepos = 0;
int timereadtree = 0;
int timetos = 0;
int timetos4 = 0;
int timetemp = 0;
int timeshape = 0;
int timeshape4 = 0;
int lcCount = 0;

int reachMaxDepth = 0;
int searchNode = 0;
int testCount = 0;




//公用棋型
const vector<string> gshaps_win = { "11111" };
const vector<string> gshaps_huo4 = { "011110" };
const vector<string> gshaps_chong4 = { "10111","11011","11101","11110","01111" };
const vector<string> gshaps_huo3 = { "011100","001110" };
const vector<string> gshaps_qian3 = { "011010","010110" };
const vector<string> gshaps_chong3 = { "11100","11010","11001","10110","10101","10011",   "00111","01011","01101","01110" };
const vector<string> gshaps_huo2 = { "001100","010100","001010","010010" };
const vector<string> gshaps_ming2 = { "11000","10100","10010",  "00011","00101","01001" ,"01010","01100" ,"00110" };

//公用棋型
const vector<string> gshaps_win_oppo = { "/////" };
const vector<string> gshaps_huo4_oppo = { "0////0" };
const vector<string> gshaps_chong4_oppo = { "/0///","//0//","///0/","////0","0////" };
const vector<string> gshaps_huo3_oppo = { "0///00","00///0" };
const vector<string> gshaps_qian3_oppo = { "0//0/0","0/0//0" };
const vector<string> gshaps_chong3_oppo = { "///00","//0/0","//00/","/0//0","/0/0/","/00//",   "00///","0/0//","0//0/",  "0///0" };
const vector<string> gshaps_huo2_oppo = { "00//00","00/0/0","0/0/00","0/00/0" };
const vector<string> gshaps_ming2_oppo = { "//000","/0/00","/00/0",  "000//","00/0/","0/00/","0/0/0","0//00" ,"00//0" };


playerEnum operator-(playerEnum p) {
	return p == ME ? OPPO : (p == OPPO ? ME : EMPTY);
};


U64 zobristInitRandom = random();