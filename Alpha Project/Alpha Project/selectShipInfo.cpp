#include "stdafx.h"
#include "selectShipInfo.h"


selectShipInfo::selectShipInfo()
{
}


selectShipInfo::~selectShipInfo()
{
}

HRESULT selectShipInfo::init()
{
	_infoGuide = IMAGEMANAGER->addImage("ship_info_guide", "image/battle/ship_info_guide.bmp", 50, 40, true, RGB(0, 0, 0));
	_infoText = IMAGEMANAGER->addImage("ship_infomation_text", "image/battle/ship_infomation_text.bmp", 70, 35, true, RGB(0, 0, 0));
	_infoReload = IMAGEMANAGER->addFrameImage("reload_gauge", "image/battle/ReloadGauge.bmp", 680, 12, 20, 1, true, RGB(0, 0, 0));
	_infoReloadBack = IMAGEMANAGER->addImage("Reload Gauge_back", "image/battle/Reload Gauge_back.bmp", 34, 12, true, RGB(0, 0, 0));

	_rcInfoGuide = RectMake(0, 0, 0, 0);
	_rcInfoText = RectMake(0, 0, 0, 0);
	_rcinfoReload = RectMake(0, 0, 0, 0);

	_guideX = _guideY = 0;
	_reloadTime = 0;

	return S_OK;
}

void selectShipInfo::release()
{
}

void selectShipInfo::update()
{
	_rcInfoGuide = RectMake(_guideX, _guideY, _infoGuide->getWidth(), _infoGuide->getHeight());
	_rcInfoText = RectMake(
		_rcInfoGuide.right,
		_rcInfoGuide.top + (_rcInfoGuide.bottom - _rcInfoGuide.top) / 2,
		_infoText->getWidth(), _infoText->getHeight());
	_rcinfoReload = RectMake(_rcInfoText.left, _rcInfoText.bottom, _infoReloadBack->getWidth(), _infoReloadBack->getHeight());
}

void selectShipInfo::render()
{
	_infoGuide->render(getMemDC(), _rcInfoGuide.left, _rcInfoGuide.top);
	_infoText->render(getMemDC(), _rcInfoText.left, _rcInfoText.top);
	_infoReloadBack->render(getMemDC(), _rcinfoReload.left, _rcinfoReload.top);
	_infoReload->frameRender(getMemDC(), _rcinfoReload.left, _rcinfoReload.top, _infoReload->getFrameX(), _infoReload->getFrameY());
}
