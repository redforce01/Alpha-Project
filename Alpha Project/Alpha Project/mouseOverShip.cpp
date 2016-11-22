#include "stdafx.h"
#include "mouseOverShip.h"


mouseOverShip::mouseOverShip()
{
}


mouseOverShip::~mouseOverShip()
{
}

HRESULT mouseOverShip::init()
{
	_shipTop	= NULL;
	_shipCenter	= NULL;
	_shipBottom	= NULL;
	_unitName	= "";
	_x = _y		= 0;
	_rcUnit		= RectMakeCenter(0, 0, 0, 0);
	_frame		= 0;
	_isSetUp	= false;

	return S_OK;
}

void mouseOverShip::release()
{
}

void mouseOverShip::update()
{
	_x = _ptMouse.x;
	_y = _ptMouse.y;
	
	if (_isSetUp)
	{
		if(_shipTop) _rcUnit = RectMakeCenter(_x, _y, _shipTop->getFrameWidth(), _shipTop->getFrameHeight());
	}
}

void mouseOverShip::render()
{
	if (!getOnWindowScreen(&_rcUnit)) return;
	
	if (_isSetUp)
	{
		if(_shipBottom) _shipBottom->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _shipBottom->getFrameX(), _shipBottom->getFrameY());
		if(_shipCenter) _shipCenter->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _shipCenter->getFrameX(), _shipCenter->getFrameY());
		if(_shipTop) _shipTop->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _shipTop->getFrameX(), _shipTop->getFrameY());
	}
}

void mouseOverShip::setUnit(string unitName)
{
	_unitName = unitName;
	char unitFieldTopImageKey[128] = "";
	char unitFieldCenterImageKey[128] = "";
	char unitFieldBottomImageKey[128] = "";

	strcat_s(unitFieldTopImageKey, "field_top_");
	strcat_s(unitFieldCenterImageKey, "field_center_");
	strcat_s(unitFieldBottomImageKey, "field_bottom_");

	strcat_s(unitFieldTopImageKey, _unitName.c_str());
	strcat_s(unitFieldCenterImageKey, _unitName.c_str());
	strcat_s(unitFieldBottomImageKey, _unitName.c_str());

	_shipTop	= IMAGEMANAGER->findImage(unitFieldTopImageKey);
	_shipCenter = IMAGEMANAGER->findImage(unitFieldCenterImageKey);
	_shipBottom = IMAGEMANAGER->findImage(unitFieldBottomImageKey);

	_shipTop	->setFrameX(0);  _shipTop		->setFrameY(0);
	_shipCenter	->setFrameX(0);  _shipCenter	->setFrameY(0);
	_shipBottom	->setFrameX(0);  _shipBottom	->setFrameY(0);




	_isSetUp = true;
}
