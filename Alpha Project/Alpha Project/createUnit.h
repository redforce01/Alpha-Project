#pragma once
#include "gameNode.h"

#define UNIT_SETUP_TIME 0.1f

class createUnit : public gameNode
{
private:
	image* _fieldTopImage;
	image* _fieldCenterImage;
	image* _fieldBottomImage;

	RECT _rcUnit;
	float _x, _y;
	int _frame;
	float _setUpTime;
	bool _isSetUp;
	POINT _setUpPos;

public:
	createUnit();
	~createUnit();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void setUnit(string imageName, float x, float y);
	
	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);
	
	POINT getTargetXY() { return _setUpPos; }
	bool getOnUnit() { return _isSetUp; }
	RECT getCreateUnitRect() { return _rcUnit; }
};

