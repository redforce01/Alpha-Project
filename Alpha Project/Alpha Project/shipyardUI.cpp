#include "stdafx.h"
#include "shipyardUI.h"


shipyardUI::shipyardUI()
{
}


shipyardUI::~shipyardUI()
{
}

HRESULT shipyardUI::init()
{
	_shipInfoUI = new shipInfoUI;
	_shipInfoUI->init();
	_topExtendUI = new topExtendUI;
	_topExtendUI->init();
	_arrowUI = new arrowUI;
	_arrowUI->init();
	_shipyardCtrlUI = new shipyardCtrlUI;
	_shipyardCtrlUI->init();

	_shipListSize = DATABASE->getShipList().size();
	_vShipList = DATABASE->getShipList();
	_showShipNumber = 0;

	_harborShip = new harborShip;
	_harborShip->init();

	return S_OK;
}

void shipyardUI::release()
{
	_shipInfoUI->release();
	_topExtendUI->release();
	_shipyardCtrlUI->release();
	_arrowUI->release();
	_harborShip->relaese();

	SAFE_DELETE(_shipInfoUI);
	SAFE_DELETE(_topExtendUI);
	SAFE_DELETE(_shipyardCtrlUI);
	SAFE_DELETE(_arrowUI);
	SAFE_DELETE(_harborShip);
}

void shipyardUI::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeScene("lobbyScene");
		return;
	}	

	_shipInfoUI->setShowShipName(_vShipList[_showShipNumber]);
	_harborShip->setShipName(_vShipList[_showShipNumber]);

	_shipInfoUI->update();
	_topExtendUI->update();
	_shipyardCtrlUI->update();
	_arrowUI->update();
		
	_shipInfoUI->setHasShip(true);
	_harborShip->setHasShip(true);
	_harborShip->update();


	if (_arrowUI->_bClickedLeft)
	{
		_arrowUI->_bClickedLeft = false;		
		if (_showShipNumber > 0)
		{
			_showShipNumber--;
			_harborShip->_bChanged = true;
			_harborShip->_alphaValue = 0;
		}
	}

	if (_arrowUI->_bClickedRight)
	{
		_arrowUI->_bClickedRight = false;
		if (_showShipNumber < _shipListSize)
		{
			_showShipNumber++;
			_harborShip->_bChanged = true;
			_harborShip->_alphaValue = 0;
		}
	}

	if (_arrowUI->_bClickedLaunch)
	{
		_arrowUI->_bClickedLaunch = false;
		SCENEMANAGER->changeScene("worldMapScene");
	}
}

void shipyardUI::render()
{
	_shipInfoUI->render();
	_topExtendUI->render();
	_shipyardCtrlUI->render();
	_harborShip->render();
	_arrowUI->render();

}
