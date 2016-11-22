#include "stdafx.h"
#include "battleBottomExtend.h"


battleBottomExtend::battleBottomExtend()
{
}


battleBottomExtend::~battleBottomExtend()
{
}

HRESULT battleBottomExtend::init()
{
	_bottomExtend = IMAGEMANAGER->findImage("battle_bottomExtend");
	_rcBottomExtend = RectMake(0, WINSIZEY - _bottomExtend->getHeight(), _bottomExtend->getWidth(), _bottomExtend->getHeight());

	return S_OK;
}

void battleBottomExtend::release()
{
}

void battleBottomExtend::update()
{
}

void battleBottomExtend::render()
{
	_bottomExtend->render(getMemDC(), _rcBottomExtend.left, _rcBottomExtend.top);
}
