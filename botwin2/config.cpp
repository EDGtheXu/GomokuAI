#include"config.h"
#include <random>
static std::mt19937_64 random(time(NULL));


//总体设置
int MAX_DEPTH = 4;
int keepLen = 30;
int range = 2;
int MAX_VCT_DEPTH = 6;//VCT可扩展层数
int MAX_VCF_DEPTH = 25;//VCF可扩展层数

//开局设置
int step_INIT = -1;
int MAX_DEPTH_INIT = 2;
int keepLen_INIT = 13;
int range_INIT = 2;

//僵局设置
int step_FINA = 40;
int MAX_DEPTH_FINA = 5;
int keepLen_FINA = 20;
int range_FINA = 2;

int skeepLen = 3;
int TIMEBEGIN = 0;
const int COL = 15;
const int ROW = 15;
const int MAX_INT = 0x3f3f3f3f;
const int MIN_INT = -MAX_INT;
const int MAX_SEARCH_TIME_MS = 0.95 * CLOCKS_PER_SEC;
const int VALUE_DEFAULT[7]{ MAX_INT / 1000          ,	  MAX_INT / 2000     ,      2000      ,      600   ,       600     ,     150       ,     150 };
const int VALUE_DEFAULT_OPPO[7]{ MIN_INT / 10000         ,    -2000              ,     -1000       ,     -400   ,      -400      ,    -100       ,    -100 };
const int VALUE_MUST_WIN = -100000;

int time1;
int tos4count = 0;
int toscount = 0;
int timescore4 = 0;
int timescore = 0;
int timepos = 0;
int timepos1 = 0;
int timetos = 0;
int timetos4 = 0;
int timetemp = 0;
int timeshape = 0;
int timeshape4 = 0;

int reachMaxDepth=0;
int searchNode = 0;
int testCount = 0;

//进攻
const vector<string> shaps_win = { "11111" };
const vector<string> shaps_huo4 = { "011110","10111","11011","11101","11110","01111" };
//防守
//const vector<string> shaps_huo4_oppo = { "011110","11111" };
//const vector<string> shaps_chong4_oppo = { "11110","01111","11101","11011","10111","11101","11101","10111"};
//公用
const vector<string> shaps_huo3 = { "011100","001110","011010","010110" };
const vector<string> shaps_chong3 = { "11100","11010","11001","10110","10101","10011",   "00111","01011","10011","01101","10101","11001",   "01110" };
const vector<string> shaps_huo2 = { "01100","00110","01010","010010" };
const vector<string> shaps_ming2 = { "11000","10100","10010","10001",  "00011","00101","01001","10001" };
const vector<string> shaps_huo1 = { "00100" };



//进攻
//const vector<string> _shaps_win = { "/////" };
//const vector<string> _shaps_huo4 = { "0////0","/0///","//0//","///0/","////0" };
//防守
const vector<string> _shaps_huo4_oppo = { "/0///0/","//0//0//","///0/0///", "0////0","/////" };
const vector<string> _shaps_chong4_oppo = { "////0","0////","///0/","//0//","/0///","///0/" ,"///0/","/0///" };
//公用
const vector<string> _shaps_huo3 = { "0///00","00///0","0//0/0","0/0//0" };
const vector<string> _shaps_chong3 = { "///00","//0/0","//00/","/0//0","/0/0/","/00//",   "00///","0/0//","/00//","0//0/","/0/0/","//00/",   "0///0" };
const vector<string> _shaps_huo2 = { "00//0","0//00","0/0/0","0/00/0" };
const vector<string> _shaps_ming2 = { "//000","/0/00","/00/0","/000/",  "000//","00/0/","0/00/","/000/" };
const vector<string> _shaps_huo1 = { "00/00" };

playerEnum operator-(playerEnum p) {
	return p == ME ? OPPO : (p == OPPO ? ME : EMPTY);
};


U64 zobristInitRandom = random();