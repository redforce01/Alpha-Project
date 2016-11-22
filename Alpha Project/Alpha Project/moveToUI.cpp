#include "stdafx.h"
#include "moveToUI.h"


moveToUI::moveToUI()
{
}


moveToUI::~moveToUI()
{
}

HRESULT moveToUI::init()
{
	_moveTo = new image;
	_moveTo->init("image/battle/MoveTo.bmp", 3400, 100, 34, 1, true, RGB(0, 0, 0));
	_rcMoveTo = RectMake(0, 0, 0, 0);
	_x = _y = 0;

	_frame = 0;
	_frameTime = 0;
	_isShow = FALSE;

	return S_OK;
}

void moveToUI::release()
{
}

void moveToUI::update()
{
	if (NULL != _moveTo)
	{
		if (_isShow)
		{
			_frameTime++;
			if (_frameTime % 2 == 0)
			{
				_frame++;
				_moveTo->setFrameX(_frame);
				if (_frame > _moveTo->getMaxFrameX())
				{
					_isShow = FALSE;
					_frame = 0;
					_frameTime = 0;
				}
			}

			_rcMoveTo = RectMakeCenter(_x, _y, _moveTo->getFrameWidth(), _moveTo->getFrameHeight());
		}
	}
}

void moveToUI::render()
{
	if (NULL != _moveTo)
	{
		if (_isShow)
		{
			_moveTo->frameRender(getMemDC(), _rcMoveTo.left, _rcMoveTo.top, _moveTo->getFrameX(), _moveTo->getFrameY());
		}
	}
}

void moveToUI::setMoveToPos(float x, float y)
{
	_x = x;
	_y = y;
}

void moveToUI::functionCameraLeft(int cameraSpeed)
{
	_x += cameraSpeed;
}

void moveToUI::functionCameraRight(int cameraSpeed)
{
	_x -= cameraSpeed;
}

void moveToUI::functionCameraUp(int cameraSpeed)
{
	_y += cameraSpeed;
}

void moveToUI::functionCameraDown(int cameraSpeed)
{
	_y -= cameraSpeed;
}
