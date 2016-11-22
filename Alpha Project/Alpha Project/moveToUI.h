#pragma once
#include "gameNode.h"
class moveToUI : public gameNode
{
private:
	image* _moveTo;
	RECT _rcMoveTo;
	float _x, _y;
	
	int _frame;
	int _frameTime;

	bool _isShow;

public:
	moveToUI();
	~moveToUI();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getShow() { return _isShow; }
	void setShow(bool flag) { _isShow = flag; }

	void setMoveToPos(float x, float y);
	
	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);
};

