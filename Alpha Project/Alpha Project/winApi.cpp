// winApi.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

/* ==== 함수 프로토타입 선언 ===== */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	//MSG : 운영체제에서 발행하는 메시지 정보를 저장하기 위한 구조체
	MSG message;

	//WNDCLASS : 윈도우의 정보를 저장하기 위한 구조체
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

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 생성
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

	//화면에 윈도우 보여준다
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_gs.init()))
	{
		//실패하면 바로 종료 시키자
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
	//메시지 큐에 메시지가 있으면 메시지 처리...
	while (GetMessage(&message, 0, 0, 0)) //일반 프로그램용
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