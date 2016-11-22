#pragma once
#include "gameNode.h"

struct tagMinimapDot
{
	image* dot;
	RECT rcDot;
	float x, y;
	RADAR_DOT_TYPE dotType;
};

class minimap : public gameNode
{
private:
	image*	_minimap;
	image*	_minimapFrame;
	image*	_minimapShadow;
	RECT	_rcMinimap;

	int		_frame;
	int		_frameTime;

	image*	_minimapGrid;
	image*	_minimapGridShadow;

	RECT	_rcMapGrid;
	RECT	_arrRcMapGrid[MINIMAP_GRID_X][MINIMAP_GRID_Y];

	RECT	_rcCamera;
	float	_cameraX, _cameraY;
	float	_mapSizeX, _mapSizeY;


	bool	_isIntro;
	vector<tagMinimapDot*> _minimapDotPlayer;
	vector<tagMinimapDot*> _minimapDotEnemy;
	
public:
	minimap();
	~minimap();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

public:
	void initMinimapGrid();

	void updateIntro();
	void UpdateDot();

	void renderMinimapCamera();

public:
	void setMapSize(float x, float y);
	void setCamera(float posX, float posY);
	void setSelectDot(int unitNumber);

	RECT getMinimapRect() { return _rcMapGrid; }
	RECT getMinimapGrid(int x, int y) { return _arrRcMapGrid[x][y]; }

	void addPlayerDot(float x, float y);
	void addEnemyDot(float x, float y);
};

