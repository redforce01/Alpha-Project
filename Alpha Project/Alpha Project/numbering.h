#pragma once
#include "singletonBase.h"
#include <vector>

enum NUMBER_TYPE
{
	NWS, NWM, NWH, NWB,
	NRM, NGS, NGH, NGB,
	SC_S, SC_M,	SC_B,
	NONE
};

class numbering : public singletonBase<numbering>
{
public:
	typedef vector<int> arrNumbers;
	typedef vector<int>::iterator iterNumbers;

	typedef vector<image*> arrNumber;
	typedef vector<image*>::iterator iterNumber;

public:
	int _nNumber;
	arrNumbers _vNumbers;
	arrNumber _vNumber;
	NUMBER_TYPE _typeNumber;
	bool _flag;

public:
	numbering();
	~numbering();

	HRESULT init();
	void release();

	vector<image*> getNumber(int number, NUMBER_TYPE type);

	void divideNumToVec();
	void changeNumToImg();
};

