#pragma once
#include "gameNode.h"
#include "IsoMetricWorld.h"
#include "worldMapUI.h"
#include "eventManager.h"
class worldMapScene : public gameNode
{
private:
	IsoMetricWorld* _IsoMetricWorld;
	worldMapUI* _worldMapUI;
	eventManager* _eventManager;
public:
	worldMapScene();
	~worldMapScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

