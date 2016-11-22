// winApi.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "gameStudy.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
bool _leftButtonDown = false;
bool _rightButtonDown = false;

int _zoomDeltaX = 0;
int _zoomDeltaY = 0;
//int _sourX = 0;
//int _sourY = 0;

gameStudy _gs;

/* ==== �Լ� ������Ÿ�� ���� ===== */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//MSG : �ü������ �����ϴ� �޽��� ������ �����ϱ� ���� ����ü
	MSG message;

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);               
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);             
	wndClass.hInstance = hInstance;                  
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;                      
	wndClass.lpszMenuName = NULL;                             
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,    
		WINNAME,    
		WINSTYLE,   
		WINSTARTX,  
		WINSTARTY,  
		WINSIZEX,   
		WINSIZEY,   
		NULL,       
		(HMENU)NULL,
		hInstance,  
		NULL);      

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_gs.init()))
	{
		//�����ϸ� �ٷ� ���� ��Ű��
		return 0;
	}

	while (true)
	{
		if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.f);
			_gs.update();
			_gs.render();
		}
	}

	/*
	//�޽��� ť�� �޽����� ������ �޽��� ó��...
	while (GetMessage(&message, 0, 0, 0)) //�Ϲ� ���α׷���
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/

	_gs.release();

	_CrtMemDumpAllObjectsSince(0);

	return message.wParam;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _gs.MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left),
		(rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}