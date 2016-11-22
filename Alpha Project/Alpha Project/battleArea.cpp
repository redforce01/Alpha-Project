#include "stdafx.h"
#include "battleArea.h"


battleArea::battleArea()
{
}


battleArea::~battleArea()
{
}

HRESULT battleArea::init()
{
	_areaFlag = NULL;
	_rcAreaFlag = RectMake(0, 0, 0, 0);
	_frame = 0;
	_frameTime = 0;

	_x = _y = 0;
	_rcArea = RectMake(0, 0, 0, 0);
	_areaType = BATTLE_AREA_NORMAL;

	return S_OK;
}

void battleArea::release()
{
	_areaFlag->release();
	SAFE_DELETE(_areaFlag);
}

void battleArea::update()
{	
	_frameTime++;
	if (_frameTime % 2 == 0)
	{
		_areaFlag->setFrameX(_frame);
		if (_frame > _areaFlag->getMaxFrameX()) _frame = 0;
		_frame++;
	}

	_rcAreaFlag = RectMakeCenter(_x, _y, _areaFlag->getFrameWidth(), _areaFlag->getFrameHeight());
	_rcArea = RectMakeCenter(_x, _y, AREA_RADIAN_SIZE, AREA_RADIAN_SIZE);
}

void battleArea::render()
{
	if (getOnWindowScreen(&_rcArea))
	{
		HBRUSH myBrush, oldBrush;
		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oldBrush = (HBRUSH)SelectObject(getBattleDC(), myBrush);

		Ellipse(getBattleDC(), _rcArea.left, _rcArea.top, _rcArea.right, _rcArea.bottom);
		_areaFlag->frameRender(getBattleDC(), _rcAreaFlag.left, _rcAreaFlag.top, _areaFlag->getFrameX(), _areaFlag->getFrameY());


		SelectObject(getBattleDC(), oldBrush);
		DeleteObject(myBrush);
	}
}

void battleArea::InitArea(float x, float y, int flagNumber)
{
	_x = x;
	_y = y;

	char battleAreaFlagKey[256];
	sprintf_s(battleAreaFlagKey, "image/battle/flag/Flag%d.bmp", flagNumber);

	_areaFlag = new image;
	_areaFlag->init(battleAreaFlagKey, 4600, 60, 46, 1, true, RGB(0, 0, 0));
}

void battleArea::functionMoveLeft(int cameraSpeed)
{
	_rcAreaFlag.left += cameraSpeed;
	_rcAreaFlag.right += cameraSpeed;
	_rcArea.left += cameraSpeed;
	_rcArea.right += cameraSpeed;
	_x += cameraSpeed;
}

void battleArea::functionMoveRight(int cameraSpeed)
{
	_rcAreaFlag.left -= cameraSpeed;
	_rcAreaFlag.right -= cameraSpeed;
	_rcArea.left -= cameraSpeed;
	_rcArea.right -= cameraSpeed;
	_x -= cameraSpeed;
}

void battleArea::functionMoveUp(int cameraSpeed)
{
	_rcAreaFlag.top += cameraSpeed;
	_rcAreaFlag.bottom += cameraSpeed;
	_rcArea.top += cameraSpeed;
	_rcArea.bottom += cameraSpeed;
	_y += cameraSpeed;
}

void battleArea::functionMoveDown(int cameraSpeed)
{
	_rcAreaFlag.top -= cameraSpeed;
	_rcAreaFlag.bottom -= cameraSpeed;
	_rcArea.top -= cameraSpeed;
	_rcArea.bottom -= cameraSpeed;
	_y -= cameraSpeed;
}

void battleArea::setAreaMaster(BATTLE_AREA_TYPE masterType)
{
	_areaType = masterType;
}
