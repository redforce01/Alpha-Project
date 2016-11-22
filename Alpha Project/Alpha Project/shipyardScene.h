#pragma once
#include "gameNode.h"
#include "shipyardUI.h"
class shipyardScene : public gameNode
{
private:
	image* _background;	
	shipyardUI* _shipyardUI;

public:
	shipyardScene();
	~shipyardScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

