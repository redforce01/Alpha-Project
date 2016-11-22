#pragma once
#include "gameNode.h"
class unitManager : public gameNode
{
private:
	

public:
	unitManager();
	~unitManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

