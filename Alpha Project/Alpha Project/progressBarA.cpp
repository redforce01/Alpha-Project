#include "stdafx.h"
#include "progressBarA.h"


progressBarA::progressBarA()
{
}


progressBarA::~progressBarA()
{
}

HRESULT progressBarA::init(char * btnFrontImageKeyName, char * btnBackImageKeyName, float x, float y, int width, int height, bool normal)
{
	_hasRH = false;
	_x = x;
	_y = y;

	_rcProgress = RectMake(_x, _y, width, height);
	char strWhiteName[128];
	char strBackName[128];

	ZeroMemory(strWhiteName, sizeof(strWhiteName));
	ZeroMemory(strBackName, sizeof(strBackName));

	sprintf_s(strWhiteName, "image/progressBar/%s.bmp", btnFrontImageKeyName);
	sprintf_s(strBackName, "image/progressBar/%s.bmp", btnBackImageKeyName);
	if (normal)
	{
		_progressBarWH = IMAGEMANAGER->addImage("btnNormalFrontKeyName", strWhiteName, x, y, width, height, true, RGB(0, 0, 0));
		_progressBarBack = IMAGEMANAGER->addImage("btnNormalBackKeyName", strBackName, x, y, width, height, true, RGB(0, 0, 0));
	}
	else
	{
		_progressBarWH = IMAGEMANAGER->addImage("btnNormalFrontKeyName", strWhiteName, x, y, width, height, true, 0xff00ff);
		_progressBarBack = IMAGEMANAGER->addImage("btnNormalBackKeyName", strBackName, x, y, width, height, true, 0xff00ff);
	}

	_width = width;

	return S_OK;
}

HRESULT progressBarA::init(char * btnUpImageKeyName, char * btnDownImageKeyName, float x, float y, int width, int height)
{
	_hasRH = false;
	_x = x;
	_y = y;

	_rcProgress = RectMake(_x, _y, width, height);
	char strWhiteName[128];
	char strBackName[128];

	ZeroMemory(strWhiteName, sizeof(strWhiteName));
	ZeroMemory(strBackName, sizeof(strBackName));

	sprintf_s(strWhiteName, "image/progressBar/%s.bmp", btnUpImageKeyName);
	sprintf_s(strBackName, "image/progressBar/%s.bmp", btnDownImageKeyName);

	_progressBarWH = IMAGEMANAGER->addImage("btnWHImageKeyName", strWhiteName, x, y, width, height, true, 0xff00ff);
	_progressBarBack = IMAGEMANAGER->addImage("btnBackImageKeyName", strBackName, x, y, width, height, true, 0xff00ff);

	_width = width;

	return S_OK;
}

HRESULT progressBarA::init(char * btnRHImageKeyName, char * btnWHImageKeyName, char * btnBackImageKeyName, float x, float y, int width, int height)
{
	_hasRH = false;
	_x = x;
	_y = y;

	_rcProgress = RectMake(_x, _y, width, height);

	char strRedName[128];
	char strWhiteName[128];
	char strBackName[128];

	ZeroMemory(strRedName, sizeof(strRedName));
	ZeroMemory(strWhiteName, sizeof(strWhiteName));
	ZeroMemory(strBackName, sizeof(strBackName));

	sprintf_s(strRedName, "image/progressBar/%s.bmp", btnRHImageKeyName);
	sprintf_s(strWhiteName, "image/progressBar/%s.bmp", btnWHImageKeyName);
	sprintf_s(strBackName, "image/progressBar/%s.bmp", btnBackImageKeyName);

	_progressBarRH = IMAGEMANAGER->addImage("btnRHImageKeyName", strRedName, x, y, width, height, true, 0xff00ff);
	_progressBarWH = IMAGEMANAGER->addImage("btnWHImageKeyName", strWhiteName, x, y, width, height, true, 0xff00ff);
	_progressBarBack = IMAGEMANAGER->addImage("btnBackImageKeyName", strBackName, x, y, width, height, true, 0xff00ff);

	_width = width;
	_hasRH = true;

	return S_OK;
}

void progressBarA::release()
{
}

void progressBarA::update()
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBarA::render()
{
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y, 0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	_progressBarWH->render(getMemDC(), _rcProgress.left, _y, 0, 0,
		_width, _progressBarWH->getHeight());

	if (_hasRH)
		_progressBarRH->render(getMemDC(), _rcProgress.left, _y, 0, 0,
			_widthRH, _progressBarRH->getHeight());
}

void progressBarA::gauge(float currentGauge, float maxGauge, float rateRH)
{
	_widthRH = (currentGauge/ maxGauge) * (rateRH / 100) * _progressBarRH->getWidth();
	_width = (currentGauge / maxGauge) * _progressBarWH->getWidth();
}

void progressBarA::gauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarWH->getWidth();
}
