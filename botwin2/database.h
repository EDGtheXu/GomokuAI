#pragma once

class dataNode
{
public:
	dataNode();
	~dataNode();

private:

};


class database
{

private:
	dataNode* root;

	bool changed;//是否已经变换
	int offsetx;//x轴偏移
	int offsety;//y轴偏移
	int rotate;//顺时针旋转角度
	bool rotHor;//水平翻转
	bool rotVer;//竖直翻转
public:
	database() {
		
	}

};

