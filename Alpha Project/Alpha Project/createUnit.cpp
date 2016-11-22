#include "stdafx.h"
#include "createUnit.h"


createUnit::createUnit()
{
}


createUnit::~createUnit()
{
}

HRESULT createUnit::init()
{
	_fieldTopImage = NULL;
	_fieldCenterImage = NULL;
	_fieldBottomImage = NULL;
	_rcUnit = RectMake(0, 0, 0, 0);
	_x = _y = 0;
	_frame = 0;
	_setUpTime = 0;
	_isSetUp = false;

	return S_OK;
}

void createUnit::release()
{
}

void createUnit::update()
{
	if (_setUpTime < UNIT_SETUP_TIME) _setUpTime += TIMEMANAGER->getElapsedTime();
	else _isSetUp = true;

	_rcUnit = RectMakeCenter(_x, _y, _fieldTopImage->getFrameWidth(), _fieldTopImage->getFrameHeight());
}

void createUnit::render()
{
	if (!getOnWindowScreen(&_rcUnit)) 
		return;
	
	if (_fieldTopImage) _fieldTopImage->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldTopImage->getFrameX(), _fieldTopImage->getMaxFrameY());
	if (_fieldCenterImage) _fieldCenterImage->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldCenterImage->getFrameX(), _fieldCenterImage->getMaxFrameY());
	if (_fieldBottomImage) _fieldBottomImage->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldBottomImage->getFrameX(), _fieldBottomImage->getMaxFrameY());
}

void createUnit::setUnit(string imageName, float x, float y)
{
	char fieldTopImageKey[128] = "field_top_";
	char fieldCenterImageKey[128] = "field_center_";
	char fieldBottomImageKey[128] = "field_bottom_";

	strcat_s(fieldTopImageKey, imageName.c_str());
	strcat_s(fieldCenterImageKey, imageName.c_str());
	strcat_s(fieldBottomImageKey, imageName.c_str());

	_fieldTopImage = IMAGEMANAGER->findImage(fieldTopImageKey);
	_fieldCenterImage = IMAGEMANAGER->findImage(fieldCenterImageKey);
	_fieldBottomImage = IMAGEMANAGER->findImage(fieldBottomImageKey);

	_x = x, _y = y;
	_rcUnit = RectMakeCenter(_x, _y, _fieldTopImage->getFrameWidth(), _fieldTopImage->getFrameHeight());
	_fieldTopImage->setFrameX(_frame);
	_fieldTopImage->setFrameY(_frame);
	_fieldCenterImage->setFrameX(_frame);
	_fieldCenterImage->setFrameX(_frame);
	_fieldBottomImage->setFrameY(_frame);
	_fieldBottomImage->setFrameY(_frame);
	_setUpPos = PointMake(_x, _y);
}

void createUnit::functionCameraLeft(int cameraSpeed)
{
	_x += cameraSpeed;
}

void createUnit::functionCameraRight(int cameraSpeed)
{
	_x -= cameraSpeed;
}

void createUnit::functionCameraUp(int cameraSpeed)
{
	_y += cameraSpeed;
}

void createUnit::functionCameraDown(int cameraSpeed)
{
	_y -= cameraSpeed;
}
