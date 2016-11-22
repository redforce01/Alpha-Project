#pragma once
#include "gameNode.h"
class selectingUI : public gameNode
{
private:
	image* _indicator;
	RECT _rcIndicator;
	int _frame;
	int _frameTime;
	float _x, _y;

	float _knt;
	vector<image*> _vKnt;
	

public:
	selectingUI();
	~selectingUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void setKnt(float knt) { _knt = knt; }
	void setIndicatorPos(float x, float y);

	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);
};

