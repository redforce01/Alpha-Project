#pragma once
#include "gameNode.h"
class battleBottomExtend : public gameNode
{
private:
	image* _bottomExtend;
	RECT _rcBottomExtend;



public:
	battleBottomExtend();
	~battleBottomExtend();

	HRESULT init();
	void release();
	void update();
	void render();
};

