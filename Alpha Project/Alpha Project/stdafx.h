// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN //MFC�� �ƴ� ���� ���α׷��� ���
							//WIN32_LEAN_AND_MEAN�� ������ commdlg.h ���
							//�ʿ���� ��������� ��Ŭ��� ���� �ʰ� ���ش�.

#include <Windows.h>		//������ ������� ��Ŭ���
#include <stdio.h>			//���Ĵٵ� ����� ��� ��Ŭ��� (printf, scanf ���)
#include <tchar.h>			//�����쿡�� ����� ���ڿ� ��� ��� ��Ŭ���
							//MBCS (Multi Byte Character Set)
							//->������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ�
							//WBCS (Wide Byte Character Set)
							//->��� ���ڸ� 2����Ʈ�� ó��. �����ڵ� ���
#include <vector>
#include <map>


#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "myUtil.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "effectManager.h"
#include "sceneManager.h"
#include "database.h"
#include "actionManager.h"
#include "keyAnimationManager.h"
#include "soundManager.h"
#include "collision.h"
#include "numbering.h"

#include "debugLogCat.h"
#include <crtdbg.h>

using namespace MY_UTIL;
using namespace MY_CUSTOM_UTIL;

/* ===== �����ι� ===== */
#define WINNAME (LPTSTR)(TEXT("WinAPI"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX 1280
#define WINSIZEY 720
#define CENTERX (WINSIZEX / 2)
#define CENTERY (WINSIZEY / 2)
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) { delete (p);		(p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[] (p);		(p) = NULL;}}
#define SAFE_RELEASE(p)			{if(p) { (p)->release();	(p) = NULL;}}


//CUSTOM DEFINE LIST
#define TRANS_RGB RGB(0, 0, 0)
#define TILE_WIDTH 128
#define TILE_HEIGHT 64
#define CAMERA_SPEED 10
#define MINIMAP_GRID_X 10
#define MINIMAP_GRID_Y 5
#define UNITCARD_WIDTH 100
#define UNITCARD_HEIGHT 70

/* =========== �̱��� =========== */
#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define DATABASE database::getSingleton()
#define ACTIONMANAGER actionManager::getSingleton()
#define KEYANIMANAGER keyAnimationManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define NUMBERINGMANAGER numbering::getSingleton()
#define LOGCAT debugLogCat::getSingleton()

/* ===== ���� ���� ===== */
extern POINT _ptMouse;
extern HWND _hWnd;
extern HINSTANCE _hInstance;
extern bool _leftButtonDown;
extern bool _rightButtonDown;

extern int _zoomDeltaX;
extern int _zoomDeltaY;
//extern int _sourX;
//extern int _sourY;