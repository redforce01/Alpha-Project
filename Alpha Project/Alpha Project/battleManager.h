#pragma once
#include "gameNode.h"
#include "ship.h"

struct ST_Player
{
	int credit;
	int victoryPoint;
	int capturePoint;
};
class battleManager : public gameNode
{
private:
	vector<ship*> _vPlayerShip;
	vector<ship*>::iterator _viPlayerShip;

	vector<ship*> _vEnemyShip;
	vector<ship*>::iterator _viEnemyShip;

private:
	ST_Player _player;
	ST_Player _computer;

	bool _bFinishBattle;
	
public:
	battleManager();
	~battleManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void functionAddUnit(string unitName, int count, float setupX, float setupY, float targetX, float targetY, UNIT_TYPE unitMaster);
	void functionFinish();

	int getPlayerCredit() { return _player.credit; }
	bool getBattleFinish() { return _bFinishBattle; }
	vector<ship*> getPlayerShips() { return _vPlayerShip; }
	vector<ship*>::iterator getPlayerShipsIter() { return _viPlayerShip; }

	vector<ship*> getEnemyShips() { return _vEnemyShip; }
	vector<ship*>::iterator getEnemyShipsIter() { return _viEnemyShip; }
};