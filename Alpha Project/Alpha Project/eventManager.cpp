#include "stdafx.h"
#include "eventManager.h"


eventManager::eventManager()
{
}


eventManager::~eventManager()
{
}

HRESULT eventManager::init()
{
	_timeWorldMap = 0.f;

	return S_OK;
}

void eventManager::release()
{
	int vSize = _vEvent.size();
	for (int i = 0; i < vSize; i++)
	{
		_vEvent[i]->release();
	}
	_vEvent.clear();
}

void eventManager::update()
{
	_timeWorldMap += TIMEMANAGER->getElapsedTime();
	if (_timeWorldMap > 3.0f)
	{
		_timeWorldMap = 0;
		eventBattle* _eventBattle;
		_eventBattle = new eventBattle;
		_eventBattle->init(RND->getFromIntTo(CENTERX - 200, CENTERX + 200), RND->getFromIntTo(CENTERY - 200, CENTERY + 200), WORLDMAP_BATTLE);
		_vEvent.push_back(_eventBattle);
	}
	

	int vSize = _vEvent.size();
	for (int i = 0; i < vSize; i++)
	{
		_vEvent[i]->update();
	}
}

void eventManager::render()
{
	int vSize = _vEvent.size();
	for (int i = 0; i < vSize; i++)
	{
		_vEvent[i]->render();
	}
}
