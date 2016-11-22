#include "stdafx.h"
#include "minimap.h"


minimap::minimap()
{
}


minimap::~minimap()
{
}

HRESULT minimap::init()
{
	_minimap = IMAGEMANAGER->findImage("battle_minimap");
	_minimapFrame = IMAGEMANAGER->findImage("battle_minimap_frame");
	_minimapShadow = IMAGEMANAGER->findImage("battle_minimap_shadow");
	_minimapGrid = IMAGEMANAGER->findImage("battle_minimap_grid");
	_minimapGridShadow = IMAGEMANAGER->findImage("battle_minimap_grid_shadow");

	_rcMinimap = RectMake(WINSIZEX - _minimap->getFrameWidth(), WINSIZEY - _minimap->getFrameHeight() + 18, _minimap->getFrameWidth(), _minimap->getFrameHeight());

	_isIntro = FALSE;
	_rcCamera = RectMake(0, 0, 0, 0);
	_rcMapGrid = RectMake(WINSIZEX - 210, WINSIZEY - 125, 190, 125);
	_cameraX = _cameraY = 0;
	_mapSizeX = _mapSizeY = 0;	
	
	_frame = 0;
	_frameTime = 0;

	initMinimapGrid();

	return S_OK;
}

void minimap::release()
{
}

void minimap::update()
{
	if (FALSE == _isIntro)
	{
		updateIntro();
		return;
	}
	
	
	//_rcCamera = RectMake(_rcMapGrid.left, _rcMapGrid.top, camWidth, camHeight);

	//MAP SIZE WIDTH	: 25728 (TILE X : 200)
	//MAP SIZE HEIGHT	: 6464	(TILE Y : 200)
	//Game Resolution : 1280 : 720 = 16 : 9
	//Minimap Resolution : 190 : 125 = a : b	
}

void minimap::render()
{
	if (FALSE == _isIntro)
	{
		_minimapFrame->frameRender(getMemDC(), _rcMinimap.left, _rcMinimap.top, _minimapFrame->getFrameX(), _minimapFrame->getFrameY());
		_minimap->frameRender(getMemDC(), _rcMinimap.left, _rcMinimap.top, _minimap->getFrameX(), _minimap->getFrameY());
		//_minimapShadow->frameRender(getMemDC(), _rcMinimap.left, _rcMinimap.top, _minimapShadow->getFrameX(), _minimapShadow->getFrameY());

		return;
	}

	_minimapFrame->frameRender(getMemDC(), _rcMinimap.left, _rcMinimap.top, _minimapFrame->getFrameX(), _minimapFrame->getFrameY());
	_minimap->frameRender(getMemDC(), _rcMinimap.left, _rcMinimap.top, _minimap->getFrameX(), _minimap->getFrameY());
	_minimapGrid->render(getMemDC(), _rcMinimap.left, _rcMinimap.top);
	//_minimapShadow->frameRender(getMemDC(), _rcMinimap.left, _rcMinimap.top, _minimapShadow->getFrameX(), _minimapShadow->getFrameY());

	renderMinimapCamera();

	//for (int i = 0; i < MINIMAP_GRID_X; i++)
	//{
	//	for (int j = 0; j < MINIMAP_GRID_Y; j++)
	//	{
	//		Rectangle(getMemDC(), _arrRcMapGrid[i][j].left, _arrRcMapGrid[i][j].top, _arrRcMapGrid[i][j].right, _arrRcMapGrid[i][j].bottom);
	//	}
	//}
}

void minimap::initMinimapGrid()
{
	RECT rcGrid;
	float x, y, width, height;
	for (int i = 0; i < MINIMAP_GRID_X; i++)
	{
		for (int j = 0; j < MINIMAP_GRID_Y; j++)
		{
			x = 190 * i / MINIMAP_GRID_X;
			y = 125 * j / MINIMAP_GRID_Y;
			width = 190 / MINIMAP_GRID_X;
			height = 125 / MINIMAP_GRID_Y;
			rcGrid = RectMake(_rcMapGrid.left + x, _rcMapGrid.top + y, width, height);
			_arrRcMapGrid[i][j] = rcGrid;
		}
	}
}

void minimap::updateIntro()
{
	_frameTime++;
	if (_frameTime % 2 == 0)
	{
		_minimap->setFrameX(_frame);
		_minimapFrame->setFrameX(_frame);
		_minimapShadow->setFrameX(_frame);
		if (_frame > _minimapFrame->getMaxFrameX() &&
			_frame > _minimap->getMaxFrameX() &&
			_frame > _minimapShadow->getMaxFrameX())
		{
			_isIntro = TRUE;
			return;
		}
		_frame++;
	}
}

void minimap::renderMinimapCamera()
{
	HPEN myPen, oldPen;
	HBRUSH myBrush, oldBrush;
	myPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
	myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	Rectangle(getMemDC(), _rcCamera.left, _rcCamera.top, _rcCamera.right, _rcCamera.bottom);
	SelectObject(getMemDC(), oldPen);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myPen);
	DeleteObject(myBrush);
}

void minimap::setMapSize(float x, float y)
{
	_mapSizeX = x;
	_mapSizeY = y;
}

void minimap::setCamera(float posX, float posY)
{
	_cameraX = posX;
	_cameraY = posY;
}
