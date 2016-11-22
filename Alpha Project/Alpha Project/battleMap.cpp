#include "stdafx.h"
#include "battleMap.h"


battleMap::battleMap()
{
}


battleMap::~battleMap()
{
}

HRESULT battleMap::init()
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j] = new mapTile;
			_map[i][j]->_tile = IMAGEMANAGER->findImage("battle_tile_1");

			if (j == 0) {
				_map[i][j]->_x = (i * TILE_WIDTH) - TILE_WIDTH;
				_map[i][j]->_y = (j * 64) - TILE_HEIGHT;
			}
			else if (j % 2 == 1) {
				_map[i][j]->_x = (i * TILE_WIDTH) + (TILE_WIDTH / 2) - TILE_WIDTH;
				_map[i][j]->_y = (j * 64) - (TILE_HEIGHT / 2) * j - TILE_HEIGHT;
			}
			else {
				_map[i][j]->_x = (i * TILE_WIDTH) - TILE_WIDTH;
				_map[i][j]->_y = (j * 64) - (TILE_HEIGHT / 2) * j - TILE_HEIGHT;
			}

			_map[i][j]->_rcTile = RectMake(_map[i][j]->_x, _map[i][j]->_y, TILE_WIDTH, TILE_HEIGHT);
			_map[i][j]->_type = BATTLE_TILE_NULL;
		}
	}
	
	battleArea* newArea = new battleArea;
	newArea->init();
	newArea->InitArea(25728 * (2 / 6), 6464 * (1 / 4), 1);	//AREA 1
	_vArea.push_back(newArea);
	newArea->InitArea(25728 * (4 / 6), 6464 * (1 / 4), 2);	//AREA 2
	_vArea.push_back(newArea);
	newArea->InitArea(25728 * (1 / 6), 6464 * (2 / 4), 3);	//AREA 3
	_vArea.push_back(newArea);
	newArea->InitArea(25728 * (3 / 6), 6464 * (2 / 4), 4);	//AREA 4
	_vArea.push_back(newArea);
	newArea->InitArea(25728 * (5 / 6), 6464 * (2 / 4), 5);	//AREA 5
	_vArea.push_back(newArea);
	newArea->InitArea(25728 * (2 / 6), 6464 * (3 / 4), 6);	//AREA 6
	_vArea.push_back(newArea);
	newArea->InitArea(25728 * (4 / 6), 6464 * (3 / 4), 7);	//AREA 7
	_vArea.push_back(newArea);

	return S_OK;
}

void battleMap::release()
{	
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j]->release();
			SAFE_DELETE(_map[i][j]);
		}
	}
}

void battleMap::update()
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j]->_rcTile = RectMake(_map[i][j]->_x, _map[i][j]->_y, 128, 64);
		}
	}


	for (_viArea = _vArea.begin(); _viArea != _vArea.begin(); ++_viArea)
	{
		(*_viArea)->update();
	}

}

void battleMap::render()
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			if (! getOnWindowScreen(&_map[i][j]->_rcTile)) continue;

			//Rectangle(getMemDC(), _map[i][j]->rcTile.left, _map[i][j]->rcTile.top, _map[i][j]->rcTile.right, _map[i][j]->rcTile.bottom);
			//IsoRender(getMemDC(), _map[i][j]->_rcTile);
			_map[i][j]->_tile->render(getBattleDC(), _map[i][j]->_rcTile.left, _map[i][j]->_rcTile.top);
		}
	}	

	for (_viArea = _vArea.begin(); _viArea != _vArea.begin(); ++_viArea)
	{
		(*_viArea)->render();
	}

#ifdef DEBUG
	char str[128];
	sprintf_s(str, "mapSize W : %d, H : %d", (mapX * TILE_WIDTH) + TILE_WIDTH, (mapY * 64) - (TILE_HEIGHT / 2) * mapY + TILE_HEIGHT);
	LOGCAT->addLog("mapSize", str);
	//TextOut(getMemDC(), WINSIZEX - 280, 100, str, strlen(str));
#endif // DEBUG

}

void battleMap::functionMoveCamera(float moveX, float moveY, CAMERA_DIRECTION direction)
{
	_direction = direction;
	switch (_direction)
	{
	case CAMERA_DIRECTION_L:
		functionMoveLeft(moveX);
		break;
	case CAMERA_DIRECTION_R:
		functionMoveRight(moveX);
		break;
	case CAMERA_DIRECTION_T:
		functionMoveUp(moveY);
		break;
	case CAMERA_DIRECTION_B:
		functionMoveDown(moveY);
		break;
	case CAMERA_DIRECTION_LT:
		functionMoveLeft(moveX);
		functionMoveUp(moveY);
		break;
	case CAMERA_DIRECTION_RT:
		functionMoveRight(moveX);
		functionMoveUp(moveY);
		break;
	case CAMERA_DIRECTION_LB:
		functionMoveLeft(moveX);
		functionMoveDown(moveY);
		break;
	case CAMERA_DIRECTION_RB:
		functionMoveRight(moveX);
		functionMoveDown(moveY);
		break;
	default:
		break;
	}

}

void battleMap::functionMoveLeft(int cameraSpeed)
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j]->_x += cameraSpeed;
		}
	}

	for (_viArea = _vArea.begin(); _viArea != _vArea.begin(); ++_viArea)
	{
		(*_viArea)->functionMoveLeft(cameraSpeed);
	}
}

void battleMap::functionMoveRight(int cameraSpeed)
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j]->_x -= cameraSpeed;
		}
	}

	for (_viArea = _vArea.begin(); _viArea != _vArea.begin(); ++_viArea)
	{
		(*_viArea)->functionMoveRight(cameraSpeed);
	}
}

void battleMap::functionMoveUp(int cameraSpeed)
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j]->_y += cameraSpeed;
		}
	}

	for (_viArea = _vArea.begin(); _viArea != _vArea.begin(); ++_viArea)
	{
		(*_viArea)->functionMoveUp(cameraSpeed);
	}
}

void battleMap::functionMoveDown(int cameraSpeed)
{
	for (int i = 0; i < mapX; i++)
	{
		for (int j = 0; j < mapY; j++)
		{
			_map[i][j]->_y -= cameraSpeed;
		}
	}

	for (_viArea = _vArea.begin(); _viArea != _vArea.begin(); ++_viArea)
	{
		(*_viArea)->functionMoveDown(cameraSpeed);
	}
}
