#pragma once
#include "singletonBase.h"
class debugLogCat : public singletonBase<debugLogCat>
{
private:
	map<string, string> _vLog;
	map<string, string>::iterator _viLog;

public:
	debugLogCat();
	~debugLogCat();

	void init();
	void release();
	void update();
	void render(HDC hdc);

	void addLog(string logName, const char* log);
};

