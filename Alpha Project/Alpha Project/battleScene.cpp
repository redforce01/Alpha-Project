#include "stdafx.h"
#include "battleScene.h"


battleScene::battleScene()
{
}


battleScene::~battleScene()
{
}

HRESULT battleScene::init()
{
	_battleLoading = new battleLoading;
	_battleLoading->init();
	
	_battleMap = new battleMap;
	_battleMap->init();

	_battleUI = new battleUI;
	_battleUI->init();

	_battleManager = new battleManager;
	_battleManager->init();

	_battleUI->setMemoryLinkBattleMap(_battleMap);
	_battleUI->setMemoryLinkBattleMgr(_battleManager);


	_unitAvailability = new unitAvailability;
	_unitAvailability->init();

	_zoomDeltaX = _zoomDeltaY = 0;

	return S_OK;
}

void battleScene::release()
{
	_battleLoading->release();
	_battleUI->release();
	_battleMap->release();
	_battleManager->release();

	SAFE_DELETE(_battleLoading);
	SAFE_DELETE(_battleUI);
	SAFE_DELETE(_battleMap);
	SAFE_DELETE(_battleManager);

	_unitAvailability->release();
	SAFE_DELETE(_unitAvailability);
}

void battleScene::update()
{
	if(! _battleLoading->getLoadingComplete()) _battleLoading->update();
	else
	{
		_battleMap->update();
		_battleUI->update();
		_battleManager->update();
	}
}

void battleScene::render()
{	
	if (!_battleLoading->getLoadingComplete()) _battleLoading->render();
	else
	{
		_battleMap->render();
		_battleManager->render();
		_battleUI->render();
	}
}
