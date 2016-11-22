#include "stdafx.h"
#include "battleUI.h"
#include "battleMap.h"
#include "battleManager.h"

battleUI::battleUI()
{
}


battleUI::~battleUI()
{
}

HRESULT battleUI::init()
{
	//IMAGEMANAGER->addImage("component_BB_Alaska", "image/component/component_BB_Alaska.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_BB_Guam", "image/component/component_BB_Guam.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_BB_Iowa", "image/component/component_BB_Iowa.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_BB_Nevada", "image/component/component_BB_Nevada.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_BB_NewMexico(1930)", "image/component/component_BB_NewMexico(1930).bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_BB_Pennsylvania(1930)", "image/component/component_BB_Pennsylvania(1930).bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CL_Atlanta", "image/component/component_CL_Atlanta.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CL_Brooklyn", "image/component/component_CL_Brooklyn.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CL_Cleveland", "image/component/component_CL_Cleveland.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CL_Omaha", "image/component/component_CL_Omaha.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CL_Portland", "image/component/component_CL_Portland.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CV_Bogue", "image/component/component_CV_Bogue.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CV_Essex", "image/component/component_CV_Essex.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CV_Lexington", "image/component/component_CV_Lexington.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CV_Midway", "image/component/component_CV_Midway.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_CV_Yorktown", "image/component/component_CV_Yorktown.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_DD_DDXProject", "image/component/component_DD_DDXProject.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_DD_Fletcher", "image/component/component_DD_Fletcher.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	//IMAGEMANAGER->addImage("component_DD_Somers", "image/component/component_DD_Somers.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));


	_scoreScreen = IMAGEMANAGER->findImage("battle_ScoreScreen");
	
	_selectUnitCard = false;
	_selectUnitCardNum = 0;
	_selectUnitName = "";

	_selectUnit = false;
	_selectUnitNum = 0;
	_orderMoveType = SHIP_ORDER_MOVEMENT_NULL;
	_isSelectEnemy = false;
	_isZoom = FALSE;

	_teamPoint = 0;
	_timeMM = 0;
	_timeSS = 0;
	_target = 0;
	_creadit = 0;
	_missionLevel = 0;

	_cameraX = _cameraY = 0;
	_sltMinimapX = _sltMinimapY = 0;

	_listFrigate	= new unitList;
	_listDestroyer	= new unitList;
	_listCruiser	= new unitList;
	_listCarrier	= new unitList;
	_listBattle		= new unitList;

	_listFrigate	->init(FF);
	_listDestroyer	->init(DD);
	_listCruiser	->init(CL);
	_listCarrier	->init(CV);
	_listBattle		->init(BB);

	_callShipUI = new callShipUI;
	_callShipUI->init();

	_mouseOverShip = new mouseOverShip;
	_mouseOverShip->init();

	_selectShipInfo = new selectShipInfo;
	_selectShipInfo->init();

	_minimap = new minimap;
	_minimap->init();
	_minimap->setMapSize(_battleMap->getMapSizeX(), _battleMap->getMapSizeY());

	_battleBottomExtend = new battleBottomExtend;
	_battleBottomExtend->init();

	for (int i = 0; i < MOVETOUI_SIZE; i++)
	{
		_vMoveToUI[i].init();
	}

	return S_OK;
}

void battleUI::release()
{
	_callShipUI->release();
	_mouseOverShip->release();
	_selectShipInfo->release();
	_minimap->release();
	_battleBottomExtend->release();

	SAFE_DELETE(_callShipUI);
	SAFE_DELETE(_mouseOverShip);
	SAFE_DELETE(_selectShipInfo);
	SAFE_DELETE(_minimap);
	SAFE_DELETE(_battleBottomExtend);

	for (int i = 0; i < MOVETOUI_SIZE; i++)
	{
		_vMoveToUI[i].release();
	}
}

void battleUI::update()
{
	_callShipUI->update();	//CALL SHIP UI 
	if (_selectUnitCard) _mouseOverShip->update();

	for (_viCreateUnit = _vCreateUnit.begin(); _viCreateUnit != _vCreateUnit.end(); ++_viCreateUnit)
	{
		(*_viCreateUnit)->update();
	}

	

	functionMouseLBT();		//MOUSE LEFT BUTTON DOWN EVENT
	functionMouseRBT();		//MOUSE RIGHT BUTTON DOWN EVENT
	functionMoveCamera();	//CAMERA MOVE EVENT

	updateAddUnit();		//CHECK CREATE UNIT DONE
	updateSetMoveTo();
	updateZoomCheck();

	//updateSelectUnitInfo();	//사용하지 않음	

	_minimap->setCamera(_cameraX, _cameraY);
	_minimap->update();
	_battleBottomExtend->update();

	//임시 종료 Event
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostQuitMessage(0);
}

void battleUI::render()
{
	_scoreScreen->render(getMemDC(), WINSIZEX - _scoreScreen->getWidth(), 20);

	_callShipUI->render();

	for (_viCreateUnit = _vCreateUnit.begin(); _viCreateUnit != _vCreateUnit.end(); ++_viCreateUnit)
	{
		(*_viCreateUnit)->render();
	}

	for (int i = 0; i < MOVETOUI_SIZE; i++)
	{
		if (_vMoveToUI[i].getShow())
			_vMoveToUI[i].render();
	}

	if (_selectUnitCard) _mouseOverShip->render();
	if (_selectUnit)
	{
		//_selectShipInfo->render();	//사용하지 않음 
	}
	

	if (_callShipUI->getFlagFrigate()) _listFrigate->render();
	if (_callShipUI->getFlagDestroyer()) _listDestroyer->render();
	if (_callShipUI->getFlagCruiser()) _listCruiser->render();
	if (_callShipUI->getFlagCarrier()) _listCarrier->render();
	if (_callShipUI->getFlagBattle()) _listBattle->render();

	_battleBottomExtend->render();
	_minimap->render();

#ifdef _DEBUG
	char str[128];
	sprintf_s(str, "cameraXY : %d, %d", _cameraX, _cameraY);
	LOGCAT->addLog("cameraXY", str);
	sprintf_s(str, "sltMapXY : %d, %d", _sltMinimapX, _sltMinimapY);
	LOGCAT->addLog("sltMapXY", str);
	
#endif // DEBUG
}

void battleUI::functionMouseLBT()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_selectUnitCard) functionDeployUnit();
		else functionCheckCard();
		
		if (! _isZoom)
		{
			updateSelectPlayerUnit();
			updateSelectEnemyUnit();
		}

		updateClickMinimap();
	}
}

void battleUI::functionMouseRBT()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_selectUnit && !_isSelectEnemy)
		{
			_battleMgr->getPlayerShips()[_selectUnitNum]->orderMovement(SHIP_ORDER_MOVEMENT_SLOW, _ptMouse.x, _ptMouse.y);

			for (int i = 0; i < MOVETOUI_SIZE; i++)
			{
				if (FALSE == _vMoveToUI[i].getShow())
				{
					_vMoveToUI[i].setShow(TRUE);
					_vMoveToUI[i].setMoveToPos(_ptMouse.x, _ptMouse.y);
					break;
				}
			}
		}
	}
}

void battleUI::functionMoveCamera()
{
	//CAMERA가 움직이면 맞춰서 좌표 보정 해야 하는 항목들
	//1. 타일 맵
	//2. 모든 배 좌표 및 타겟 좌표
	//3. 모든 포탄 및 어뢰 좌표
	//4. 모든 항공기 좌표
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown('A'))
	{
		if (_cameraX > 0)
		{
			_battleMap->functionMoveLeft(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
				_battleMgr->getPlayerShips()[i]->functionCameraLeft(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
				_battleMgr->getEnemyShips()[i]->functionCameraLeft(CAMERA_SPEED);
			for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
				_vCreateUnit[i]->functionCameraLeft(CAMERA_SPEED);
			for (int i = 0; i < MOVETOUI_SIZE; i++)
				_vMoveToUI[i].functionCameraLeft(CAMERA_SPEED);

			_cameraX -= CAMERA_SPEED;
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown('D'))
	{
		if (_cameraX < (TILE_WIDTH / 2) * mapX - WINSIZEX - TILE_WIDTH)
		{
			_battleMap->functionMoveRight(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
				_battleMgr->getPlayerShips()[i]->functionCameraRight(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
				_battleMgr->getEnemyShips()[i]->functionCameraRight(CAMERA_SPEED);
			for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
				_vCreateUnit[i]->functionCameraRight(CAMERA_SPEED);
			for (int i = 0; i < MOVETOUI_SIZE; i++)
				_vMoveToUI[i].functionCameraRight(CAMERA_SPEED);

			_cameraX += CAMERA_SPEED;
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown('W'))
	{
		if (_cameraY > 0)
		{
			_battleMap->functionMoveUp(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
				_battleMgr->getPlayerShips()[i]->functionCameraUp(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
				_battleMgr->getEnemyShips()[i]->functionCameraUp(CAMERA_SPEED);
			for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
				_vCreateUnit[i]->functionCameraUp(CAMERA_SPEED);
			for (int i = 0; i < MOVETOUI_SIZE; i++)
				_vMoveToUI[i].functionCameraUp(CAMERA_SPEED);

			_cameraY -= CAMERA_SPEED;
		}

	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown('S'))
	{
		if (_cameraY < (TILE_HEIGHT / 2) * mapY - WINSIZEY - TILE_HEIGHT)
		{
			_battleMap->functionMoveDown(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
				_battleMgr->getPlayerShips()[i]->functionCameraDown(CAMERA_SPEED);
			for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
				_battleMgr->getEnemyShips()[i]->functionCameraDown(CAMERA_SPEED);
			for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
				_vCreateUnit[i]->functionCameraDown(CAMERA_SPEED);
			for (int i = 0; i < MOVETOUI_SIZE; i++)
				_vMoveToUI[i].functionCameraDown(CAMERA_SPEED);

			_cameraY += CAMERA_SPEED;
		}		
	}
}

void battleUI::functionMoveCamera(int minimapX, int minimapY)
{
	int totalWidth = _battleMap->getMapSizeX();
	int totalHeight = _battleMap->getMapSizeY();

	int targetCameraX = totalWidth * minimapX / MINIMAP_GRID_X;
	int targetCameraY = totalHeight * minimapY / MINIMAP_GRID_Y;

	int moveValueHri = _cameraX - targetCameraX;
	int moveValueVer = _cameraY - targetCameraY;

	if (moveValueHri > 0) functionMoveLeft(abs(moveValueHri));
	else functionMoveRight(abs(moveValueHri));
	
	if (moveValueVer > 0) functionMoveUp(abs(moveValueVer));
	else functionMoveDown(abs(moveValueVer));

}

void battleUI::functionMoveLeft(int value)
{
	if (_cameraX > 0)
	{
		_battleMap->functionMoveLeft(value);
		for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
			_battleMgr->getPlayerShips()[i]->functionCameraLeft(value);
		for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
			_battleMgr->getEnemyShips()[i]->functionCameraLeft(value);
		for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
			_vCreateUnit[i]->functionCameraLeft(value);
		for (int i = 0; i < MOVETOUI_SIZE; i++)
			_vMoveToUI[i].functionCameraLeft(value);

		_cameraX -= value;
	}
}

void battleUI::functionMoveRight(int value)
{
	if (_cameraX < (TILE_WIDTH / 2) * mapX - WINSIZEX - TILE_WIDTH)
	{
		_battleMap->functionMoveRight(value);
		for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
			_battleMgr->getPlayerShips()[i]->functionCameraRight(value);
		for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
			_battleMgr->getEnemyShips()[i]->functionCameraRight(value);
		for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
			_vCreateUnit[i]->functionCameraRight(value);
		for (int i = 0; i < MOVETOUI_SIZE; i++)
			_vMoveToUI[i].functionCameraRight(value);

		_cameraX += value;
	}
}

void battleUI::functionMoveUp(int value)
{
	if (_cameraY > 0)
	{
		_battleMap->functionMoveUp(value);
		for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
			_battleMgr->getPlayerShips()[i]->functionCameraUp(value);
		for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
			_battleMgr->getEnemyShips()[i]->functionCameraUp(value);
		for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
			_vCreateUnit[i]->functionCameraUp(value);
		for (int i = 0; i < MOVETOUI_SIZE; i++)
			_vMoveToUI[i].functionCameraUp(value);

		_cameraY -= value;
	}
}

void battleUI::functionMoveDown(int value)
{
	if (_cameraY < (TILE_HEIGHT / 2) * mapY - WINSIZEY - TILE_HEIGHT)
	{
		_battleMap->functionMoveDown(value);
		for (unsigned int i = 0; i < _battleMgr->getPlayerShips().size(); i++)
			_battleMgr->getPlayerShips()[i]->functionCameraDown(value);
		for (unsigned int i = 0; i < _battleMgr->getEnemyShips().size(); i++)
			_battleMgr->getEnemyShips()[i]->functionCameraDown(value);
		for (unsigned int i = 0; i < _vCreateUnit.size(); i++)
			_vCreateUnit[i]->functionCameraDown(value);
		for (int i = 0; i < MOVETOUI_SIZE; i++)
			_vMoveToUI[i].functionCameraDown(value);

		_cameraY += value;
	}
}

void battleUI::functionCheckCard()
{
	switch (_callShipUI->getSelectCardType())
	{
	case CARD_FF:
		for (int i = 0; i < _listFrigate->getListSize(); i++)
		{
			if (PtInRect(&_listFrigate->getUnitList()[i].rc, _ptMouse))
			{
				_selectUnitCard = true;
				_selectUnitCardNum = i;
				_mouseOverShip->setUnit(_listFrigate->getUnitList()[i].unitName);
				_selectUnitName = _listFrigate->getUnitList()[i].unitName;
				return;
			}
		}
		break;

	case CARD_DD:
		for (int i = 0; i < _listDestroyer->getListSize(); i++)
		{
			if (PtInRect(&_listDestroyer->getUnitList()[i].rc, _ptMouse))
			{
				_selectUnitCard = true;
				_selectUnitCardNum = i;
				_mouseOverShip->setUnit(_listDestroyer->getUnitList()[i].unitName);
				_selectUnitName = _listDestroyer->getUnitList()[i].unitName;
				return;
			}
		}
		break;

	case CARD_CL:
		for (int i = 0; i < _listCruiser->getListSize(); i++)
		{
			if (PtInRect(&_listCruiser->getUnitList()[i].rc, _ptMouse))
			{
				_selectUnitCard = true;
				_selectUnitCardNum = i;
				_mouseOverShip->setUnit(_listCruiser->getUnitList()[i].unitName);
				_selectUnitName = _listCruiser->getUnitList()[i].unitName;
				return;
			}
		}
		break;

	case CARD_CV:
		for (int i = 0; i < _listCarrier->getListSize(); i++)
		{
			if (PtInRect(&_listCarrier->getUnitList()[i].rc, _ptMouse))
			{
				_selectUnitCard = true;
				_selectUnitCardNum = i;
				_mouseOverShip->setUnit(_listCarrier->getUnitList()[i].unitName);
				_selectUnitName = _listCarrier->getUnitList()[i].unitName;
				return;
			}
		}
		break;

	case CARD_BB:
		for (int i = 0; i < _listBattle->getListSize(); i++)
		{
			if (PtInRect(&_listBattle->getUnitList()[i].rc, _ptMouse))
			{
				_selectUnitCard = true;
				_selectUnitCardNum = i;
				_mouseOverShip->setUnit(_listBattle->getUnitList()[i].unitName);
				_selectUnitName = _listBattle->getUnitList()[i].unitName;
				return;
			}
		}
		break;
	default:
		break;
	}
}

void battleUI::functionDeployUnit()
{
	switch (_callShipUI->getSelectCardType())
	{
	case CARD_FF:
		if (_listFrigate->getUnitList()[_selectUnitCardNum].availability <= 0) return;
		break;
	case CARD_DD:
		if (_listDestroyer->getUnitList()[_selectUnitCardNum].availability <= 0) return;
		break;
	case CARD_CL:
		if (_listCruiser->getUnitList()[_selectUnitCardNum].availability <= 0) return;
		break;
	case CARD_CV:
		if (_listCarrier->getUnitList()[_selectUnitCardNum].availability <= 0) return;
		break;
	case CARD_BB:
		if (_listBattle->getUnitList()[_selectUnitCardNum].availability <= 0) return;
		break;
	}

	createUnit* newUnit = new createUnit;
	newUnit->setUnit(_selectUnitName, _ptMouse.x, _ptMouse.y);
	_vCreateUnit.push_back(newUnit);
	_selectUnitCard = false;
}

void battleUI::decreaceList()
{
	switch (_callShipUI->getSelectCardType())
	{
	case CARD_FF:
		_listFrigate->getUnitList()[_selectUnitCardNum].availability--;
		break;
	case CARD_DD:
		_listDestroyer->getUnitList()[_selectUnitCardNum].availability--;
		break;
	case CARD_CL:
		_listCruiser->getUnitList()[_selectUnitCardNum].availability--;
		break;
	case CARD_CV:
		_listCarrier->getUnitList()[_selectUnitCardNum].availability--;
		break;
	case CARD_BB:
		_listBattle->getUnitList()[_selectUnitCardNum].availability--;
		break;
	}
}

void battleUI::updateAddUnit()
{
	for (_viCreateUnit = _vCreateUnit.begin(); _viCreateUnit != _vCreateUnit.end(); )
	{
		if ((*_viCreateUnit)->getOnUnit())
		{
			_battleMgr->functionAddUnit(
				_selectUnitName, 1,
				_cameraX + CENTERX - CENTERX / 2,
				_cameraY + CENTERY,
				_cameraX + (*_viCreateUnit)->getTargetXY().x,
				_cameraY + (*_viCreateUnit)->getTargetXY().y, UNIT_PLAYER);
			
			_viCreateUnit = _vCreateUnit.erase(_viCreateUnit);
			decreaceList();
		}
		else
		{
			++_viCreateUnit;
		}
	}
}

void battleUI::updateSetMoveTo()
{
	for (int i = 0; i < MOVETOUI_SIZE; i++)
	{
		if (!_vMoveToUI[i].getShow()) continue;

		_vMoveToUI[i].update();
	}
}

void battleUI::updateSelectUnitInfo()
{
	if (_selectUnit && !_isSelectEnemy)
	{
		_selectShipInfo->setGuidePos(
			PointMake(
				_battleMgr->getPlayerShips()[_selectUnitNum]->getShipRect().right - (_battleMgr->getPlayerShips()[_selectUnitNum]->getShipRectWidth() / 3),
				_battleMgr->getPlayerShips()[_selectUnitNum]->getShipRect().top + (_battleMgr->getPlayerShips()[_selectUnitNum]->getShipRectHeight() / 3)));
		
		_selectShipInfo->update();
	}
}

void battleUI::updateClickMinimap()
{

	for (int i = 0; i < MINIMAP_GRID_X; i++)
	{
		for (int j = 0; j < MINIMAP_GRID_Y; j++)
		{			
			if (!PtInRect(&_minimap->getMinimapGrid(i, j), _ptMouse)) continue;

			_sltMinimapX = i;
			_sltMinimapY = j;

			functionMoveCamera(_sltMinimapX, _sltMinimapY);
			break;
		}
	}
	
}

void battleUI::updateZoomCheck()
{
	if (_zoomDeltaX < 0 || _zoomDeltaY < 0)
	{
		_isZoom = TRUE;
	}
	else
	{
		_isZoom = FALSE;
	}
}

void battleUI::updateSelectPlayerUnit()
{
	int i = 0;

	vector<ship*> playerShip = _battleMgr->getPlayerShips();
	vector<ship*>::iterator playerIter = _battleMgr->getPlayerShipsIter();

	for (playerIter = playerShip.begin(); playerIter != playerShip.end(); ++playerIter)
	{
		if (!PtInRect(&(*playerIter)->getShipRect(), _ptMouse))
		{
			(*playerIter)->setSelected(FALSE);
			_selectUnit = false;
			_selectUnitNum = 0;
			i++;
			continue;
		}

		(*playerIter)->setSelected(TRUE);
		_selectUnit = true;
		_selectUnitNum = i;
		_isSelectEnemy = false;
		break;
	}
}

void battleUI::updateSelectEnemyUnit()
{
	int i = 0;
	vector<ship*> enemyShip = _battleMgr->getEnemyShips();
	vector<ship*>::iterator enemyIter = _battleMgr->getEnemyShipsIter();

	for (enemyIter = enemyShip.begin(); enemyIter != enemyShip.end(); ++enemyIter)
	{
		if (!PtInRect(& (*enemyIter)->getShipRect(), _ptMouse))
		{			
			_selectUnit = false;
			_selectUnitNum = 0;
			i++;
			continue;
		}

		_selectUnit = true;
		_selectUnitNum = i;
		_isSelectEnemy = true;
		break;
	}
}