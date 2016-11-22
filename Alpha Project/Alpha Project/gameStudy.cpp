#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);

	SCENEMANAGER->addScene("TestScene", new TestScene);
	
	SCENEMANAGER->addScene("titleScene", new titleScene);
	SCENEMANAGER->addScene("lobbyScene", new LobbyScene);
	SCENEMANAGER->addScene("shipyardScene", new shipyardScene);	
	SCENEMANAGER->addScene("worldMapScene", new worldMapScene);
	SCENEMANAGER->addScene("battleScene", new battleScene);

	//SCENEMANAGER->addLoadingScene("startLoading", new startLoading);
	SCENEMANAGER->addScene("startLoading", new startLoading);

	//SCENEMANAGER->changeScene("titleScene", "startLoading");
	SCENEMANAGER->changeScene("startLoading");
		
	_mouseCursor = new mouseCursor;
	_mouseCursor->init();

	return S_OK;
}

void gameStudy::release()
{
	_mouseCursor->release();
	SAFE_DELETE(_mouseCursor);

	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();
	_mouseCursor->update();

	gameNode::update();
}

void gameStudy::render()
{
	//백버퍼에서 뿌려준다	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	StretchBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY,
		getBattleDC(), 0, 0, WINSIZEX + _zoomDeltaX, WINSIZEY + _zoomDeltaY, SRCCOPY);
	//======================
	SCENEMANAGER->render();
	_mouseCursor->render();

	LOGCAT->render(getMemDC());

#ifdef _DEBUG
	int _cameraX = 0;
	int _cameraY = 0;
	char str[128];
	//마우스 X,Y 출력
	sprintf_s(str, "mouse : %d, %d", _ptMouse.x, _ptMouse.y);
	LOGCAT->addLog("mousePos", str);
	sprintf_s(str, "zoomXY : %d, %d", _zoomDeltaX, _zoomDeltaY);
	LOGCAT->addLog("mousePos", str);
#endif // DEBUG
	
	//======================
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0, 0, 0, WINSIZEX, WINSIZEY);
}


