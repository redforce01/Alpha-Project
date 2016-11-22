#pragma once
#include "gameNode.h"
#include "turret.h"
#include "destinationUI.h"
#include "selectingUI.h"

#define HARBOR_X 200
#define HARBOR_Y 200
#define FIELD_NORMAL_FRAME_X 36
#define FIELD_NORMAL_FRAME_Y 1
#define SHIP_SPEED_NORMALIZE 0.05f
#define SHIP_CHANGE_SPEED 0.01f
#define SHIP_CHANGE_ANGLE 0.008f
#define ANGLE_CORRECTION 90

#define ANGLE_FIXVALUE 0.01f

enum SHIP_RENDER_SEQUENCE
{
	SHIP_RENDER_SEQUENCE_TOP, SHIP_RENDER_SEQUENCE_CENTER, SHIP_RENDER_SEQUENCE_BOTTOM,
	SHIP_RENDER_SEQUENCE_SHADOW, SHIP_RENDER_SEQUENCE_WAVE, SHIP_RENDER_SEQUENCE_TURRET
};

class ship : public gameNode
{
private:
	image* _fieldTop;
	image* _fieldCenter;
	image* _fieldBottom;
	image* _fieldShadow;

	image* _fieldSink;
	image* _fieldSinkShadow;
	image* _fieldWave;

	image* _harborTop;
	image* _harborCenter;
	image* _harborBottom;
	image* _harborWave;

	float	_harborX, _harborY;
	float	_currentX, _currentY;
	float	_targetX, _targetY;
	RECT	_rcUnit;
	RECT	_rcForMove;
	float	_currentAngle;
	float	_targetAngle;
	int		_frameX;
	int		_frameY;

	int		_waveFrameTime;
	int		_waveFrameX;
	int		_waveFrameY;

	float _currentSpeed;
	float _targetSpeed;

	float _reverseAngle, _inverseAngle;

	int _turretSize;
	vector<turret*> _vTurret;

private:
	bool _bSetUpField;
	bool _bDestination;

	bool _bSelected;

	SHIP_ORDER_MOVEMENT_STATE _stateMovement;
	destinationUI* _destinationUI;
	selectingUI* _selectingUI;
private:
	string	_shipName;
	string	_shipClass;
	int		_shipDP;
	int		_shipWeight;
	int		_shipDefenExTop;
	int		_shipDefenPeTop;
	int		_shipDefenExBottom;
	int		_shipDefenPeBottom;
	float	_shipInchTop;
	float	_shipInchBottom;
	string	_shipRaderName;
	int		_shipRange;
	int		_shipAccuracy;
	string	_shipEngineName;
	int		_shipEnginePower;
	int		_shipMinSpeed;
	int		_shipMaxSpeed;

public:
	ship();
	~ship();
	
	HRESULT init();
	void release();
	void update();
	void render();
	
public:
	void initForHarbor(string unitName);
	void initForField(string unitName);
	void initForInformation(string unitName);
	void renderField();
	void renderHarbor();

	void renderDebugInfo();
public:
	void setUpField(float x, float y);
	void setUpTarget(float targetX, float targetY);
	void setUpHarbor(float harborX, float harborY);
	void setDestination(bool flag) { _bDestination = flag; }
	
	void setSelected(bool flag) { _bSelected = flag; }

	RECT getShipRect() { return _rcUnit; }
	int getShipRectWidth() { return _rcUnit.right - _rcUnit.left; }
	int getShipRectHeight() { return _rcUnit.bottom - _rcUnit.top; }
	POINT getShipPos() { return PointMake(_currentX, _currentY); }
	float getShipSpeed() { return _currentSpeed; }
	bool getDestination() { return _bDestination; }


	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);

public:
	void updateDestination();

public:
	void updateInterTargetXY();
	void updateMovement();
	void updateAngle();

	void updateTurret();

	void orderMovement(SHIP_ORDER_MOVEMENT_STATE orderMovement, float targetX, float targetY);
	void orderMovement(SHIP_ORDER_MOVEMENT_STATE orderMovement, float targetX, float targetY, int speed);
};

