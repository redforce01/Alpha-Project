#pragma once
#include "gameNode.h"
#include "button.h"
class titleUI : public gameNode
{
private:
	button* _btnJoin;
	button* _btnCancel;

public:
	titleUI();
	~titleUI();

	HRESULT init();
	void release();
	void update();
	void render();

	static void functionJoin(void* obj);
	static void functionCancel(void* obj);
};

