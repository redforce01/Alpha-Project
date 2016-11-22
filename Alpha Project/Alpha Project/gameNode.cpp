#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}


HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);

		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		TXTDATA->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		DATABASE->init();
		ACTIONMANAGER->init();
		KEYANIMANAGER->init();
		NUMBERINGMANAGER->init();
		LOGCAT->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);

		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		DATABASE->release();
		DATABASE->releaseSingleton();
		ACTIONMANAGER->release();
		ACTIONMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		NUMBERINGMANAGER->release();
		NUMBERINGMANAGER->releaseSingleton();
		LOGCAT->release();
		LOGCAT->releaseSingleton();
	}

	//받아온 DC 해제 해주자
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render()
{

}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);

	switch (iMessage)
	{
	case WM_MOUSEWHEEL:
		if (zDelta > 0)
		{
			_zoomDeltaX += 16;
			_zoomDeltaY += 9;
			if (_zoomDeltaX > 0) _zoomDeltaX = 0;
			if (_zoomDeltaY > 0) _zoomDeltaY = 0;
		}
		if (zDelta < 0)
		{
			_zoomDeltaX -= 16;
			_zoomDeltaY -= 9;
			if (_zoomDeltaX < -480) _zoomDeltaX = -480;
			if (_zoomDeltaY < -270) _zoomDeltaY = -270;
		}
		break;

	case WM_LBUTTONDOWN:
		_leftButtonDown = true;
		break;

	case WM_LBUTTONUP:
		_leftButtonDown = false;
		break;

	case WM_RBUTTONDOWN:
		_rightButtonDown = true;
		break;

	case WM_RBUTTONUP:
		_rightButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		//case VK_ESCAPE:
		//	PostMessage(_hWnd, WM_DESTROY, 0, 0);
		//	break;
		default:
			break;
		}
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//윈도우 프로시져에서 처리되지 않은 나머지 메시지를 처리해준다
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}