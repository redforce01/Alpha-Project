#pragma once
#include "gameNode.h"
class TestScene : public gameNode
{
private:
	float x1, x2, y1, y2;
	RECT _rc1, _rc2;

	image* _character;
	RECT _rcCharacter;
	int _frameTime;
	int _frame;


public:
	TestScene();
	~TestScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

