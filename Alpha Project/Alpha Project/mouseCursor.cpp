#include "stdafx.h"
#include "mouseCursor.h"


mouseCursor::mouseCursor()
{
}


mouseCursor::~mouseCursor()
{
}

HRESULT mouseCursor::init()
{
	IMAGEMANAGER->addFrameImage("mouseCursor_pyramid", "image/cursor/mouseCursor_pyramid.bmp", 1100, 90, 10, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("mouseCursor_compass", "image/cursor/mouseCursor_compass.bmp", 1100, 90, 10, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("mouseCursor_CompassShadow", "image/cursor/CompassShadow.bmp", 1100, 90, 10, 1, true, RGB(0, 0, 0));

	_cursorPyramid = IMAGEMANAGER->findImage("mouseCursor_pyramid");
	_cursorCompass = IMAGEMANAGER->findImage("mouseCursor_compass");
	_cursorCompassShadow = IMAGEMANAGER->findImage("mouseCursor_CompassShadow");

	_rcCursor = RectMake(_ptMouse.x, _ptMouse.y, _cursorPyramid->getFrameWidth(), _cursorPyramid->getFrameHeight());
	_frame = 0;
	_frameTime = 0;
	//ShowCursor(false);

	return S_OK;
}

void mouseCursor::release()
{
}

void mouseCursor::update()
{
	_frameTime++;
	if (_frameTime % 2 == 0)
	{
		_frame++;
		_cursorPyramid->setFrameX(_frame);
		_cursorCompass->setFrameX(_frame);
		_cursorCompassShadow->setFrameX(_frame);
		if (_frame > _cursorPyramid->getMaxFrameX()) _frame = 0;
	}

	_rcCursor = RectMake(_ptMouse.x - CURSOR_NORMALIZE_X, _ptMouse.y - CURSOR_NORMALIZE_Y, _cursorPyramid->getFrameWidth(), _cursorPyramid->getFrameHeight());

	//int height = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));

	//if (_ptMouse.y >= 20) ShowCursor(false);
	//else ShowCursor(true);
}

void mouseCursor::render()
{
	_cursorPyramid->frameRender(getMemDC(), _rcCursor.left, _rcCursor.top, _cursorPyramid->getFrameX(), _cursorPyramid->getMaxFrameY());
	_cursorCompass->frameRender(getMemDC(), _rcCursor.left, _rcCursor.top, _cursorCompass->getFrameX(), _cursorCompass->getMaxFrameY());
	_cursorCompassShadow->shadowRender(getMemDC(), _rcCursor.left, _rcCursor.top, _cursorCompassShadow->getFrameX(), _cursorCompassShadow->getMaxFrameY());
}
