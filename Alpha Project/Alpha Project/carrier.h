#pragma once

#include "ship.h"

class carrier : public ship
{
public:
	carrier();
	~carrier();

	HRESULT init(const char* imageName, int x, int y);
	void release();
	void update();
	void render();

	void keyControl();
	void move();
};

