#pragma once
#include "gameNode.h"
#include "button.h"
#include "unitList.h"
#include "callShipUI.h"
#include "mouseOverShip.h"
#include "createUnit.h"
#include "selectShipInfo.h"
#include "moveToUI.h"
#include "minimap.h"
#include "battleBottomExtend.h"
#include "ship.h"


#define MOVETOUI_SIZE 100

class battleMap;
class battleManager;
class battleUI : public gameNode
{
private:
	image* _scoreScreen;
	
	int _teamPoint;
	int _timeMM;
	int _timeSS;
	int _target;
	int _creadit;
	int _missionLevel;

	int _cameraX, _cameraY;
	int _sltMinimapX, _sltMinimapY;
	
	bool _selectUnitCard;
	int _selectUnitCardNum;
	string _selectUnitName;

	bool _selectUnit;
	int _selectUnitNum;
	SHIP_ORDER_MOVEMENT_STATE _orderMoveType;
	bool _isSelectEnemy;
	bool _isZoom;

private:
	callShipUI* _callShipUI;
	mouseOverShip* _mouseOverShip;
	selectShipInfo* _selectShipInfo;
	minimap* _minimap;
	battleBottomExtend* _battleBottomExtend;

private:
	vector<createUnit*> _vCreateUnit;
	vector<createUnit*>::iterator _viCreateUnit;

	moveToUI _vMoveToUI[MOVETOUI_SIZE];

	vector<moveToUI*> _vMoveTo;
	vector<moveToUI*>::iterator _viMoveTo;

	unitList* _listFrigate;
	unitList* _listDestroyer;
	unitList* _listCruiser;
	unitList* _listCarrier;
	unitList* _listBattle;

	battleMap* _battleMap;
	battleManager* _battleMgr;
public:
	battleUI();
	~battleUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void functionMouseLBT();
	void functionMouseRBT();
	void functionCheckCard();
	void functionDeployUnit();

	void functionMoveCamera();
	void functionMoveCamera(int minimapX, int minimapY);


	void functionMoveLeft(int value);
	void functionMoveRight(int value);
	void functionMoveUp(int value);
	void functionMoveDown(int value);


	int getCameraX() { return _cameraX; }
	int getCameraY() { return _cameraY; }

public:
	void decreaceList();

public:
	void updateAddUnit();
	void updateSetMoveTo();
	void updateSelectUnitInfo();
	void updateClickMinimap();
	void updateZoomCheck();

	void updateSelectPlayerUnit();
	void updateSelectEnemyUnit();

	void setMemoryLinkBattleMap(battleMap* battleMap) { _battleMap = battleMap; }
	void setMemoryLinkBattleMgr(battleManager* battleMgr) { _battleMgr = battleMgr; }
};

 