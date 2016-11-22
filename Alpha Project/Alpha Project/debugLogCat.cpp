#include "stdafx.h"
#include "debugLogCat.h"


debugLogCat::debugLogCat()
{
}


debugLogCat::~debugLogCat()
{
}

void debugLogCat::init()
{
}

void debugLogCat::release()
{
}

void debugLogCat::update()
{	
}

void debugLogCat::render(HDC hdc)
{
#ifdef DEBUG
	SetTextColor(hdc, RGB(255, 255, 255));
	int i = 0;
	for (_viLog = _vLog.begin(); _viLog != _vLog.end(); ++_viLog)
	{
		TextOut(hdc, WINSIZEX - 280, 100 + (i * 20), _viLog->second.c_str(), strlen(_viLog->second.c_str()));
		i++;
	}
	SetTextColor(hdc, RGB(0, 0, 0));
#endif // DEBUG
}

void debugLogCat::addLog(string logName, const char * log)
{
	//같은 타입의 로그 명시가 있는지 확인하자
	for (_viLog = _vLog.begin(); _viLog != _vLog.end(); ++_viLog)
	{
		//만약 같은 타입의 로그가 있다면 값만 변경해주자
		if ((logName == _viLog->first))
		{
			_viLog->second = log;
			return;
		}
	}

	_vLog.insert(pair<string, string>(logName, log));
}
