#pragma once
#ifndef CONFIG
#define CONFIG



#include <cstring>
#include <iostream>
#include <time.h>
#include <vector>


//#define FULLSEARCH


#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY
//#define DEBUG_ABS
//#define DEBUG_POSS





#define DEBUG_BOTZONE
#define TIME_CONTROL


#define SWAP3				//三手交换
#define FORBID_BLACK_33		//33禁手
#define FORBID_BLACK_44		//44禁手
#define FORBID_BLACK_LONG	//长连禁手
#define STEP5_OUT_N 2		//五手N打
#define STEP5_OUT_COUNT 5

#define STD_OUT_FORM		//比赛输出格式
#define STD_OUT_X(x) ((char)(x+'A'))
#define STD_OUT_Y(y) (15-y)

//#define TIMER_CLOCK

using namespace std;

typedef pair<int, int> Pos;
typedef uint64_t U64;
#define SHAPE_TYPES 9


//总体设置
extern int START_DEPTH;
extern int MAX_DEPTH;
extern int keepLen;
extern int range;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;
extern int LC_DELTA;//坏点与最大估值的差值
extern int LC_LOW;//坏点最低值
extern int LC_KEEP;//LC保留节点数
extern int TT_KEEP;//置换表保留节点数
extern int keepLenMin;//最小保留分支数
extern int posScoreMulti;
extern float defendMulti;
extern float curentMulti;
extern int turnValeDelta;


//开局设置
extern int step_INIT;
extern int MAX_DEPTH_INIT;
extern int keepLen_INIT;
extern int range_INIT;

//僵局设置
extern int step_FINA;
extern int MAX_DEPTH_FINA;
extern int keepLen_FINA;
extern int range_FINA;

extern int skeepLen;
extern int TIMEBEGIN;
extern const int COL;
extern const int ROW;
extern const int MAX_INT;
extern const int MIN_INT;
extern const int MAX_SEARCH_TIME_MS;

extern const int VALUE_GDEFAULT[SHAPE_TYPES];

extern int time1;
extern int tos4count;
extern int shape4count;
extern int toscount;
extern int timemove;
extern int movecount;
extern int timepos;
extern int timereadtree;
extern int timetos;
extern int timetos4;
extern int timetemp;
extern int timeshape;
extern int timeshape4;
extern int lcCount;


extern int reachMaxDepth;
extern int searchNode;
extern int testCount;




//公用棋型
extern const vector<string> gshaps_win;

extern const vector<string> gshaps_huo4;
extern const vector<string> gshaps_chong4;

extern const vector<string> gshaps_huo3;
extern const vector<string> gshaps_qian3;
extern const vector<string> gshaps_chong3;
extern const vector<string> gshaps_huo2;
extern const vector<string> gshaps_ming2;


//公用棋型
extern const vector<string> gshaps_win_oppo;

extern const vector<string> gshaps_huo4_oppo;
extern const vector<string> gshaps_chong4_oppo;

extern const vector<string> gshaps_huo3_oppo;
extern const vector<string> gshaps_qian3_oppo;
extern const vector<string> gshaps_chong3_oppo;
extern const vector<string> gshaps_huo2_oppo;
extern const vector<string> gshaps_ming2_oppo;


enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

playerEnum operator-(playerEnum p);

enum shapeEnum {
	WIN = 0, H4, C4, H3, Q3, C3, H2, M2, BAN
};



class hashTable;
class TransitionTable;

extern hashTable shapeHashTable;
extern TransitionTable TT;

extern U64 zobristArr[2][15][15];

void initZobrist();

#endif // !CONFIG