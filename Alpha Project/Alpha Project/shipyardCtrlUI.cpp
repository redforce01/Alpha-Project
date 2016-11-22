#include "stdafx.h"
#include "shipyardCtrlUI.h"


shipyardCtrlUI::shipyardCtrlUI()
{
}


shipyardCtrlUI::~shipyardCtrlUI()
{
}

HRESULT shipyardCtrlUI::init()
{
	_btnBuy = new button;
	_btnSell = new button;
	_btnRepair = new button;

	_btnBuy->init("btnBuy", 130, 325, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionBuy, this);
	_btnSell->init("btnSell", 160, 325, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionSell, this);
	_btnRepair->init("btnRepair", 200, 325, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionRepair, this);

	return E_NOTIMPL;
}

void shipyardCtrlUI::release()
{
	_btnBuy->release();
	_btnSell->release();
	_btnRepair->release();
}

void shipyardCtrlUI::update()
{
	_btnBuy->update();
	_btnSell->update();
	_btnRepair->update();
}

void shipyardCtrlUI::render()
{
	_btnBuy->render();
	_btnSell->render();
	_btnRepair->render();
}

void shipyardCtrlUI::functionBuy(void * obj)
{
}

void shipyardCtrlUI::functionSell(void * obj)
{
}

void shipyardCtrlUI::functionRepair(void * obj)
{
}
