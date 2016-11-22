#pragma once
#include "gameNode.h"

#define WORLDMAP_ISO_WIDTH 160
#define WORLDMAP_ISO_HEIGHT 60
#define AREA_SIZE_X 5
#define AREA_SIZE_Y 5

class IsoMetricArea : public gameNode
{
private:
	RECT _rcIsoTile[AREA_SIZE_X][AREA_SIZE_Y];
	int _nArea;
	float _startX, _startY;

public:
	IsoMetricArea();
	~IsoMetricArea();

	HRESULT init(float startX, float startY, int areaNumber);
	void release();
	void update();
	void render();

	int getAreaNumber(int area) { return _nArea; }
};