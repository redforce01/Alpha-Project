#include "stdafx.h"
#include "arrowUI.h"


arrowUI::arrowUI()
{
}


arrowUI::~arrowUI()
{
}

HRESULT arrowUI::init()
{	
	_btnArrowLeft = new button;
	_btnArrowRight = new button;
	_btnArrowLaunch = new button;

	_btnArrowLeft->init("btnArrowLeft", 500, 630, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionArrowLeft, this);
	_btnArrowRight->init("btnArrowRight", 310, 420, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionArrowRight, this);
	_btnArrowLaunch->init("btnArrowLaunch", 100, 650, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionArrowLaunch, this);

	return S_OK;
}

void arrowUI::release()
{
	_btnArrowLeft->release();
	_btnArrowRight->release();
	_btnArrowLaunch->release();

	SAFE_DELETE(_btnArrowLeft);
	SAFE_DELETE(_btnArrowRight);
	SAFE_DELETE(_btnArrowLaunch);
}

void arrowUI::update()
{
	_btnArrowLeft->update();
	_btnArrowRight->update();
	_btnArrowLaunch->update();
}

void arrowUI::render()
{
	_btnArrowLeft->render();
	_btnArrowRight->render();
	_btnArrowLaunch->render();
}

void arrowUI::functionArrowLeft(void * obj)
{
	arrowUI* _arrowUI = (arrowUI*)obj;
	_arrowUI->_bClickedLeft = true;
}

void arrowUI::functionArrowRight(void * obj)
{
	arrowUI* _arrowUI = (arrowUI*)obj;
	_arrowUI->_bClickedRight = true;
}

void arrowUI::functionArrowLaunch(void * obj)
{
	arrowUI* _arrowUI = (arrowUI*)obj;
	_arrowUI->_bClickedLaunch = true;
}
