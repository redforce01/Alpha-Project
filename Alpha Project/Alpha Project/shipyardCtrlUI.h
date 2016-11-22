#pragma once
#include "gameNode.h"
#include "button.h"
class shipyardCtrlUI : public gameNode
{
private:
	button* _btnBuy;
	button* _btnSell;
	button* _btnRepair;

public:
	shipyardCtrlUI();
	~shipyardCtrlUI();

	HRESULT init();
	void release();
	void update();
	void render();

	static void functionBuy(void* obj);
	static void functionSell(void* obj);
	static void functionRepair(void* obj);

};

