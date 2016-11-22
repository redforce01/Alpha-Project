#include "stdafx.h"
#include "eventBattle.h"


eventBattle::eventBattle()
{
}


eventBattle::~eventBattle()
{
}


HRESULT eventBattle::init(float x, float y, WORLDMAP_EVENT_TYPE event)
{
	_event = new image;
	_event->init("image/worldMap/WorldMap_Battle.bmp", 6912, 128, 54, 1, true, RGB(0, 0, 0));
	_x = x, _y = y;
	_rc = RectMakeCenter(_x, _y, _event->getFrameWidth(), _event->getFrameHeight());
	_type = event;

	_timeFrame = 0;
	_frame = 0;

	return S_OK;
}

void eventBattle::release()
{	
}

void eventBattle::update()
{
	_timeFrame++;
	if (_timeFrame % 5 == 0)
	{
		if (_frame > _event->getMaxFrameX()) _frame = 0;
		_event->setFrameX(_frame);
		_frame++;
	}
	
}

void eventBattle::render()
{
	_event->frameRender(getMemDC(), _rc.left, _rc.top, _event->getFrameX(), _event->getFrameY());
}
