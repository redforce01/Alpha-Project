#include "stdafx.h"
#include "turret.h"


turret::turret()
{
}


turret::~turret()
{
}

HRESULT turret::init()
{
	_turret = NULL;
	_cylinder = NULL;
	_rcTurret = RectMakeCenter(0, 0, 0, 0);
	_rcCylinder = RectMakeCenter(0, 0, 0, 0);
	_turretX = _turretY = 0;
	_shipX = 0, _shipY = 0;

	_targetX = _targetY = 0;

	_shipAngle = 0;
	_turretAngle = 0;
	_targetAngle = 0;
	_cylinderAngle = 0;

	_frameX = 0;
	_frameY = 0;

	_cylinderFrameX = 0;
	_cylinderFrameY = 0;

	_rateOfFire = 0;
	_rateOfTime = 0;

	_bFire = false;
	_bAimTarget = false;

	return S_OK;
}

void turret::release()
{
}

void turret::update()
{
	if (_turretAngle > PI2) _turretAngle -= PI2;
	if (_turretAngle < 0) _turretAngle += PI2;

	updateTurretFrame();
	updateCylinderFrame();
	updateTurretAngle();
	updateTurretPos();

	
	if (_cylinder == NULL) return;
	if (_turret == NULL) return;
	
	_rcTurret = RectMakeCenter(_turretX, _turretY, _turret->getFrameWidth(), _turret->getFrameHeight());
	_rcCylinder = RectMakeCenter(_turretX - 7, _turretY, _cylinder->getFrameWidth(), _cylinder->getFrameHeight());
	
}

void turret::render()
{
	if (_cylinder == NULL || _turret == NULL) return;

	_turret->frameRender(getBattleDC(), _rcTurret.left, _rcTurret.top, _turret->getFrameX(), _turret->getFrameY());
	_cylinder->frameRender(getBattleDC(), _rcCylinder.left, _rcCylinder.top, _cylinder->getFrameX(), _cylinder->getFrameY());

	//Rectangle(getMemDC(), _rcTurret.left, _rcTurret.top, _rcTurret.right, _rcTurret.bottom);
	//Rectangle(getMemDC(), _rcCylinder.left, _rcCylinder.top, _rcCylinder.right, _rcCylinder.bottom);
}

void turret::updateTurretAngle()
{
	_targetAngle = getAngle(_turretX, _turretY, _targetX, _targetY);
	
	if (_turretAngle < _targetAngle) _turretAngle += TURRET_ANGLE_CHANGESPEED;
	if (_turretAngle > _targetAngle) _turretAngle -= TURRET_ANGLE_CHANGESPEED;

}

void turret::updateTurretPos()
{	
	//_turretX = _shipX + _distanceX[_frameX];
	//_turretY = _shipY + _distanceY[_frameX];

	int value = RadianToDegree(_shipAngle) / 10;
	value = value - 17;
	if (value < 0) value += 36;
	value *= 10;

	_turretX = _shipX + _distance *  cosf(DegreeToRadian(value));
	_turretY = _shipY + _distance * -sinf(DegreeToRadian(value)) * 0.6;
}

void turret::updateTurretFrame()
{

	//함포 자체의 바라보는 방향 각도에 따른 프레임 출력
	if (RadianToDegree(_turretAngle) >= 0 && RadianToDegree(_turretAngle) <= 90)
	{
		_frameX = RadianToDegree(_turretAngle) / 10 - 9;
		if (_frameX < 0) _frameX += 36;
	}
	else _frameX = RadianToDegree((_turretAngle - DegreeToRadian(90))) / 10;
}

void turret::updateCylinderFrame()
{
	_cylinderFrameX = _cylinderAngle / 10;
	if (RadianToDegree(_turretAngle) >= 0 && RadianToDegree(_turretAngle) <= 90)
	{
		_cylinderFrameY = RadianToDegree(_turretAngle) / 10 - 9;
		if (_cylinderFrameY < 0) _cylinderFrameY += 36;
	}
	else _cylinderFrameY = RadianToDegree((_turretAngle - DegreeToRadian(90))) / 10;
}

void turret::initTurret(string unitName, float shipX, float shipY, int distance/* int turretNumber*/, float dirAngle)
{
	_shipX = shipX;
	_shipY = shipY;
	//_turretNumber = turretNumber;
	_distance = distance;

	//for (int i = 0; i < 36; i++)
	//{
	//	_distanceX[i] = DATABASE->getTurretList(unitName)->interpolateX[i + 36 * _turretNumber];
	//	_distanceY[i] = DATABASE->getTurretList(unitName)->interpolateY[i + 36 * _turretNumber];
	//}

	_shipAngle = dirAngle;

	_turretX = _shipX + _distance *  cosf(_shipAngle);
	_turretY = _shipY + _distance * -sinf(_shipAngle);

	//_turretX = _shipX + _distanceX[_frameX];
	//_turretY = _shipY + _distanceY[_frameX];
	
	_turret = new image;
	_turret->init(
		DATABASE->getTurretList(unitName)->turretImageKey.c_str(),
		DATABASE->getTurretList(unitName)->imageWidth,
		DATABASE->getTurretList(unitName)->imageHeight,
		DATABASE->getTurretList(unitName)->maxFrameX,
		DATABASE->getTurretList(unitName)->maxFrameY,
		true, TRANS_RGB);


	_cylinder = new image;
	_cylinder->init(
		DATABASE->getTurretList(unitName)->cylinderImageKey.c_str(),
		DATABASE->getTurretList(unitName)->cylinderImageWidth,
		DATABASE->getTurretList(unitName)->cylinderImageHeight,
		DATABASE->getTurretList(unitName)->cylinderMaxFrameX,
		DATABASE->getTurretList(unitName)->cylinderMaxFrameY,
		true, TRANS_RGB);
	
	//for (int i = 0; i < BULLET_SIZE; i++)
	//{
	//	_bullet[i] = new bullet;
	//	_bullet[i]->init();
	//}
}

void turret::setShipPos(float shipX, float shipY, float shipAngle)
{
	_shipX = shipX;
	_shipY = shipY;
	_shipAngle = shipAngle;

	
}

void turret::setFire(float targetX, float targetY)
{
}

void turret::functionCameraLeft(int cameraSpeed)
{
	_turretX += cameraSpeed;
}

void turret::functionCameraRight(int cameraSpeed)
{
	_turretX -= cameraSpeed;
}

void turret::functionCameraUp(int cameraSpeed)
{
	_turretY += cameraSpeed;
}

void turret::functionCameraDown(int cameraSpeed)
{
	_turretY -= cameraSpeed;
}
