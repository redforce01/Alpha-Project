#pragma once
#include "gameNode.h"
class progressBarA : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y;
	float _width;
	float _widthRH;

	image* _progressBarRH;
	image* _progressBarWH;
	image* _progressBarBack;
	bool _hasRH;
	
public:
	progressBarA();
	~progressBarA();

	HRESULT init(char* btnFrontImageKeyName, char* btnBackImageKeyName, float x, float y, int width, int height, bool normal);
	HRESULT init(char* btnUpImageKeyName, char* btnDownImageKeyName, float x, float y, int width, int height);
	HRESULT init(char* btnRHImageKeyName, char* btnWHImageKeyName, char* btnBackImageKeyName, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	void gauge(float currentGauge, float maxGauge);
	void gauge(float currentGauge, float maxGauge, float rateRH);
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};

