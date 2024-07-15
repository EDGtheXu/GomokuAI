#pragma once
#ifndef CONFIG
#define CONFIG



#include <cstring>
#include <iostream>
#include <time.h>
#include <vector>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY
//#define DEBUG_ABS
//#define DEBUG_POSS



//#define DEBUG_BOTZONE
//#define TIME_CONTROL
using namespace std;

typedef pair<int, int> Pos;
typedef uint64_t U64;



//总体设置
extern int MAX_DEPTH ;
extern int keepLen ;
extern int range ;
extern int MAX_VCT_DEPTH;
extern int MAX_VCF_DEPTH;

//开局设置
extern int step_INIT ;
extern int MAX_DEPTH_INIT ;
extern int keepLen_INIT ;
extern int range_INIT ;

//僵局设置
extern int step_FINA ;
extern int MAX_DEPTH_FINA ;
extern int keepLen_FINA ;
extern int range_FINA ;

extern int skeepLen ;
extern int TIMEBEGIN ;
extern const int COL ;
extern const int ROW ;
extern const int MAX_INT ;
extern const int MIN_INT ;
extern const int MAX_SEARCH_TIME_MS ;
extern const int VALUE_DEFAULT[7];
extern const int VALUE_DEFAULT_OPPO[7];
extern const int VALUE_MUST_WIN ;

extern const int VALUE_GDEFAULT[7];

extern int time1;
extern int tos4count ;
extern int shape4count;
extern int toscount ;
extern int timescore4 ;
extern int timescore ;
extern int timepos ;
extern int timepos1 ;
extern int timetos ;
extern int timetos4 ;
extern int timetemp ;
extern int timeshape;
extern int timeshape4;


extern int reachMaxDepth;
extern int searchNode;
extern int testCount;




//公用棋型
extern const vector<string> gshaps_win;

extern const vector<string> gshaps_huo4;
extern const vector<string> gshaps_chong4 ;

extern const vector<string> gshaps_huo3;
extern const vector<string> gshaps_qian3;
extern const vector<string> gshaps_chong3;
extern const vector<string> gshaps_huo2;


//公用棋型
extern const vector<string> gshaps_win_oppo;

extern const vector<string> gshaps_huo4_oppo;
extern const vector<string> gshaps_chong4_oppo;

extern const vector<string> gshaps_huo3_oppo;
extern const vector<string> gshaps_qian3_oppo;
extern const vector<string> gshaps_chong3_oppo;
extern const vector<string> gshaps_huo2_oppo;



enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};

playerEnum operator-(playerEnum p);

enum shapeEnum {
	WIN = 0, H4, C4, H3, Q3, C3, H2, 
};


class hashTable;
class TransitionTable;

extern hashTable shapeHashTable;
extern TransitionTable TT;

#endif // !CONFIG