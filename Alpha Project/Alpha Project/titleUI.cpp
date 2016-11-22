#include "stdafx.h"
#include "titleUI.h"


titleUI::titleUI()
{
}


titleUI::~titleUI()
{
}

HRESULT titleUI::init()
{
	_btnJoin = new button;
	_btnJoin->init("joinButton", CENTERX - 20, WINSIZEY - 100, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionJoin, this);
	_btnCancel = new button;
	_btnCancel->init("cancelButton", CENTERX + 50, WINSIZEY - 100, PointMake(2, 0), PointMake(0, 0), PointMake(1, 0), functionCancel, this);
	

	return S_OK;
}

void titleUI::release()
{

	_btnJoin->release();
	_btnCancel->release();
	SAFE_DELETE(_btnJoin);
	SAFE_DELETE(_btnCancel);
}

void titleUI::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostMessage(_hWnd, WM_DESTROY, 0, 0);	
	
	_btnCancel->update();
	_btnJoin->update();
}

void titleUI::render()
{
	string str = "Dev by. Kim JaeJun. redforce01@naver.com";
	TextOut(getMemDC(), 460, 450, str.c_str(), strlen(str.c_str()));
	str = "Thanks for Playing";
	TextOut(getMemDC(), 460, 470, str.c_str(), strlen(str.c_str()));
	str = "All Resource used From Original NavyField 1";
	TextOut(getMemDC(), 460, 490, str.c_str(), strlen(str.c_str()));

	_btnJoin->render();
	_btnCancel->render();
}

void titleUI::functionJoin(void * obj)
{
	SCENEMANAGER->changeScene("lobbyScene");
}

void titleUI::functionCancel(void * obj)
{
	PostMessage(_hWnd, WM_DESTROY, 0, 0);
}
