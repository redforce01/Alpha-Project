#pragma once
#include "gameNode.h"
#include "IsoMetricArea.h"

#define WORLDMAP_SIZE_X 5
#define WORLDMAP_SIZE_Y 5

class IsoMetricWorld : public gameNode
{
private:
	IsoMetricArea* _IsoMetricArea[WORLDMAP_SIZE_X][WORLDMAP_SIZE_Y];
	int _areaNumber[WORLDMAP_SIZE_X][WORLDMAP_SIZE_Y];
	int _areaX[WORLDMAP_SIZE_X][WORLDMAP_SIZE_Y];
	int _areaY[WORLDMAP_SIZE_X][WORLDMAP_SIZE_Y];
		
public:
	IsoMetricWorld();
	~IsoMetricWorld();

	HRESULT init();
	void release();
	void update();
	void render();

	int getAreaNumber(int areaX, int areaY) { return _areaNumber[areaX][areaY]; }
	int getAreaX(int areaX, int areaY) { return _areaX[areaX][areaY]; }
	int getAreaY(int areaX, int areaY) { return _areaY[areaX][areaY]; }
};

