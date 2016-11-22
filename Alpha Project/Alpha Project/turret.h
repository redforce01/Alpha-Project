#pragma once
#include "gameNode.h"
#include "bullet.h"

#define TURRET_ANGLE_CHANGESPEED 0.08f
#define BULLET_SIZE 100

class turret : public gameNode
{
private:
	image* _turret;
	image* _cylinder;
	RECT _rcTurret;
	RECT _rcCylinder;
	float _turretX, _turretY;
	float _shipX, _shipY;

	int _turretNumber;
	int _distanceX[36];
	int _distanceY[36];

	int _distance;

	float _shipAngle;
	
	float _targetX, _targetY;
	float _turretAngle;
	float _cylinderAngle;
	float _targetAngle;
	int _frameX;
	int _frameY;

	float _cylinderFrameX;
	float _cylinderFrameY;
	

	float _rateOfFire;
	float _rateOfTime;
	
	bool _bFire;
	bool _bAimTarget;

private:
	bullet* _bullet[BULLET_SIZE];
	

public:
	turret();
	~turret();

	HRESULT init();
	void release();
	void update();
	void render();

	void updateTurretAngle();
	void updateTurretPos();
	void updateTurretFrame();
	void updateCylinderFrame();

	void initTurret(string unitName, float shipX, float shipY, int distance,/* int turretNumber,*/ float dirAngle);


	void setShipPos(float shipX, float shipY, float shipAngle);
	void setTarget(float targetX, float targetY) { _targetX = targetX, _targetY = targetY; }
	void setAngle(float angle) { _turretAngle = angle; }
	void setFire(float targetX, float targetY);

	POINT getTurretPos() { return PointMake(_turretX, _turretY); }

	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);
};

