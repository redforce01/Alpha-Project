#include "stdafx.h"
#include "worldMapUI.h"
#include "IsoMetricWorld.h"
#include "eventManager.h"

worldMapUI::worldMapUI()
{
}


worldMapUI::~worldMapUI()
{
}

HRESULT worldMapUI::init()
{
	_worldMap = IMAGEMANAGER->findImage("worldMap");

	_btnArrowLeftDown = new button;
	_btnArrowLeftUp = new button;
	_btnArrowRightDown = new button;
	_btnArrowRightUp = new button;

	_btnArrowLeftDown->init("btnArrowLeftUpN", "btnArrowLeftUpO", "btnArrowLeftUpP", CENTERX - 220, CENTERY - 90, functionLeftUp, this);
	_btnArrowLeftUp->init("btnArrowLeftDownN", "btnArrowLeftDownO", "btnArrowLeftDownP", CENTERX - 200, CENTERY + 140, functionLeftDown, this);
	_btnArrowRightDown->init("btnArrowRightUpN", "btnArrowRightUpO", "btnArrowRightUpP", CENTERX + 230, CENTERY - 100, functionRightUp, this);
	_btnArrowRightUp->init("btnArrowRightDownN", "btnArrowRightDownO", "btnArrowRightDownP", CENTERX + 280, CENTERY + 130, functionRightDown, this);

	_cameraX = 1300;
	_cameraY = 0;
	_showAreaNumber = 0;

	_topExtendUI = new topExtendUI;
	_topExtendUI->init();

	return S_OK;
}

void worldMapUI::release()
{
	_btnArrowLeftDown->release();
	_btnArrowLeftUp->release();
	_btnArrowRightDown->release();
	_btnArrowRightUp->release();

	_topExtendUI->release();
	SAFE_DELETE(_topExtendUI);
}

void worldMapUI::update()
{
	if (_showAreaNumber / 5 != 4)	_btnArrowRightUp->update();
	if (_showAreaNumber / 5 != 0)	_btnArrowLeftDown->update();
	if (_showAreaNumber % 5 != 0)	_btnArrowRightDown->update();
	if (_showAreaNumber % 5 != 4)	_btnArrowLeftUp->update();

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeScene("lobbyScene");
		_cameraX = _cameraY = 0;
		return;
	}


	//if (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown(VK_UP)) _cameraY		-= CAMERA_SPEED;
	//if (KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown(VK_DOWN)) _cameraY		+= CAMERA_SPEED;
	//if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown(VK_LEFT)) _cameraX		-= CAMERA_SPEED;
	//if (KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown(VK_RIGHT)) _cameraX		+= CAMERA_SPEED;

	if (_cameraX <= 0) _cameraX = 0;
	if (_cameraX >= _worldMap->getWidth() - WINSIZEX) _cameraX = _worldMap->getWidth() - WINSIZEX;
	if (_cameraY <= 0) _cameraY = 0;
	if (_cameraY >= _worldMap->getHeight() - WINSIZEY) _cameraY = _worldMap->getHeight() - WINSIZEY;
	
	if (_cameraX < _isoMetricWorld->getAreaX((_showAreaNumber / 5), (_showAreaNumber % 5))) _cameraX += 10;
	if (_cameraX > _isoMetricWorld->getAreaX((_showAreaNumber / 5), (_showAreaNumber % 5))) _cameraX -= 10;
	if (_cameraY < _isoMetricWorld->getAreaY((_showAreaNumber / 5), (_showAreaNumber % 5))) _cameraY += 10;
	if (_cameraY > _isoMetricWorld->getAreaY((_showAreaNumber / 5), (_showAreaNumber % 5))) _cameraY -= 10;
		
	_topExtendUI->update();

	functionLButtonClick();
}

void worldMapUI::render()
{
	_worldMap->render(getMemDC(), 0, 0, _cameraX, _cameraY, WINSIZEX, WINSIZEY);

	if (_showAreaNumber / 5 != 4)	_btnArrowRightUp->render();
	if (_showAreaNumber / 5 != 0)	_btnArrowLeftDown->render();
	if (_showAreaNumber % 5 != 0)	_btnArrowRightDown->render();
	if (_showAreaNumber % 5 != 4)	_btnArrowLeftUp->render();

	_topExtendUI->render();

#ifdef _DEBUG
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	char str[128];
	//카메라 X,Y 출력
	sprintf_s(str, "WorldMap Camera : %d, %d", _cameraX, _cameraY);
	TextOut(getMemDC(), CENTERX, 90, str, strlen(str));

	sprintf_s(str, "Show Area Number : %d", _showAreaNumber);
	TextOut(getMemDC(), CENTERX, 110, str, strlen(str));

	SetTextColor(getMemDC(), RGB(255, 255, 255));
#endif // DEBUG
	
}

void worldMapUI::functionLButtonClick()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{		
		int vSize = _eventManager->getvEvent().size();
		for (int i = 0; i < vSize; i++)
		{
			if (PtInRect(&_eventManager->getvEvent()[i]->getEventRect(), _ptMouse))
			{
				SCENEMANAGER->changeScene("battleScene");
			}
			
		}
	}
	
}

void worldMapUI::functionLeftUp(void * obj)
{
	worldMapUI* _worldMapUI = (worldMapUI*)obj;
	_worldMapUI->_showAreaNumber -= 5;
}

void worldMapUI::functionLeftDown(void * obj)
{
	worldMapUI* _worldMapUI = (worldMapUI*)obj;
	_worldMapUI->_showAreaNumber += 1;
}

void worldMapUI::functionRightUp(void * obj)
{
	worldMapUI* _worldMapUI = (worldMapUI*)obj;
	_worldMapUI->_showAreaNumber -= 1;
}

void worldMapUI::functionRightDown(void * obj)
{
	worldMapUI* _worldMapUI = (worldMapUI*)obj;
	_worldMapUI->_showAreaNumber += 5;
}
