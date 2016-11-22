#include "stdafx.h"
#include "battleManager.h"


battleManager::battleManager()
{
}


battleManager::~battleManager()
{
}

HRESULT battleManager::init()
{
	_player.capturePoint = 0;
	_player.credit = 0;
	_player.victoryPoint = 500;

	_computer.capturePoint = 0;
	_computer.credit = 0;
	_computer.victoryPoint = 500;


	_bFinishBattle = false;

	return S_OK;
}

void battleManager::release()
{
}

void battleManager::update()
{
	if (_bFinishBattle) SCENEMANAGER->changeScene("battleResult");
	if (_player.victoryPoint < 0 || _computer.victoryPoint < 0)
	{
		_bFinishBattle = true;
		functionFinish();
		return;
	}
	
	for (_viPlayerShip = _vPlayerShip.begin(); _viPlayerShip != _vPlayerShip.end(); ++_viPlayerShip) (*_viPlayerShip)->update();
	for (_viEnemyShip = _vEnemyShip.begin(); _viEnemyShip != _vEnemyShip.end(); ++_viEnemyShip) (*_viEnemyShip)->update();

	//for (unsigned int i = 0; i < _vPlayerShip.size(); i++) _vPlayerShip[i]->update();
	//for (unsigned int i = 0; i < _vEnemyShip.size(); i++) _vEnemyShip[i]->update();
}

void battleManager::render()
{
	for (_viPlayerShip = _vPlayerShip.begin(); _viPlayerShip != _vPlayerShip.end(); ++_viPlayerShip)
	{
		if (!getOnWindowScreen(&(*_viPlayerShip)->getShipRect())) continue;
		(*_viPlayerShip)->render();
	}
	for (_viEnemyShip = _vEnemyShip.begin(); _viEnemyShip != _vEnemyShip.end(); ++_viEnemyShip)
	{
		if (!getOnWindowScreen(&(*_viEnemyShip)->getShipRect())) continue;
		(*_viEnemyShip)->render();
	}

	//for (unsigned int i = 0; i < _vPlayerShip.size(); i++) _vPlayerShip[i]->render();
	//for (unsigned int i = 0; i < _vEnemyShip.size(); i++) _vEnemyShip[i]->render();
}

void battleManager::functionAddUnit(string unitName, int count, float setupX, float setupY, float targetX, float targetY, UNIT_TYPE unitMaster)
{
	if (unitMaster == UNIT_PLAYER)
	{
		for (int i = 0; i < count; i++)
		{
			ship* newShip = new ship;
			newShip->init();
			newShip->initForInformation(unitName);
			newShip->initForField(unitName);
			newShip->setUpField(setupX, setupY);
			newShip->setUpTarget(targetX, targetY);

			_vPlayerShip.push_back(newShip);
		}
	}

	if (unitMaster == UNIT_ENEMY)
	{
		for (int i = 0; i < count; i++)
		{
			ship* newShip = new ship;
			newShip->init();
			newShip->initForInformation(unitName);
			newShip->initForField(unitName);
			newShip->setUpField(setupX, setupY);
			newShip->setUpTarget(targetX, targetY);

			_vEnemyShip.push_back(newShip);
		}
	}
}

void battleManager::functionFinish()
{
	
}
