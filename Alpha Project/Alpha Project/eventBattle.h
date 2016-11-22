#pragma once
#include "gameNode.h"
class eventBattle : public gameNode
{
private:
	image* _event;
	RECT _rc;
	float _x, _y;
	WORLDMAP_EVENT_TYPE _type;
	int _timeFrame;
	int _frame;

public:
	eventBattle();
	~eventBattle();

	HRESULT init(float x, float y, WORLDMAP_EVENT_TYPE event);
	void release();
	void update();
	void render();

	RECT getEventRect() { return _rc; }
};

