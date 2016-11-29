#pragma once
#include "singletonBase.h"
class debugLogCat : public singletonBase<debugLogCat>
{
private:
	map<string, string> _vLog;
	map<string, string>::iterator _viLog;

	map<string, string> _vLog2;
	map<string, string>::iterator _viLog2;

public:
	debugLogCat();
	~debugLogCat();

	void init();
	void release();
	void update();
	void render(HDC hdc);

	void addLog(string logName, const char* log);
	void addLog2(string logName, const char* log);
};

