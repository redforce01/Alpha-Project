#include "stdafx.h"
#include "titleScene.h"


titleScene::titleScene()
{
}


titleScene::~titleScene()
{
}

HRESULT titleScene::init()
{
	_background = IMAGEMANAGER->findImage("titleBackground");
	_rcBackground = RectMakeCenter(CENTERX, CENTERY, _background->getWidth(), _background->getHeight());

	_plane = IMAGEMANAGER->findImage("opPlane_1");
	_rcPlane = RectMake(0, 0, _plane->getFrameWidth(), _plane->getFrameHeight());
	_nPlaneFrame = 0;
	_nPlaneTime = 0;
	_nPlaneImgNumber = 0;
	_bShowPlane = true;
	_nPlaneX = 0;

	_login = IMAGEMANAGER->findImage("titleLogin");
	_rcLogin = RectMakeCenter(CENTERX, CENTERY, _login->getWidth(), _login->getHeight());

	_ship = IMAGEMANAGER->findImage("titleShip");
	_rcShip = RectMakeCenter(CENTERX + 14, CENTERY - 195, _ship->getWidth(), _ship->getHeight());

	_titleUI = new titleUI;
	_titleUI->init();

	return S_OK;
}

void titleScene::release()
{
	_titleUI->release();
	SAFE_DELETE(_titleUI);
}

void titleScene::update()
{
	if (_nPlaneImgNumber == 0) _plane = IMAGEMANAGER->findImage("opPlane_1");
	if (_nPlaneImgNumber == 1) _plane = IMAGEMANAGER->findImage("opPlane_2");
	if (_nPlaneImgNumber == 2) _plane = IMAGEMANAGER->findImage("opPlane_3");
	if (_nPlaneImgNumber == 3) _plane = IMAGEMANAGER->findImage("opPlane_4");
	if (_nPlaneImgNumber > 3) _bShowPlane = false;

	_nPlaneTime++;
	if (_nPlaneTime % 5 == 0)
	{
		_plane->setFrameX(_nPlaneFrame);
		_nPlaneFrame++;
		if (_nPlaneFrame > _plane->getMaxFrameX())
		{
			_nPlaneFrame = 0;
			_nPlaneImgNumber++;
		}
	}
	
	_nPlaneX++;
	_rcPlane = RectMake(_nPlaneX, 0, _plane->getFrameWidth(), _plane->getFrameHeight());
	
	_titleUI->update();
}

void titleScene::render()
{
	_background->render(getMemDC(), _rcBackground.left, _rcBackground.top);
	if(_bShowPlane) _plane->frameRender(getMemDC(), _rcPlane.left, _rcPlane.top, _plane->getFrameX(), _plane->getFrameY());
	_ship->render(getMemDC(), _rcShip.left, _rcShip.top);
	_login->render(getMemDC(), _rcLogin.left, _rcLogin.top);

	_titleUI->render();
}
