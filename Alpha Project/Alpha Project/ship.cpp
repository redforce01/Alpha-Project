#include "stdafx.h"
#include "ship.h"


ship::ship()
{
}


ship::~ship()
{
}

HRESULT ship::init()
{	
	_fieldTop			= NULL;
	_fieldCenter		= NULL;
	_fieldBottom		= NULL;
	_fieldShadow		= NULL;

	_fieldSink			= NULL;
	_fieldSinkShadow	= NULL;
	_fieldWave			= NULL;

	_harborTop			= NULL;
	_harborCenter		= NULL;
	_harborBottom		= NULL;
	_harborWave			= NULL;
	
	_harborX = _harborY		= 0;
	_currentX = _currentY	= 0;
	_targetX = _targetY		= 0;
	_rcUnit = RectMakeCenter(0, 0, 0, 0);
	_rcForMove = RectMakeCenter(0, 0, 0, 0);
	_currentAngle = DegreeToRadian(90);
	_targetAngle = DegreeToRadian(90);
	_frameX = _frameY = 0;
	_waveFrameTime = 0;
	_waveFrameX = _waveFrameY = 0;
	_currentSpeed = _targetSpeed = 0;
	_reverseAngle = _inverseAngle = 0;

	_shipName			= "";
	_shipClass			= "";
	_shipDP				= 0;
	_shipWeight			= 0;
	_shipDefenExTop		= 0;
	_shipDefenPeTop		= 0;
	_shipDefenExBottom	= 0;
	_shipDefenPeBottom	= 0;
	_shipInchTop		= 0;
	_shipInchBottom		= 0;
	_shipRaderName		= "";
	_shipRange			= 0;
	_shipAccuracy		= 0;
	_shipEngineName		= "";
	_shipEnginePower	= 0;
	_shipMinSpeed		= 0;
	_shipMaxSpeed		= 0;
	
	_turretSize			= 0;
	
	_bSetUpField = false;
	_stateMovement = SHIP_ORDER_MOVEMENT_NULL;
	_bDestination = false;
	_bSelected = FALSE;

	return S_OK;
}

void ship::release()
{
}

void ship::update()
{
	if (! _bSetUpField) return;

	if (_fieldTop == NULL || _fieldCenter == NULL || _fieldBottom == NULL ||
		_fieldShadow == NULL || _fieldWave == NULL) return;

	_targetAngle = getAngle(_currentX, _currentY, _targetX, _targetY);

	//Ship Frame Update
	if (RadianToDegree(_currentAngle) >= 0 && RadianToDegree(_currentAngle) <= 90)
	{
		_frameX = static_cast<int>(RadianToDegree(_currentAngle) / 10 - 9);
		if (_frameX < 0) _frameX += 36;
	}
	else _frameX = static_cast<int>(RadianToDegree((_currentAngle - DegreeToRadian(90))) / 10);

	_fieldTop->setFrameX(_frameX);
	_fieldCenter->setFrameX(_frameX);
	_fieldBottom->setFrameX(_frameX);
	_fieldShadow->setFrameX(_frameX);

	//Wave Frame Update
	_waveFrameTime++;
	if (_waveFrameTime % 5 == 0)
	{
		_waveFrameX++;
		_fieldWave->setFrameX(_waveFrameX);
		if (_waveFrameX > _fieldWave->getMaxFrameX()) _waveFrameX = 0;
	}
	if (RadianToDegree(_currentAngle) >= 0 && RadianToDegree(_currentAngle) <= 90)
	{
		_waveFrameY = static_cast<int>(RadianToDegree(_currentAngle) / 10 - 9);
		if (_waveFrameY < 0) _waveFrameY += 36;
	}
	else _waveFrameY = static_cast<int>(RadianToDegree((_currentAngle - DegreeToRadian(90))) / 10);
	_fieldWave->setFrameY(_waveFrameY);

	if (_bSelected)
	{
		_selectingUI->setIndicatorPos(_currentX, _currentY);
		_selectingUI->update();
	}

	updateInterTargetXY();
	updateMovement();
	updateAngle();
	updateTurret();
	updateDestination();
	
	
	if(_currentX != _targetX) _currentX += cosf(_currentAngle) * _currentSpeed * SHIP_SPEED_NORMALIZE;
	if(_currentY != _targetY) _currentY += -sinf(_currentAngle) * _currentSpeed * SHIP_SPEED_NORMALIZE;
	

	_rcUnit = RectMakeCenter(_currentX, _currentY, _fieldTop->getFrameWidth(), _fieldTop->getFrameHeight());
	_rcForMove = RectMakeCenter(_currentX, _currentY, _fieldTop->getFrameWidth() / 2, _fieldTop->getFrameHeight() / 2);
}

void ship::render()
{
	//Rectangle(getBattleDC(), _rcUnit.left, _rcUnit.top, _rcUnit.right, _rcUnit.bottom);
	//Rectangle(getMemDC(), _rcForMove.left, _rcForMove.top, _rcForMove.right, _rcForMove.bottom);

	renderField();
	renderHarbor();
	renderDebugInfo();
}

void ship::initForHarbor(string unitName)
{
	_shipName = unitName;
	char harborTopImageKey[128]		= "harbor_top_";
	char harborCenterImageKey[128]	= "harbor_center_";
	char harborBottomImageKey[128]	= "harbor_bottom_";
	char harborWaveImageKey[128]	= "harbor_wave_";
	
	strcat_s(harborTopImageKey, _shipName.c_str());
	strcat_s(harborCenterImageKey, _shipName.c_str());
	strcat_s(harborBottomImageKey, _shipName.c_str());
	strcat_s(harborWaveImageKey, _shipName.c_str());

	_harborTop		= IMAGEMANAGER->findImage(harborTopImageKey);
	_harborCenter	= IMAGEMANAGER->findImage(harborCenterImageKey);
	_harborBottom	= IMAGEMANAGER->findImage(harborBottomImageKey);
	_harborWave		= IMAGEMANAGER->findImage(harborWaveImageKey);

	_harborX = HARBOR_X;
	_harborY = HARBOR_Y;
}

void ship::initForField(string unitName)
{
	_shipName = unitName;
	char fieldTopFileName[128] = "";
	char fieldCenterFileName[128] = "";
	char fieldBottomFileName[128] = "";
	char fieldShadowFileName[128] = "";
	char fieldWaveFileName[128] = "";
	char fieldSinkFileName[128] = "";
	char fieldSinkShadowFileName[128] = "";

	char fieldLocationKey[128] = "image/ships/";
	strcat_s(fieldLocationKey, _shipName.c_str());
	strcat_s(fieldLocationKey, "/");

	char fieldTopImageKey[128]			= "field_top_";
	char fieldCenterImageKey[128]		= "field_center_";
	char fieldBottomImageKey[128]		= "field_bottom_";
	char fieldShadowImageKey[128]		= "field_shadow_";
	char fieldWaveImageKey[128]			= "field_wave_";
	char fieldSinkImageKey[128]			= "field_sink_";
	char fieldSinkShadowImageKey[128]	= "field_sinkshadow_";

	strcat_s(fieldTopImageKey, _shipName.c_str());
	strcat_s(fieldCenterImageKey, _shipName.c_str());
	strcat_s(fieldBottomImageKey, _shipName.c_str());
	strcat_s(fieldShadowImageKey, _shipName.c_str());
	strcat_s(fieldWaveImageKey, _shipName.c_str());
	strcat_s(fieldSinkImageKey, _shipName.c_str());
	strcat_s(fieldSinkShadowImageKey, _shipName.c_str());

	strcat_s(fieldTopFileName, fieldLocationKey);
	strcat_s(fieldCenterFileName, fieldLocationKey);
	strcat_s(fieldBottomFileName, fieldLocationKey);
	strcat_s(fieldShadowFileName, fieldLocationKey);
	strcat_s(fieldWaveFileName, fieldLocationKey);
	strcat_s(fieldSinkFileName, fieldLocationKey);
	strcat_s(fieldSinkShadowFileName, fieldLocationKey);

	strcat_s(fieldTopFileName, fieldTopImageKey);
	strcat_s(fieldCenterFileName, fieldCenterImageKey);
	strcat_s(fieldBottomFileName, fieldBottomImageKey);
	strcat_s(fieldShadowFileName, fieldShadowImageKey);
	strcat_s(fieldWaveFileName, fieldWaveImageKey);
	strcat_s(fieldSinkFileName, fieldSinkImageKey);
	strcat_s(fieldSinkShadowFileName, fieldSinkShadowImageKey);

	strcat_s(fieldTopFileName, ".bmp");
	strcat_s(fieldCenterFileName, ".bmp");
	strcat_s(fieldBottomFileName, ".bmp");
	strcat_s(fieldShadowFileName, ".bmp");
	strcat_s(fieldWaveFileName, ".bmp");
	strcat_s(fieldSinkFileName, ".bmp");
	strcat_s(fieldSinkShadowFileName, ".bmp");

	int imageWidth = DATABASE->getShipElementData(_shipName)->imageFieldWidth;
	int imageHeight = DATABASE->getShipElementData(_shipName)->imageFieldHeight;

	_fieldTop			= new image;
	_fieldCenter		= new image;
	_fieldBottom		= new image;
	_fieldShadow		= new image;
	_fieldWave			= new image;
	_fieldSink			= new image;
	_fieldSinkShadow	= new image;

	_fieldTop->init(fieldTopFileName, imageWidth, imageHeight, FIELD_NORMAL_FRAME_X, FIELD_NORMAL_FRAME_Y, true, TRANS_RGB);
	_fieldCenter->init(fieldCenterFileName, imageWidth, imageHeight, FIELD_NORMAL_FRAME_X, FIELD_NORMAL_FRAME_Y, true, TRANS_RGB);
	_fieldBottom->init(fieldBottomFileName, imageWidth, imageHeight, FIELD_NORMAL_FRAME_X, FIELD_NORMAL_FRAME_Y, true, TRANS_RGB);
	_fieldShadow->init(fieldShadowFileName, imageWidth, imageHeight, FIELD_NORMAL_FRAME_X, FIELD_NORMAL_FRAME_Y, true, TRANS_RGB);
	_fieldWave->init(fieldWaveFileName, 1800, 4824, 10, 36, true, TRANS_RGB);
	_fieldSink->init(fieldSinkFileName, imageWidth, imageHeight, FIELD_NORMAL_FRAME_X, FIELD_NORMAL_FRAME_Y, true, TRANS_RGB);
	_fieldSinkShadow->init(fieldSinkShadowFileName, imageWidth, imageHeight, FIELD_NORMAL_FRAME_X, FIELD_NORMAL_FRAME_Y, true, TRANS_RGB);
		
	for (int i = 0; i < _turretSize; i++)
	{
		turret* temp;
		temp = new turret;
		temp->init();
		temp->initTurret(_shipName, _currentX, _currentY, DATABASE->getShipElementData(_shipName)->fieldTurretDistance[i], _currentAngle);
		_vTurret.push_back(temp);
	}

	_destinationUI = new destinationUI;
	_destinationUI->init();
	_selectingUI = new selectingUI;
	_selectingUI->init();
}

void ship::initForInformation(string unitName)
{
	_shipName = unitName;
	_shipClass = DATABASE->getShipElementData(unitName)->shipClass;
	_shipDP = DATABASE->getShipElementData(unitName)->shipDP;
	_shipWeight = DATABASE->getShipElementData(unitName)->shipWeight;
	_shipDefenExTop = DATABASE->getShipElementData(unitName)->shipDefenExTop;
	_shipDefenPeTop = DATABASE->getShipElementData(unitName)->shipDefenPeTop;
	_shipDefenExBottom = DATABASE->getShipElementData(unitName)->shipDefenExBottom;
	_shipDefenPeBottom = DATABASE->getShipElementData(unitName)->shipDefenPeBottom;
	_shipInchTop = DATABASE->getShipElementData(unitName)->shipInchTop;
	_shipInchBottom = DATABASE->getShipElementData(unitName)->shipInchBottom;
	_shipRaderName = DATABASE->getShipElementData(unitName)->shipRaderName;
	_shipRange = DATABASE->getShipElementData(unitName)->shipRange;
	_shipAccuracy = DATABASE->getShipElementData(unitName)->shipAccuracy;
	_shipEngineName = DATABASE->getShipElementData(unitName)->shipEngineName;
	_shipEnginePower = DATABASE->getShipElementData(unitName)->shipEnginePower;
	_shipMinSpeed = DATABASE->getShipElementData(unitName)->shipMinSpeed;
	_shipMaxSpeed = DATABASE->getShipElementData(unitName)->shipMaxSpeed;
	_turretSize = DATABASE->getShipElementData(unitName)->turretSize;
}

void ship::setUpField(float x, float y)
{
	_currentX = x;
	_currentY = y;
	_bSetUpField = true;
}

void ship::setUpTarget(float targetX, float targetY)
{
	_targetX = targetX;
	_targetY = targetY;
}

void ship::setUpHarbor(float harborX, float harborY)
{
	_harborX = harborX;
	_harborY = harborY;
}

void ship::functionCameraLeft(int cameraSpeed)
{
	_currentX += cameraSpeed;
	_targetX += cameraSpeed;
	_destinationUI->functionCameraLeft(cameraSpeed);
	_selectingUI->functionCameraLeft(cameraSpeed);
}

void ship::functionCameraRight(int cameraSpeed)
{
	_currentX -= cameraSpeed;
	_targetX -= cameraSpeed;
	_destinationUI->functionCameraRight(cameraSpeed);
	_selectingUI->functionCameraRight(cameraSpeed);
}

void ship::functionCameraUp(int cameraSpeed)
{
	_currentY += cameraSpeed;
	_targetY += cameraSpeed;
	_destinationUI->functionCameraUp(cameraSpeed);
	_selectingUI->functionCameraUp(cameraSpeed);
}

void ship::functionCameraDown(int cameraSpeed)
{
	_currentY -= cameraSpeed;
	_targetY -= cameraSpeed;
	_destinationUI->functionCameraDown(cameraSpeed);
	_selectingUI->functionCameraDown(cameraSpeed);
}

void ship::updateDestination()
{
	if (_bDestination)
	{
		_destinationUI->setReInit();
		_destinationUI->setDestPos(_currentX, _currentY);		
		_bDestination = false;
	}
	

	_destinationUI->update();
}

void ship::updateInterTargetXY()
{
	if (!_bDestination)
	{
		if (PtInRect(&_rcForMove, PointMake(_targetX, _targetY)))
		{
			_stateMovement = SHIP_ORDER_MOVEMENT_STOP;
			_targetSpeed = 0;
			_targetX += cosf(_currentAngle) * 10000;
			_targetY += -sinf(_currentAngle) * 10000;
			_bDestination = true;
			_destinationUI->setShow();
		}
	}
}

void ship::renderField()
{
	if (!getOnWindowScreen(&_rcUnit)) return;
	
	//if (_fieldWave) _fieldWave->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldWave->getFrameX(), _fieldWave->getFrameY());
	//if (_fieldBottom) _fieldBottom->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldBottom->getFrameX(), _fieldBottom->getFrameY());
	//if (_fieldCenter) _fieldCenter->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldCenter->getFrameX(), _fieldCenter->getFrameY());
	//if (_fieldTop) _fieldTop->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _fieldTop->getFrameX(), _fieldTop->getFrameY());

	//if (_vTurret.size() > 0)
	//{
	//	for (int i = 0; i < _turretSize; i++)
	//	{
	//		_vTurret[i]->render();
	//	}
	//}	
	if (_bSelected) _selectingUI->render();

	vector<SHIP_RENDER_SEQUENCE> shipSequence;
	if (_vTurret.size() > 0)
	{
		for (int i = 0; i < _turretSize; i++)
		{
			if (_vTurret[i]->getTurretPos().y > _rcUnit.top + (_rcUnit.bottom - _rcUnit.top) / 2)
			{
				shipSequence.push_back(SHIP_RENDER_SEQUENCE_TURRET);
				continue;
			}
		}
	}

	shipSequence.push_back(SHIP_RENDER_SEQUENCE_WAVE);
	shipSequence.push_back(SHIP_RENDER_SEQUENCE_BOTTOM);
	shipSequence.push_back(SHIP_RENDER_SEQUENCE_CENTER);
	shipSequence.push_back(SHIP_RENDER_SEQUENCE_TOP);

	if (_vTurret.size() > 0)
	{
		for (int i = 0; i < _turretSize; i++)
		{
			if (_vTurret[i]->getTurretPos().y < _rcUnit.top + (_rcUnit.bottom - _rcUnit.top) / 2)
			{
				shipSequence.push_back(SHIP_RENDER_SEQUENCE_TURRET);
				continue;
			}
		}
	}

	//SHIP_RENDER_SEQUENCE_TOP, SHIP_RENDER_SEQUENCE_CENTER, SHIP_RENDER_SEQUENCE_BOTTOM,
	//SHIP_RENDER_SEQUENCE_SHADOW, SHIP_RENDER_SEQUENCE_WAVE, SHIP_RENDER_SEQUENCE_TURRET
	int turretNum = 0;

	//if (RadianToDegree(_currentAngle) >= 0 && RadianToDegree(_currentAngle) <= 180) turretNum = _turretSize - 1;
	//else turretNum = 0;

	int size = shipSequence.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (shipSequence[i] == SHIP_RENDER_SEQUENCE_TOP)
		{
			if (_fieldTop) _fieldTop->frameRender(getBattleDC(), _rcUnit.left, _rcUnit.top, _fieldTop->getFrameX(), _fieldTop->getFrameY());
			continue;
		}
		else if (shipSequence[i] == SHIP_RENDER_SEQUENCE_CENTER)
		{
			if (_fieldCenter) _fieldCenter->frameRender(getBattleDC(), _rcUnit.left, _rcUnit.top, _fieldCenter->getFrameX(), _fieldCenter->getFrameY());
			continue;
		}
		else if (shipSequence[i] == SHIP_RENDER_SEQUENCE_BOTTOM)
		{
			if (_fieldBottom) _fieldBottom->frameRender(getBattleDC(), _rcUnit.left, _rcUnit.top, _fieldBottom->getFrameX(), _fieldBottom->getFrameY());
			continue;
		}
		else if (shipSequence[i] == SHIP_RENDER_SEQUENCE_WAVE)
		{
			if (_fieldWave) _fieldWave->frameRender(getBattleDC(), _rcUnit.left, _rcUnit.top, _fieldWave->getFrameX(), _fieldWave->getFrameY());
			continue;
		}
		else if (shipSequence[i] == SHIP_RENDER_SEQUENCE_TURRET)
		{
			_vTurret[turretNum]->render();
			//if (RadianToDegree(_currentAngle) >= 0 && RadianToDegree(_currentAngle) <= 180) turretNum--;
			//else turretNum++;
			turretNum++;
			continue;
		}
	}
	

	_destinationUI->render();
}

void ship::renderHarbor()
{
	if (_harborBottom) _harborBottom->render(getMemDC(), _rcUnit.left, _rcUnit.top);
	if (_harborCenter) _harborCenter->render(getMemDC(), _rcUnit.left, _rcUnit.top);
	if (_harborTop) _harborTop->render(getMemDC(), _rcUnit.left, _rcUnit.top);
	if (_harborWave) _harborWave->frameRender(getMemDC(), _rcUnit.left, _rcUnit.top, _harborWave->getFrameX(), _harborWave->getFrameY());
}

void ship::renderDebugInfo()
{
#ifdef _DEBUG

	if (_bSelected)
	{
		char buffer[128];
		sprintf_s(buffer, "current Angle : %.1f", RadianToDegree(_currentAngle));
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top, buffer, strlen(buffer));
		sprintf_s(buffer, "target Angle : %.1f", RadianToDegree(_targetAngle));
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 15, buffer, strlen(buffer));

		sprintf_s(buffer, "currentX : %.1f, currentY : %.1f", _currentX, _currentY);
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 30, buffer, strlen(buffer));
		sprintf_s(buffer, "targetX : %.1f, targetY : %.1f", _targetX, _targetY);
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 45, buffer, strlen(buffer));

		sprintf_s(buffer, "current Speed : %.1f", _currentSpeed);
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 60, buffer, strlen(buffer));
		sprintf_s(buffer, "target Speed : %.1f", _targetSpeed);
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 75, buffer, strlen(buffer));

		sprintf_s(buffer, "frame X : %d", _frameX);
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 90, buffer, strlen(buffer));

		sprintf_s(buffer, "tAngle - cAngle = %.1f", RadianToDegree(_targetAngle - _currentAngle));
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 105, buffer, strlen(buffer));

		sprintf_s(buffer, "alpha : %.1f, beta : %.1f", RadianToDegree(_inverseAngle), RadianToDegree(_reverseAngle));
		TextOut(getMemDC(), _rcUnit.right, _rcUnit.top + 120, buffer, strlen(buffer));

		//Target POSITION RECT
		RECT rc = RectMakeCenter(_targetX, _targetY, 50, 50);
		//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	}

#endif // _DEBUG
}

void ship::updateMovement()
{
	switch (_stateMovement)
	{
	case SHIP_ORDER_MOVEMENT_FAST:
		if (_currentSpeed < _targetSpeed) _currentSpeed += SHIP_CHANGE_SPEED;
		break;
	case SHIP_ORDER_MOVEMENT_PARALLEL:
		if (_currentSpeed < _targetSpeed) _currentSpeed += SHIP_CHANGE_SPEED;
		if (_currentSpeed > _targetSpeed) _currentSpeed -= SHIP_CHANGE_SPEED;
		break;
	case SHIP_ORDER_MOVEMENT_STOP:
		if (_currentSpeed > _targetSpeed) _currentSpeed -= SHIP_CHANGE_SPEED;
		break;
	case SHIP_ORDER_MOVEMENT_SLOW:
		if (_currentSpeed < _targetSpeed) _currentSpeed += SHIP_CHANGE_SPEED;
		break;
	default:
		break;
	}
}

void ship::updateAngle()
{
	//_inverseAngle : 각도를 올려서 타겟 앵글로 가기 위한 각도 변화량
	//_reverseAngle : 각도를 내려서 타겟 앵글로 가기 위한 각도 변화량
	//_currentAngle : 현재 함선의 앵글 값
	//_targetAngle	: 현재 좌표 지점으로부터의 타겟 지점 앵글 값

	if (fabsf(_currentAngle - _targetAngle) < ANGLE_FIXVALUE) return;	

	//if (_currentAngle - _targetAngle > PI)
	//{
	//	_currentAngle += SHIP_CHANGE_ANGLE;
	//}
	//else
	//{
	//	_currentAngle -= SHIP_CHANGE_ANGLE;
	//}
	
	if (_inverseAngle > PI2) _inverseAngle -= PI2;
	
	if (_targetAngle < DegreeToRadian(90))
	{
		_inverseAngle = _targetAngle;
		_reverseAngle = fabsf(DegreeToRadian(360) - _inverseAngle);
		if (_reverseAngle > _inverseAngle)
		{
			_currentAngle += SHIP_CHANGE_ANGLE;
		}
		else
		{
			_currentAngle -= SHIP_CHANGE_ANGLE;
		}
	}
	else if (_targetAngle > DegreeToRadian(270))
	{
		_inverseAngle = _targetAngle;
		_reverseAngle = fabsf(DegreeToRadian(360) - _inverseAngle);
		if (_reverseAngle > _inverseAngle)
		{
			_currentAngle += SHIP_CHANGE_ANGLE;
		}
		else
		{
			_currentAngle -= SHIP_CHANGE_ANGLE;
		}
	}
	else
	{
		if (_targetAngle - _currentAngle > 0)
		{
			_currentAngle += SHIP_CHANGE_ANGLE;
		}
		else
		{
			_currentAngle -= SHIP_CHANGE_ANGLE;
		}
	}

	if (_currentAngle > PI2 || _currentAngle < 0) _currentAngle = PI2 - _currentAngle;
}

void ship::updateTurret()
{
	if (_vTurret.size() > 0)
	{
		for (int i = 0; i < _turretSize; i++)
		{
			_vTurret[i]->setShipPos(_currentX, _currentY, _currentAngle);
			_vTurret[i]->update();
		}
	}
	
}

void ship::orderMovement(SHIP_ORDER_MOVEMENT_STATE orderMovement, float targetX, float targetY)
{
	_stateMovement = orderMovement;
	_targetX = targetX;
	_targetY = targetY;
	_bDestination = false;

	switch (_stateMovement)
	{
	case SHIP_ORDER_MOVEMENT_FAST:
		_targetSpeed = _shipMaxSpeed;
		break;
	case SHIP_ORDER_MOVEMENT_SLOW:
		_targetSpeed = _shipMaxSpeed / 2;
		break;
	case SHIP_ORDER_MOVEMENT_STOP:
		_targetSpeed = 0;
		break;
	default:
		break;
	}
}

void ship::orderMovement(SHIP_ORDER_MOVEMENT_STATE orderMovement, float targetX, float targetY, int speed)
{
	_stateMovement = orderMovement;
	_targetX = targetX;
	_targetY = targetY;
	_bDestination = false;

	switch (_stateMovement)
	{
	case SHIP_ORDER_MOVEMENT_FAST:
		_targetSpeed = _shipMaxSpeed;
		break;
	case SHIP_ORDER_MOVEMENT_SLOW:
		_targetSpeed = _shipMaxSpeed / 2;
		break;
	case SHIP_ORDER_MOVEMENT_PARALLEL:
		_targetSpeed = speed;
		break;
	case SHIP_ORDER_MOVEMENT_STOP:
		_targetSpeed = 0;
		break;
	default:
		break;
	}
}
