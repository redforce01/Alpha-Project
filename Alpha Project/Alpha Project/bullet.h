#pragma once
#include  "gameNode.h"
#define BULLET_SPEED 3
class bullet : public gameNode
{
private:
	image* _bullet;
	RECT _rcBullet;

	float _currentX, _currentY;
	float _fireAngle;
	float _bulletAngle;

	float _shotPower;
	float _gravity;

	bool _isFinish;
	
public:
	bullet();
	~bullet();

	HRESULT init();
	void release();
	void update();
	void render();


	bool getFinish() { return _isFinish; }

	void setGravity(float gravity) { _gravity = gravity; }
	void setShotPower(float power) { _shotPower = power; }
	void setStartXY(float x, float y) { _currentX = x, _currentY = y; }
	void setFireAngle(float fireAngle) { _fireAngle = fireAngle; }

	void functionCameraLeft(int cameraSpeed);
	void functionCameraRight(int cameraSpeed);
	void functionCameraUp(int cameraSpeed);
	void functionCameraDown(int cameraSpeed);
};

