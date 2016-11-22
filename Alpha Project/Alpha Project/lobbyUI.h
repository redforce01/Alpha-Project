#pragma once
#include "gameNode.h"
#include "button.h"
class lobbyUI : public gameNode
{
private:
	button* _btnShipYard;
	button* _btnBattle;
	button* _btnMaptool;
	button* _btnOption;
	button* _btnCredit;
	button* _btnExit;

	bool _bChangeScene;

public:
	lobbyUI();
	~lobbyUI();

	HRESULT init();
	void release();
	void update();
	void render();

	static void functionShipYard(void* obj);
	static void functionBattle(void* obj);
	static void functionExit(void* obj);
	static void functionMaptool(void* obj);
	static void functionOption(void* obj);
	static void functionCredit(void* obj);
};

