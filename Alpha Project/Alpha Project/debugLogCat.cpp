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
	for (_viLog = _vLog.begin(); _viLog != _vLog.end(); ++_viLog, i++)
	{
		TextOut(hdc, WINSIZEX - 280, 100 + (i * 20), _viLog->second.c_str(), strlen(_viLog->second.c_str()));		
	}

	i = 0;
	for (_viLog2 = _vLog2.begin(); _viLog2 != _vLog2.end(); ++_viLog2, i++)
	{
		TextOut(hdc, 20, 100 + (i * 20), _viLog2->second.c_str(), strlen(_viLog2->second.c_str()));
	}

	SetTextColor(hdc, RGB(0, 0, 0));
#endif // DEBUG
}

void debugLogCat::addLog(string logName, const char * log)
{
	//���� Ÿ���� �α� ��ð� �ִ��� Ȯ������
	for (_viLog = _vLog.begin(); _viLog != _vLog.end(); ++_viLog)
	{
		//���� ���� Ÿ���� �αװ� �ִٸ� ���� ����������
		if ((logName == _viLog->first))
		{
			_viLog->second = log;
			return;
		}
	}

	_vLog.insert(pair<string, string>(logName, log));
}

void debugLogCat::addLog2(string logName, const char * log)
{
	//���� Ÿ���� �α� ��ð� �ִ��� Ȯ������
	for (_viLog2 = _vLog2.begin(); _viLog2 != _vLog2.end(); ++_viLog2)
	{
		//���� ���� Ÿ���� �αװ� �ִٸ� ���� ����������
		if ((logName == _viLog2->first))
		{
			_viLog2->second = log;
			return;
		}
	}

	_vLog2.insert(pair<string, string>(logName, log));
}
