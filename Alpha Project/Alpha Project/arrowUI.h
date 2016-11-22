#pragma once
#include "gameNode.h"
#include "button.h"
class arrowUI : public gameNode
{
private:
	button* _btnArrowLeft;
	button* _btnArrowRight;	
	button* _btnArrowLaunch;



public:
	bool _bClickedLeft;
	bool _bClickedRight;
	bool _bClickedLaunch;

public:
	arrowUI();
	~arrowUI();

	HRESULT init();
	void release();
	void update();
	void render();

	static void functionArrowLeft(void* obj);
	static void functionArrowRight(void* obj);
	static void functionArrowLaunch(void* obj);
};

