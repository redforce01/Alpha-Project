#pragma once
#include <vector>

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void LineMake(HDC hdc, std::vector<POINT> vPt)
{
	std::vector<POINT>::iterator viPoint;
	int i = 0;
	for (viPoint = vPt.begin(); viPoint != vPt.end(); ++viPoint, i++)
	{
		if (i == 0) MoveToEx(hdc, viPoint->x, viPoint->y, NULL);
		else LineTo(hdc, viPoint->x, viPoint->y);
	}

	vPt.clear();
}
#define MUL(a) a * a

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
	return rc;
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline void IsoRender(HDC hdc, RECT rc)
{
	HPEN myPen, oldPen;
	myPen = CreatePen(1, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hdc, myPen);
	
	LineMake(hdc, (rc.right + rc.left) / 2, rc.top, rc.right, (rc.top + rc.bottom) / 2);	//12 -> 3
	LineMake(hdc, rc.right, (rc.top + rc.bottom) / 2, (rc.left + rc.right) / 2, rc.bottom);	//3 -> 6 
	LineMake(hdc, (rc.left + rc.right) / 2, rc.bottom, rc.left, (rc.top + rc.bottom) / 2);	//6 -> 9
	LineMake(hdc, rc.left, (rc.top + rc.bottom) / 2, (rc.right + rc.left) / 2, rc.top);		//9 -> 12

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}

inline void WorldIsoRender(HDC hdc, RECT rc)
{
	HPEN myPen, oldPen;
	myPen = CreatePen(1, 1, RGB(255, 255, 255));
	oldPen = (HPEN)SelectObject(hdc, myPen);

	rc.left = rc.left + 15;
	rc.top = rc.top;
	rc.right = rc.right + 30;
	rc.bottom = rc.bottom + 30;
	

	LineMake(hdc, (rc.right + rc.left) / 2, rc.top, rc.right, (rc.top + rc.bottom) / 2);
	LineMake(hdc, rc.right, (rc.top + rc.bottom) / 2, (rc.left + rc.right) / 2, rc.bottom);
	LineMake(hdc, (rc.left + rc.right) / 2, rc.bottom, rc.left, (rc.top + rc.bottom) / 2);
	LineMake(hdc, rc.left, (rc.top + rc.bottom) / 2, (rc.right + rc.left) / 2, rc.top);

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);
}