#include "stdafx.h"
#include "IsoMetricArea.h"


IsoMetricArea::IsoMetricArea()
{
}


IsoMetricArea::~IsoMetricArea()
{
}

HRESULT IsoMetricArea::init(float startX, float startY, int areaNumber)
{
	_nArea = areaNumber;
	_startX = startX;
	_startY = startY;

	for (int i = 0; i < AREA_SIZE_X; i++)
	{
		for (int j = 0; j < AREA_SIZE_Y; j++)
		{
			_rcIsoTile[i][j] = RectMake(
				startX + (i - j) * WORLDMAP_ISO_WIDTH / 2, startY + (i + j) * WORLDMAP_ISO_HEIGHT / 2,
				WORLDMAP_ISO_WIDTH, WORLDMAP_ISO_HEIGHT);
		}
	}
	

	return S_OK;
}

void IsoMetricArea::release()
{
}

void IsoMetricArea::update()
{
	for (int i = 0; i < AREA_SIZE_X; i++)
	{
		for (int j = 0; j < AREA_SIZE_Y; j++)
		{
			_rcIsoTile[i][j] = RectMake(
				_startX + (i - j) * WORLDMAP_ISO_WIDTH / 2, _startY + (i + j) * WORLDMAP_ISO_HEIGHT / 2,
				WORLDMAP_ISO_WIDTH, WORLDMAP_ISO_HEIGHT);
		}
	}

}

void IsoMetricArea::render()
{
	for (int i = 0; i < AREA_SIZE_X; i++)
	{
		for (int j = 0; j < AREA_SIZE_Y; j++)
		{
			//Rectangle(getMemDC(), _rcIsoTile[i][j].left, _rcIsoTile[i][j].top, _rcIsoTile[i][j].right, _rcIsoTile[i][j].bottom);
			//IsoRender(getMemDC(), _rcIsoTile[i][j]);
			
		}
	}
}
