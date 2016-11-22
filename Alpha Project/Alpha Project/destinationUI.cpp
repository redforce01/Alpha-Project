#include "stdafx.h"
#include "destinationUI.h"


destinationUI::destinationUI()
{
}


destinationUI::~destinationUI()
{
}

HRESULT destinationUI::init()
{
	_destination = new image;
	_destination->init("image/battle/Destination.bmp", 2700, 75, 36, 1, true, RGB(0, 0, 0));

	_rcDestination = RectMake(0, 0, 0, 0);
	_x = _y = 0;

	_frame = 0;
	_frameTime = 0;

	_showTime = 0;
	_isFinish = false;
	_isShow = false;

	return S_OK;
}

void destinationUI::release()
{
}

void destinationUI::update()
{
	if (_destination != NULL)
	{

		if (_showTime < DESTINATION_TIME) _showTime += TIMEMANAGER->getElapsedTime();
		else
		{
			_isFinish = true;
			return;
		}

		_frameTime++;
		if (_frameTime % 2 == 0)
		{
			_destination->setFrameX(_frame);
			_frame++;

			if (_frame > _destination->getMaxFrameX()) _frame = 0;
		}

		_rcDestination = RectMakeCenter(_x, _y, _destination->getFrameWidth(), _destination->getFrameHeight());
	}
}

void destinationUI::render()
{	
	if (_destination != NULL)
	{
		if (_isShow)
		{
			if (_isFinish == FALSE) _destination->frameRender(getBattleDC(), _rcDestination.left, _rcDestination.top, _destination->getFrameX(), _destination->getFrameY());
		}
	}
}

void destinationUI::setDestPos(float x, float y)
{
	_x = x;
	_y = y;
}

void destinationUI::setReInit()
{
	_showTime = 0.f;
	_frameTime = 0;
	_frame = 0;
	_isFinish = FALSE;
}

void destinationUI::functionCameraLeft(int cameraSpeed)
{
	_x += cameraSpeed;
}

void destinationUI::functionCameraRight(int cameraSpeed)
{
	_x -= cameraSpeed;
}

void destinationUI::functionCameraUp(int cameraSpeed)
{
	_y += cameraSpeed;
}

void destinationUI::functionCameraDown(int cameraSpeed)
{
	_y -= cameraSpeed;
}
