#include "stdafx.h"
#include "numbering.h"


numbering::numbering()
{
}


numbering::~numbering()
{
}

HRESULT numbering::init()
{
	_nNumber = 0;
	_typeNumber = NONE;

	return S_OK;
}

void numbering::release()
{
}

void numbering::divideNumToVec()
{
	_vNumbers.clear();
	int inputCount = _nNumber;
	_flag = false;

	int hundredMillionShare = inputCount / 10000000;
	int hundredMillionRemain = inputCount % 10000000;
	int tenMillionShare = hundredMillionRemain / 1000000;
	int tenMillionRemain = hundredMillionRemain % 1000000;
	int millionShare = tenMillionRemain / 100000;
	int millionRemain = tenMillionRemain % 100000;
	int tenThousandShare = millionRemain / 10000;
	int tenThousandRemain = millionRemain % 10000;
	int thousandShare = tenThousandRemain / 1000;
	int thousandRemain = tenThousandRemain % 1000;
	int hundredShare = thousandRemain / 100;
	int hundredRemain = thousandRemain % 100;
	int tenShare = hundredRemain / 10;
	int tenRemain = hundredRemain % 10;
	int oneShare = tenRemain / 1;

	if (hundredMillionShare > 0)
	{
		_vNumbers.push_back(hundredMillionShare);
		_flag = true;
	}
	if (tenMillionShare > 0 || _flag)
	{
		_vNumbers.push_back(tenMillionShare);
		_flag = true;
	}
	if (millionShare > 0 || _flag)
	{
		_vNumbers.push_back(millionShare);
		_flag = true;
	}
	if (tenThousandShare > 0 || _flag)
	{
		_vNumbers.push_back(tenThousandShare);
		_flag = true;
	}
	if (thousandShare > 0 || _flag)
	{
		_vNumbers.push_back(thousandShare);
		_flag = true;
	}
	if (hundredShare > 0 || _flag)
	{
		_vNumbers.push_back(hundredShare);
		_flag = true;
	}
	if (tenShare > 0 || _flag)
	{
		_vNumbers.push_back(tenShare);
		_flag = true;
	}
	if (oneShare > 0 || _flag)
	{
		_vNumbers.push_back(oneShare);
		_flag = true;
	}

	if (!_flag) _vNumbers.push_back(0);
	
}

void numbering::changeNumToImg()
{
	_vNumber.clear();
	int numberSize = _vNumbers.size();
	for (int i = 0; i < numberSize; i++)
	{
		image* tempNum = new image;
		switch (_typeNumber)
		{
		case NWS:
			tempNum->init("image/numbers/Nws.bmp", 60, 11, 10, 1, true, RGB(0, 0, 0));
			break;
		case NWM:
			tempNum->init("image/numbers/Nwm.bmp", 70, 11, 10, 1, true, RGB(0, 0, 0));
			break;
		case NWH:
			tempNum->init("image/numbers/Nwh.bmp", 100, 13, 10, 1, true, RGB(0, 0, 0));
			break;
		case NWB:
			tempNum->init("image/numbers/Nwb.bmp", 170, 22, 10, 1, true, RGB(0, 0, 0));
			break;
		case NRM:
			tempNum->init("image/numbers/Nrm.bmp", 70, 11, 10, 1, true, RGB(0, 0, 0));
			break;
		case NGS:
			tempNum->init("image/numbers/Ngs.bmp", 60, 11, 10, 1, true, RGB(0, 0, 0));
			break;
		case NGH:
			tempNum->init("image/numbers/Ngh.bmp", 100, 13, 10, 1, true, RGB(0, 0, 0));
			break;
		case NGB:
			tempNum->init("image/numbers/Ngb.bmp", 170, 22, 10, 1, true, RGB(0, 0, 0));
			break;
		case SC_S:
			tempNum->init("image/numbers/Sc_s.bmp", 90, 13, 10, 1, true, RGB(0, 0, 0));
			break;
		case SC_M:
			tempNum->init("image/numbers/Sc_m.bmp", 150, 16, 10, 1, true, RGB(0, 0, 0));
			break;
		case SC_B:
			tempNum->init("image/numbers/Sc_b.bmp", 180, 22, 10, 1, true, RGB(0, 0, 0));
			break;
		default:
			break;
		}
		tempNum->setFrameX(_vNumbers[i]);
		_vNumber.push_back(tempNum);
	}
	
}

vector<image*> numbering::getNumber(int number, NUMBER_TYPE type)
{
	_nNumber = number;
	_typeNumber = type;

	divideNumToVec();
	changeNumToImg();

	return _vNumber;
}
