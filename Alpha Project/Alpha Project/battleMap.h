#pragma once
#include "gameNode.h"
#include "battleArea.h"
#include "mapTile.h"

#define mapX 200
#define mapY 200
//MAP SIZE WIDTH	: 25728 (TILE X : 200)
//MAP SIZE HEIGHT	: 6464	(TILE Y : 200)

class battleMap : public gameNode
{
private:
	mapTile* _map[mapX][mapY];
	CAMERA_DIRECTION _direction;

	vector<battleArea*> _vArea;
	vector<battleArea*>::iterator _viArea;
public:
	battleMap();
	~battleMap();

	HRESULT init();
	void release();
	void update();
	void render();


	void functionMoveCamera(float moveX, float moveY, CAMERA_DIRECTION direction);
	
	void functionMoveLeft(int cameraSpeed);
	void functionMoveRight(int cameraSpeed);
	void functionMoveUp(int cameraSpeed);
	void functionMoveDown(int cameraSpeed);

	float getMapSizeX() { return (mapX * TILE_WIDTH) + TILE_WIDTH; }
	float getMapSizeY() { return (mapY * 64) - (TILE_HEIGHT / 2) * mapY + TILE_HEIGHT; }
};

