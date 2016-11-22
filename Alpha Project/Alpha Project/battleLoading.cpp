#include "stdafx.h"
#include "battleLoading.h"


battleLoading::battleLoading()
{
}


battleLoading::~battleLoading()
{
}

HRESULT battleLoading::init()
{
	_loadingBackground = IMAGEMANAGER->addImage("battleLoading", "image/battle/battle_loading_background.bmp", 1280, 720, false, false);
	IMAGEMANAGER->addImage("battleLoadingBar", "image/battle/battle_loading_bar.bmp", 287, 4, false, false);
	IMAGEMANAGER->addImage("battleLoadingBack", "image/battle/battle_loading_back.bmp", 290, 6, true, RGB(0, 0, 0));


	IMAGEMANAGER->addFrameImage("field_top_Fletcher", "image/ships/Fletcher/field_top_Fletcher.bmp", 6480, 134, 36, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("field_center_Fletcher", "image/ships/Fletcher/field_center_Fletcher.bmp", 6480, 134, 36, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("field_bottom_Fletcher", "image/ships/Fletcher/field_bottom_Fletcher.bmp", 6480, 134, 36, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("field_shadow_Fletcher", "image/ships/Fletcher/field_shadow_Fletcher.bmp", 6480, 134, 36, 1, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("field_sink_Fletcher", "image/ships/Fletcher/field_sink_Fletcher.bmp", 1800, 1206, 10, 9, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("field_sinkShadow_Fletcher", "image/ships/Fletcher/field_sinkShadow_Fletcher.bmp", 1800, 1206, 10, 9, true, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("field_wave_Fletcher", "image/ships/Fletcher/field_wave_Fletcher.bmp", 1800, 4824, 10, 36, true, RGB(0, 0, 0));
	

	_loadingBar = new progressBarA;
	_loadingBar->init("battle_loading_bar", "battle_loading_back", 496, 397, 290, 6, true);
	_loadingBar->gauge(0, 100);

	_timeLoading = 0;
	_loadingCount = 100;
	_bCompleteLoading = false;

	return S_OK;
}

void battleLoading::release()
{
	_loadingBar->release();
	SAFE_DELETE(_loadingBar);
}

void battleLoading::update()
{
	_timeLoading += TIMEMANAGER->getElapsedTime();
	
	_loadingBar->gauge(_loadingCount, 100);
	_loadingBar->update();
	if (!_bCompleteLoading)
	{
		
	}

	if (_loadingCount >= 100)
	{
		_bCompleteLoading = true;
	}
}

void battleLoading::render()
{
	_loadingBackground->render(getMemDC());
	_loadingBar->render();
}
