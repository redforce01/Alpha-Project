#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init( char * btnUpImageKeyName, char * btnDwonImageKeyName, float x, float y, int width, int height )
{
	_x = x;
	_y = y;

	_rcProgress = RectMake( _x, _y, width, height );

	char strUpName[128];
	char strDownName[128];

	ZeroMemory( strUpName, sizeof( strUpName ) );
	ZeroMemory( strDownName, sizeof( strDownName ) );

	sprintf_s( strUpName, "image/%s.bmp", btnUpImageKeyName );
	sprintf_s( strDownName, "image/%s.bmp", btnDwonImageKeyName );

	_progressBarFront = IMAGEMANAGER->addImage( "btnUpImageKeyName", strUpName, x, y, width, height, true, 0xff00ff );
	_progressBarBack = IMAGEMANAGER->addImage( "btnDwonImageKeyName", strDownName, x, y, width, height, true, 0xff00ff );

	_width = width;

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMake(_x, _y, _progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render()
{
	/*IMAGEMANAGER->render("barBottom", getMemDC(),
		_rcProgress.left,
		_y,
		0, 0, 
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMAGEMANAGER->render("barTop", getMemDC(),
		_rcProgress.left,
		_y,
		0, 0, 
		_width, _progressBarFront->getHeight());*/

	_progressBarBack->render( getMemDC(), _rcProgress.left, _y, 0, 0,
		_progressBarBack->getWidth(),
		_progressBarBack->getHeight() );

	_progressBarFront->render( getMemDC(), _rcProgress.left, _y, 0, 0,
		_width, _progressBarFront->getHeight() );
}

//게이지 바
void progressBar::gauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarFront->getWidth();
}