#pragma once
#include "gameNode.h"

#define DESTINATION_TIME 10.f
class destinationUI : public gameNode
{
private:
	image* _destination;
	RECT _rcDestination;
	float _x, _y;

	int _frame;
	int _frameTime;

	float _showTime;
	bool _isFinish;
	bool _isShow;

public:
	destinationUI();
	~destinationUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDestPos(float x, float y);
	void setReInit();
	void setShow() { _isShow = TRUE; }

	bool setFinish(bool flag) { _isFinish = flag; }
	bool getFinish() { return _isFinish; }

	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);
};

