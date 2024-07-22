#include <random>
#include"config.h"

static std::mt19937_64 random(time(NULL));


//总体设置
int START_DEPTH = 2;
int MAX_DEPTH = 5;
int keepLen = 10;
int range = 2;
int MAX_VCT_DEPTH = 7;//VCT可扩展层数
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

const int VALUE_GDEFAULT[SHAPE_TYPES]{ 200     ,	  100     ,      10      ,      10   ,       5     ,     3       ,     3    ,  1 };

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

int reachMaxDepth=0;
int searchNode = 0;
int testCount = 0;




//公用棋型
const vector<string> gshaps_win = { "11111" };
const vector<string> gshaps_huo4 = { "011110"};
const vector<string> gshaps_chong4 = {"10111","11011","11101","11110","01111" };
const vector<string> gshaps_huo3 = { "011100","001110"};
const vector<string> gshaps_qian3 = { "011010","010110" };
const vector<string> gshaps_chong3 = { "11100","11010","11001","10110","10101","10011",   "00111","01011","01101","01110" };
const vector<string> gshaps_huo2 = { "001100","010100","001010","010010" };
const vector<string> gshaps_ming2 = { "11000","10100","10010",  "00011","00101","01001" ,"01010","01100" ,"00110"};

//公用棋型
const vector<string> gshaps_win_oppo = { "/////" };
const vector<string> gshaps_huo4_oppo = { "0////0" };
const vector<string> gshaps_chong4_oppo = { "/0///","//0//","///0/","////0","0////" };
const vector<string> gshaps_huo3_oppo = { "0///00","00///0"};
const vector<string> gshaps_qian3_oppo = { "0//0/0","0/0//0" };
const vector<string> gshaps_chong3_oppo = { "///00","//0/0","//00/","/0//0","/0/0/","/00//",   "00///","0/0//","0//0/",  "0///0" };
const vector<string> gshaps_huo2_oppo = { "00//00","00/0/0","0/0/00","0/00/0" };
const vector<string> gshaps_ming2_oppo = { "//000","/0/00","/00/0",  "000//","00/0/","0/00/","0/0/0","0//00" ,"00//0" };


playerEnum operator-(playerEnum p) {
	return p == ME ? OPPO : (p == OPPO ? ME : EMPTY);
};


U64 zobristInitRandom = random();