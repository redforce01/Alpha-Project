#pragma once

#include "image.h"
#define WORLDMAP_WIDTH 4261
#define WORLDMAP_HEIGHT 2067

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _battleBuffer = IMAGEMANAGER->addImage("battleBuffer", WINSIZEX * 3, WINSIZEY * 3);
//static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WORLDMAP_WIDTH, WORLDMAP_HEIGHT);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	image* getBackBuffer() { return _backBuffer; }	
	image* getBattleBuffer() { return _battleBuffer; }
	HDC getBattleDC() { return _battleBuffer->getMemDC(); }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

