#include "stdafx.h"
#include "bullet.h"


bullet::bullet()
{
}


bullet::~bullet()
{
}

HRESULT bullet::init()
{
	_bullet = new image;
	_bullet->init("image/bullet/bulletWhite.bmp", 18, 18, true, RGB(0, 0, 0));
	_rcBullet = RectMake(0, 0, 0, 0);

	_currentX = _currentY = 0;
	_fireAngle = 0;
	_bulletAngle = 0;
	_shotPower = 2.0f;
	_gravity = 0.08f;

	_isFinish = false;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	if (_isFinish) return;

	_shotPower = -sinf(_bulletAngle);
	_shotPower -= _gravity;

	_currentX += cosf(_fireAngle) * BULLET_SPEED;
	_currentY += -sinf(_fireAngle) * BULLET_SPEED + _shotPower;

	_rcBullet = RectMakeCenter(_currentX, _currentY, _bullet->getWidth(), _bullet->getHeight());
}

void bullet::render()
{
	if (_isFinish) return;

	_bullet->render(getMemDC(), _rcBullet.left, _rcBullet.top);
}

void bullet::functionCameraLeft(int cameraSpeed)
{
	_currentX += cameraSpeed;
}

void bullet::functionCameraRight(int cameraSpeed)
{
	_currentX -= cameraSpeed;
}

void bullet::functionCameraUp(int cameraSpeed)
{
	_currentY += cameraSpeed;
}

void bullet::functionCameraDown(int cameraSpeed)
{
	_currentY -= cameraSpeed;
}
