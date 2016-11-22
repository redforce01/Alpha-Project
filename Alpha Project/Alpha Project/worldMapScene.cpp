#include "stdafx.h"
#include "worldMapScene.h"


worldMapScene::worldMapScene()
{
}


worldMapScene::~worldMapScene()
{
}

HRESULT worldMapScene::init()
{	

	_IsoMetricWorld = new IsoMetricWorld;
	_IsoMetricWorld->init();
	_worldMapUI = new worldMapUI;
	_worldMapUI->init();

	_eventManager = new eventManager;
	_eventManager->init();


	_worldMapUI->setMemoryLinkIsoWorld(_IsoMetricWorld);
	_worldMapUI->setMemoryLinkEventMgr(_eventManager);

	return S_OK;
}

void worldMapScene::release()
{
	_IsoMetricWorld->release();
	_worldMapUI->release();
	_eventManager->release();

	SAFE_DELETE(_IsoMetricWorld);
	SAFE_DELETE(_worldMapUI);
	SAFE_DELETE(_eventManager);
}

void worldMapScene::update()
{
	_IsoMetricWorld->update();
	_eventManager->update();
	_worldMapUI->update();
}

void worldMapScene::render()
{
	_worldMapUI->render();
	_IsoMetricWorld->render();
	_eventManager->render();

}
