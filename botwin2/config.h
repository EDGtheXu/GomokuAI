#pragma once
#ifndef CONFIG
#define CONFIG




#include <iostream>
#include <time.h>
#include <vector>

#define DEBUG
#define DEBUG_main
#define DEBUG_POLICY
//#define DEBUG_ABS
//#define DEBUG_POSS
//#define DEBUG_GS

//#define TIME_CONTROL



using namespace std;
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

extern int time1;
extern int tos4count ;
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

//进攻
extern const vector<string> shaps_win ;
extern const vector<string> shaps_huo4 ;
//防守
//const vector<string> shaps_huo4_oppo ;
//const vector<string> shaps_chong4_oppo ;
//公用
extern const vector<string> shaps_huo3 ;
extern const vector<string> shaps_chong3 ;
extern const vector<string> shaps_huo2 ;
extern const vector<string> shaps_ming2 ;
extern const vector<string> shaps_huo1 ;



//进攻
//const vector<string> _shaps_win ;
//const vector<string> _shaps_huo4 ;
//防守
extern const vector<string> _shaps_huo4_oppo ;
extern const vector<string> _shaps_chong4_oppo ;
//公用
extern const vector<string> _shaps_huo3 ;
extern const vector<string> _shaps_chong3 ;
extern const vector<string> _shaps_huo2 ;
extern const vector<string> _shaps_ming2 ;
extern const vector<string> _shaps_huo1 ;


enum playerEnum
{
	EMPTY = 0,
	ME = 1,
	OPPO = -1
};


#endif // !CONFIG