#include "stdafx.h"
#include "harborShip.h"


harborShip::harborShip()
{
}


harborShip::~harborShip()
{
}

HRESULT harborShip::init()
{
	_bHasShip = false;
	_shipName = "";

	_shipTop = new image;
	_shipBottom = new image;
	_shipX = 700;
	_shipY = 410;

	_rcShip = RectMake(0, 0, 0, 0);
	_bChanged = true;
	_alphaValue = 0.f;

	return S_OK;
}

void harborShip::relaese()
{
}

void harborShip::update()
{
	char loadKeyTop[256] = "harbor_";
	char loadKeyCenter[256] = "harbor_";
	char loadKeyBottom[256] = "harbor_";
		
	char shipTopKey[128] = "top_";
	char shipCenterKey[128] = "center_";
	char shipBottomKey[128] = "bottom_";

	strcat_s(loadKeyTop, shipTopKey);
	strcat_s(loadKeyBottom, shipCenterKey);
	strcat_s(loadKeyCenter, shipBottomKey);

	strcat_s(loadKeyTop, _shipName.c_str());
	strcat_s(loadKeyCenter, _shipName.c_str());
	strcat_s(loadKeyBottom, _shipName.c_str());

	if (_bHasShip)
	{
		_shipTop = IMAGEMANAGER->findImage(loadKeyTop);
		_shipCenter = IMAGEMANAGER->findImage(loadKeyCenter);
		_shipBottom = IMAGEMANAGER->findImage(loadKeyBottom);

		_rcShip = RectMakeCenter(_shipX, _shipY, _shipTop->getWidth(), _shipTop->getHeight());
	}

	if (_bChanged)
	{
		_alphaValue += ALPHA_CHANGE_SPEED;
		
		if (_alphaValue > 255)
		{
			_alphaValue = 255;
			_bChanged = false;
		}
	}
}

void harborShip::render()
{
	if (_bHasShip)
	{
		if (_shipTop) _shipTop->alphaRender(getMemDC(), _rcShip.left, _rcShip.top, _alphaValue);
		if (_shipCenter) _shipCenter->alphaRender(getMemDC(), _rcShip.left, _rcShip.top, _alphaValue);
		if (_shipBottom) _shipBottom->alphaRender(getMemDC(), _rcShip.left, _rcShip.top, _alphaValue);
	}
}



