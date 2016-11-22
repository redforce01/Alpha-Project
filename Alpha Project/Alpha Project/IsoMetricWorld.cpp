#include "stdafx.h"
#include "IsoMetricWorld.h"


IsoMetricWorld::IsoMetricWorld()
{
}


IsoMetricWorld::~IsoMetricWorld()
{
}

HRESULT IsoMetricWorld::init()
{
	int _areaNum = 0;
	_areaX[0][0] = 1300;	 _areaY[0][0] = 0;
	_areaX[0][1] = 960;		 _areaY[0][1] = 180;
	_areaX[0][2] = 590;		 _areaY[0][2] = 350;
	_areaX[0][3] = 250;		 _areaY[0][3] = 530;
	_areaX[0][4] = 0;		 _areaY[0][4] = 720;

	_areaX[1][0] = 1730;	 _areaY[1][0] = 150;
	_areaX[1][1] = 1380;	 _areaY[1][1] = 330;
	_areaX[1][2] = 1020;	 _areaY[1][2] = 510;
	_areaX[1][3] = 680;		 _areaY[1][3] = 680;
	_areaX[1][4] = 320;		 _areaY[1][4] = 860;

	_areaX[2][0] = 2160;	 _areaY[2][0] = 290;
	_areaX[2][1] = 1830;	 _areaY[2][1] = 470;
	_areaX[2][2] = 1470;	 _areaY[2][2] = 650;
	_areaX[2][3] = 1130;	 _areaY[2][3] = 840;
	_areaX[2][4] = 755;		 _areaY[2][4] = 1010;

	_areaX[3][0] = 2600;	 _areaY[3][0] = 450;
	_areaX[3][1] = 2240;	 _areaY[3][1] = 620;
	_areaX[3][2] = 1900;	 _areaY[3][2] = 800;
	_areaX[3][3] = 1555;	 _areaY[3][3] = 980;
	_areaX[3][4] = 1190;	 _areaY[3][4] = 1160;

	_areaX[4][0] = 2980;	 _areaY[4][0] = 600;
	_areaX[4][1] = 2680;	 _areaY[4][1] = 780;
	_areaX[4][2] = 2330;	 _areaY[4][2] = 940; 
	_areaX[4][3] = 1980;	 _areaY[4][3] = 1130;
	_areaX[4][4] = 1630;	 _areaY[4][4] = 1290;

	for (int i = 0; i < WORLDMAP_SIZE_X; i++)
	{
		for (int j = 0; j < WORLDMAP_SIZE_Y; j++)
		{
			_IsoMetricArea[i][j] = new IsoMetricArea;
			_IsoMetricArea[i][j]->init(0, 0 - 200, _areaNum);
			_areaNumber[i][j] = _areaNum;
			_areaNum++;
		}
	}

	return S_OK;
}

void IsoMetricWorld::release()
{
	for (int i = 0; i < WORLDMAP_SIZE_X; i++)
	{
		for (int j = 0; j < WORLDMAP_SIZE_Y; j++)
		{
			_IsoMetricArea[i][j]->release();
		}
	}
}

void IsoMetricWorld::update()
{
	for (int i = 0; i < WORLDMAP_SIZE_X; i++)
	{
		for (int j = 0; j < WORLDMAP_SIZE_Y; j++)
		{
			_IsoMetricArea[i][j]->update();
		}
	}
}

void IsoMetricWorld::render()
{
	for (int i = 0; i < WORLDMAP_SIZE_X; i++)
	{
		for (int j = 0; j < WORLDMAP_SIZE_Y; j++)
		{
			_IsoMetricArea[i][j]->render();
		}
	}
}