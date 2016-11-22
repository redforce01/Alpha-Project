#include "stdafx.h"
#include "selectingUI.h"


selectingUI::selectingUI()
{
}


selectingUI::~selectingUI()
{
}

HRESULT selectingUI::init()
{
	_x = _y = 0;
	_indicator = IMAGEMANAGER->addFrameImage("ship_indicator", "image/battle/greenIndicator.bmp", 6300, 175, 36, 1, true, RGB(0, 0, 0));
	_rcIndicator = RectMakeCenter(_x, _y, _indicator->getFrameWidth(), _indicator->getFrameHeight());
	_frame = 0;
	_frameTime = 0;
	_knt = 0.f;
	
	return S_OK;
}

void selectingUI::release()
{
}

void selectingUI::update()
{
	if (_indicator)
	{
		_frameTime++;
		if (_frameTime % 2 == 0)
		{
			_frame++;
			_indicator->setFrameX(_frame);
			if (_frame > _indicator->getMaxFrameX()) _frame = 0;
		}

		//_vKnt = NUMBERINGMANAGER->getNumber((int)_knt, NGS);
		_rcIndicator = RectMakeCenter(_x, _y, _indicator->getFrameWidth(), _indicator->getFrameHeight());
	}
}

void selectingUI::render()
{
	if (_indicator)
	{
		_indicator->frameRender(getMemDC(), _rcIndicator.left, _rcIndicator.top, _indicator->getFrameX(), _indicator->getFrameY());

		for (unsigned int i = 0; i < _vKnt.size(); i++)
		{
			//_vKnt[i]->frameRender(getMemDC(), _rcIndicator.left + 130 + (6 * i), _rcIndicator.top + 111, _vKnt[i]->getFrameX(), _vKnt[i]->getFrameY());
		}
	}	
}

void selectingUI::setIndicatorPos(float x, float y)
{
	_x = x;
	_y = y;
}

void selectingUI::functionCameraLeft(int cameraSpeed)
{
	_x += cameraSpeed;
}

void selectingUI::functionCameraRight(int cameraSpeed)
{
	_x -= cameraSpeed;
}

void selectingUI::functionCameraUp(int cameraSpeed)
{
	_y += cameraSpeed;
}

void selectingUI::functionCameraDown(int cameraSpeed)
{
	_y -= cameraSpeed;
}
