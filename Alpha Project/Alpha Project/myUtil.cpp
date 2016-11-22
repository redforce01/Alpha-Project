#include "stdafx.h"
#include "myUtil.h"

namespace MY_CUSTOM_UTIL
{
	string getShipClass(UNIT_CLASS unitClass)
	{
		switch (unitClass)
		{
		case FF: return "FF";
		case DD: return "DD";
		case CL: return "CL";
		case CV: return "CV";
		case BB: return "BB";
		default:
			break;
		}
	}
	
	UNIT_CLASS getShipClass(string unitClass)
	{
		string str = unitClass;
		if (strcmp(str.c_str(), "FF")) return FF;
		if (strcmp(str.c_str(), "DD")) return DD;
		if (strcmp(str.c_str(), "CL")) return CL;
		if (strcmp(str.c_str(), "CV")) return CV;
		if (strcmp(str.c_str(), "BB")) return BB;
		
	}

	bool getOnWindowScreen(RECT * rc)
	{
		if (rc->left < WINSIZEX && rc->right > 0
			&& rc->top < WINSIZEY && rc->bottom > 0) return true;

		return false;
	}
	float RadianToDegree(float rad)
	{
		return rad * 180 / PI;
	}
	float DegreeToRadian(float degree)
	{
		return degree * PI / 180;
	}


	HDC makeBlackAndWhite(HDC hdc, int startX, int startY, int endX, int endY)
	{
		LPVOID bits;
		int bytePerLine;
		BITMAPINFO* bitMapInfo;
		HDC hdcTemp;
		hdcTemp = CreateCompatibleDC(hdc);
		BITMAPINFO bitmap;
		BYTE* bitPointer;
		bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
		bitmap.bmiHeader.biWidth = WINSIZEX;
		bitmap.bmiHeader.biHeight = WINSIZEY;
		bitmap.bmiHeader.biPlanes = 1;
		bitmap.bmiHeader.biBitCount = 24;
		bitmap.bmiHeader.biCompression = BI_RGB;
		bitmap.bmiHeader.biSizeImage = WINSIZEX * 4 * WINSIZEY;
		bitmap.bmiHeader.biClrUsed = 0;
		bitmap.bmiHeader.biClrImportant = 0;
		HBITMAP hBitmap = CreateDIBSection(hdcTemp, &bitmap, DIB_RGB_COLORS, (void**)(&bitPointer), NULL, NULL);
		HBITMAP hOldBitmap;
		hOldBitmap = (HBITMAP)SelectObject(hdcTemp, hBitmap);
		BitBlt(hdcTemp, 0, 0, WINSIZEX, WINSIZEY, hdc, 0, 0, SRCCOPY);

		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(bmi));
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader); //버전확인용
		GetDIBits(hdcTemp, hBitmap, 0, 0, NULL, &bmi, DIB_RGB_COLORS);

		bitMapInfo = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)];
		memcpy(bitMapInfo, &bmi, sizeof(bmi.bmiHeader));
		bytePerLine = bmi.bmiHeader.biBitCount / 8 * bmi.bmiHeader.biWidth;
		bytePerLine = (bytePerLine + 3) & ~3;
		bits = new char[bytePerLine * abs(bmi.bmiHeader.biHeight)];
		bitMapInfo->bmiHeader.biHeight = abs(bmi.bmiHeader.biHeight) * -1;
		GetDIBits(hdcTemp, hBitmap, 0, abs(bmi.bmiHeader.biHeight), bits, bitMapInfo, DIB_RGB_COLORS);

		for (int x = startX; x < endX; x = x + 1)
		{
			for (int y = startY; y < endY; y = y + 1)
			{
				DWORD dw = ((DWORD*)bits)[x + (y * (bytePerLine / sizeof(DWORD)))];
				COLORREF color = ((dw & 0x000000FF) << 24) + (dw & 0x0000FF00) + ((dw & 0x00FF0000) >> 24);
				int red;
				int green;
				int blue;
				red = GetRValue(color);
				green = GetGValue(color);
				blue = GetBValue(color);
				int blackAndWhite = (red + green + blue) / 3;
				color = RGB(blackAndWhite, blackAndWhite, blackAndWhite);
				((DWORD*)bits)[x + (y * (bytePerLine / sizeof(DWORD)))] = color;

			}
		}
		SetDIBits(hdcTemp, hBitmap, 0, abs(bmi.bmiHeader.biHeight), bits, bitMapInfo, DIB_RGB_COLORS);
		BitBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, hdcTemp, 0, 0, SRCCOPY);

		SelectObject(hdcTemp, hOldBitmap);
		DeleteObject(hBitmap);
		delete bits;

		return hdc;
	}
}