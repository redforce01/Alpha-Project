#include "stdafx.h"
#include "carrier.h"


carrier::carrier()
{
}


carrier::~carrier()
{
}

HRESULT carrier::init(const char * imageName, int x, int y)
{
	ship::init(imageName, x, y);

	return S_OK;
}

void carrier::release()
{
	ship::release();
}

void carrier::update()
{
	ship::update();
}

void carrier::render()
{
	ship::render();
}

void carrier::keyControl()
{
	if (KEYMANAGER->isStayKeyDown('A')) _angle += 0.06f;
	if (KEYMANAGER->isStayKeyDown('D')) _angle -= 0.06f;
	if (KEYMANAGER->isStayKeyDown('W')) _speed += 0.02f;
	if (KEYMANAGER->isStayKeyDown('S')) _speed -= 0.02f;
}

void carrier::move()
{
	int frame;

//	_angle = _angle + PI32;
	if (_angle > PI2) _angle -= PI2;

	if (_angle < 0) _angle += PI2;

	frame = int(_angle / PI16);
	_image->setFrameX(frame);

	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}


