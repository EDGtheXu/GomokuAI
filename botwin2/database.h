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

	bool changed;//�Ƿ��Ѿ��任
	int offsetx;//x��ƫ��
	int offsety;//y��ƫ��
	int rotate;//˳ʱ����ת�Ƕ�
	bool rotHor;//ˮƽ��ת
	bool rotVer;//��ֱ��ת
public:
	database() {
		
	}

};

