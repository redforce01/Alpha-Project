#include "stdafx.h"
#include "lobbyUI.h"


lobbyUI::lobbyUI()
{
}


lobbyUI::~lobbyUI()
{
}

HRESULT lobbyUI::init()
{
	IMAGEMANAGER->findImage("shipYardButton");

	_btnShipYard = new button;
	_btnBattle	 = new button;
	_btnMaptool	 = new button;
	_btnOption	 = new button;
	_btnCredit	 = new button;
	_btnExit	 = new button;

	_btnShipYard ->init("shipYardButton", 600, 300, PointMake(1, 0), PointMake(0, 0), PointMake(1, 0), functionShipYard, this);

	_btnBattle	 ->init("Battle", 1100, 470, functionBattle, this);
	_btnMaptool	 ->init("Maptool", 1100, 500, functionMaptool, this);
	_btnOption	 ->init("Option", 1100, 530, functionOption, this);
	_btnCredit	 ->init("Credit", 1100, 560, functionCredit, this);
	_btnExit	 ->init("Exit", 1100, 590, functionExit, this);

	_bChangeScene = false;

	return S_OK;
}

void lobbyUI::release()
{
	_btnShipYard ->release();
	_btnBattle	 ->release();
	_btnMaptool	 ->release();
	_btnOption	 ->release();
	_btnCredit	 ->release();
	_btnExit	 ->release();

	SAFE_DELETE(_btnShipYard);
	SAFE_DELETE(_btnBattle);
	SAFE_DELETE(_btnMaptool);
	SAFE_DELETE(_btnOption);
	SAFE_DELETE(_btnCredit);
	SAFE_DELETE(_btnExit);
}

void lobbyUI::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostQuitMessage(0);


	if(! _bChangeScene) _btnShipYard ->update();
	if(! _bChangeScene) _btnBattle	 ->update();
	if(! _bChangeScene) _btnMaptool	 ->update();
	if(! _bChangeScene) _btnCredit	 ->update();
	if(! _bChangeScene) _btnOption	 ->update();
	if(! _bChangeScene) _btnExit	 ->update();
}

void lobbyUI::render()
{


	_btnShipYard ->render();
	_btnBattle	 ->render();
	_btnMaptool	 ->render();
	_btnCredit	 ->render();
	_btnOption	 ->render();
	_btnExit	 ->render();
}

void lobbyUI::functionShipYard(void * obj)
{
	lobbyUI* _lobbyUI = (lobbyUI*)obj;
	SCENEMANAGER->changeScene("shipyardScene");
	_lobbyUI->_bChangeScene = true;
}

void lobbyUI::functionBattle(void * obj)
{
	lobbyUI* _lobbyUI = (lobbyUI*)obj;
	SCENEMANAGER->changeScene("worldMapScene");
	_lobbyUI->_bChangeScene = true;
}

void lobbyUI::functionMaptool(void * obj)
{
	lobbyUI* _lobbyUI = (lobbyUI*)obj;
	SCENEMANAGER->changeScene("maptoolScene");
	_lobbyUI->_bChangeScene = true;
}

void lobbyUI::functionOption(void * obj)
{
}

void lobbyUI::functionCredit(void * obj)
{
}

void lobbyUI::functionExit(void * obj)
{
	PostQuitMessage(0);
}


