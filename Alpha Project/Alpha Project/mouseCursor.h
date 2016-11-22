#pragma once
#include "gameNode.h"

#define CURSOR_NORMALIZE_X 23
#define CURSOR_NORMALIZE_Y 21
class mouseCursor : public gameNode
{
private:
	image* _cursorPyramid;
	image* _cursorCompass;
	image* _cursorCompassShadow;
	RECT _rcCursor;

	int _frame;
	int _frameTime;

public:
	mouseCursor();
	~mouseCursor();

	HRESULT init();
	void release();
	void update();
	void render();
};

