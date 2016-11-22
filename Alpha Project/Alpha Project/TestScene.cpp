#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::init()
{
	x1 = 300;
	y1 = 500;

	x2 = 700;
	y2 = 200;

	_character = IMAGEMANAGER->addFrameImage("test_character", "image/testing/character.bmp", 6720, 413, 60, 1, true, RGB(0, 0, 0));
	_rcCharacter = RectMakeCenter(CENTERX, CENTERY - 200, 1, 1);
	_frameTime = 0;
	_frame = 0;

	return S_OK;
}

void TestScene::release()
{
}

void TestScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) PostQuitMessage(0);

	float angle = getAngle(x1, y1, x2, y2);
	
	_rc1 = RectMakeCenter(x1, y1, 10, 10);
	_rc2 = RectMakeCenter(x2, y2, 10, 10);

	_frameTime++;
	if (_frameTime % 2 == 0)
	{
		_character->setFrameX(_frame);
		_frame++;
		if (_frame > _character->getMaxFrameX()) 
			_frame = 0;
	}
}

void TestScene::render()
{
	//char str[128];
	//sprintf_s(str, "%f", getAngle(x1, y1, x2, y2) * 90);
	//TextOut(getMemDC(), CENTERX, CENTERY, str, strlen(str));
	//Rectangle(getMemDC(), _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);
	//Rectangle(getMemDC(), _rc2.left, _rc2.top, _rc2.right, _rc2.bottom);


	//HPEN myPen, oldPen;
	//myPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
	//oldPen = (HPEN)SelectObject(getMemDC(), myPen);

	//TextOut(getMemDC(), x1, y1, "Rc1", 3);
	//TextOut(getMemDC(), x2, y2, "Rc2", 3);
	//MoveToEx(getMemDC(), x1, y1, 0);
	//LineTo(getMemDC(), x2, y2);

	//SelectObject(getMemDC(), oldPen);
	//DeleteObject(myPen);

	_character->frameRender(getMemDC(), _rcCharacter.left, _rcCharacter.top, _character->getFrameX(), _character->getFrameY());
}
