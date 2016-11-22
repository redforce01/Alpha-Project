#pragma once
#include "gameNode.h"
#include "button.h"
class topExtendUI : public gameNode
{
private:
	image* _topExtendUI;

	button* _btnHarbor;
	button* _btnBattle;
	button* _btnDepot;
	button* _btnTrade;

	SYSTEMTIME _st;
	int _timeHH;
	int _timeMM;
	char _strHH[32];
	char _strMM[32];

public:
	topExtendUI();
	~topExtendUI();

	HRESULT init();
	void release();
	void update();
	void render();

	static void functionTrade(void* obj);
	static void functionBattle(void* obj);
	static void functionDepot(void* obj);
	static void functionHarbor(void* obj);
};

