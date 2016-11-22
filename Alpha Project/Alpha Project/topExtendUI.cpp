#include "stdafx.h"
#include "topExtendUI.h"


topExtendUI::topExtendUI()
{
}


topExtendUI::~topExtendUI()
{
}

HRESULT topExtendUI::init()
{
	_topExtendUI = IMAGEMANAGER->findImage("topExtendUI");
	
	_btnHarbor = new button;
	_btnBattle = new button;
	_btnDepot = new button;
	_btnTrade = new button;

	_btnHarbor	->init("btnShipyard", 1248, 8, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionHarbor, this);
	_btnBattle	->init("btnBattle",  1200, 8, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionBattle, this);
	_btnDepot	->init("btnDepot", 1150, 8, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionDepot, this);
	_btnTrade	->init("btnTrade", 1100, 8, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionTrade, this);

	GetLocalTime(&_st);
	_timeHH = _st.wHour;
	_timeMM = _st.wMinute;

	return S_OK;
}

void topExtendUI::release()
{
	_btnHarbor	->release();
	_btnBattle	->release();
	_btnDepot	->release();
	_btnTrade	->release();
}

void topExtendUI::update()
{
	GetLocalTime(&_st);
	_timeHH = _st.wHour;
	_timeMM = _st.wMinute;


	_btnHarbor	->update();
	_btnBattle	->update();
	_btnDepot	->update();
	_btnTrade	->update();
}

void topExtendUI::render()
{
	_topExtendUI->render(getMemDC(), 0, 0);

	_itoa_s(_timeHH, _strHH, 10);
	_itoa_s(_timeMM, _strMM, 10);

	if (_timeHH < 10) sprintf_s(_strHH, "0%d", _timeHH);
	if (_timeMM < 10) sprintf_s(_strMM, "0%d", _timeMM);

	TextOut(getMemDC(), 530, 0, _strHH, strlen(_strHH));
	TextOut(getMemDC(), 550, 0, ":", 1);
	TextOut(getMemDC(), 560, 0, _strMM, strlen(_strMM));



	_btnHarbor	->render();
	_btnBattle	->render();
	_btnDepot	->render();
	_btnTrade	->render();
}

void topExtendUI::functionTrade(void * obj)
{
}

void topExtendUI::functionBattle(void * obj)
{
	SCENEMANAGER->changeScene("battleScene");
}

void topExtendUI::functionDepot(void * obj)
{
}

void topExtendUI::functionHarbor(void * obj)
{
}
