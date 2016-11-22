#pragma once
#include "gameNode.h"
#include "eventBattle.h"
class eventManager : public gameNode
{
private:
	vector<eventBattle*> _vEvent;
	vector<eventBattle*>::iterator _viEvent;

private:
	float _timeWorldMap;
	
	
public:
	eventManager();
	~eventManager();

	HRESULT init();
	void release();
	void update();
	void render();

	vector<eventBattle*> getvEvent() { return _vEvent; }
	vector<eventBattle*>::iterator getviEvent() { return _viEvent; }
};

