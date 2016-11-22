#include "stdafx.h"
#include "LobbyScene.h"


LobbyScene::LobbyScene()
{
}


LobbyScene::~LobbyScene()
{
}

HRESULT LobbyScene::init()
{
	_background = IMAGEMANAGER->findImage("lobbyBackground");

	_lobbyUI = new lobbyUI;
	_lobbyUI->init();

	return S_OK;
}

void LobbyScene::release()
{
	_lobbyUI->release();
	SAFE_DELETE(_lobbyUI);
}

void LobbyScene::update()
{
	_lobbyUI->update();
}

void LobbyScene::render()
{
	_background->render(getMemDC(), 0, 0);

	_lobbyUI->render();
}
