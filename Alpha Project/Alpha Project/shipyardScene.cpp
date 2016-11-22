#include "stdafx.h"
#include "shipyardScene.h"


shipyardScene::shipyardScene()
{
}


shipyardScene::~shipyardScene()
{
}

HRESULT shipyardScene::init()
{
	_background = IMAGEMANAGER->findImage("shipyardBackground");
	

	_shipyardUI = new shipyardUI;
	_shipyardUI->init();

	return S_OK;
}

void shipyardScene::release()
{
	_shipyardUI->release();
	SAFE_DELETE(_shipyardUI);
}

void shipyardScene::update()
{

	_shipyardUI->update();
}

void shipyardScene::render()
{
	_background->render(getMemDC(), 0, 0, 200, 200, 1280, 720);


	_shipyardUI->render();
}
