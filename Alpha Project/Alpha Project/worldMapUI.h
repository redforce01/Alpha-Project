#pragma once
#include "gameNode.h"
#include "button.h"
#include "topExtendUI.h"

class eventManager;
class IsoMetricWorld;
class worldMapUI : public gameNode
{
private:
	image* _worldMap;
	button* _btnArrowLeftDown;
	button* _btnArrowLeftUp;
	button* _btnArrowRightDown;
	button* _btnArrowRightUp;

	int _cameraX, _cameraY;
	int _showAreaNumber;

	IsoMetricWorld* _isoMetricWorld;
	topExtendUI* _topExtendUI;
	eventManager* _eventManager;
public:
	worldMapUI();
	~worldMapUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void functionLButtonClick();

	static void functionLeftUp(void* obj);
	static void functionLeftDown(void* obj);
	static void functionRightUp(void* obj);
	static void functionRightDown(void* obj);

	void setMemoryLinkIsoWorld(IsoMetricWorld* IsoMetricWorld) { _isoMetricWorld = IsoMetricWorld; }
	void setMemoryLinkEventMgr(eventManager* eventManager) { _eventManager = eventManager; }
};

