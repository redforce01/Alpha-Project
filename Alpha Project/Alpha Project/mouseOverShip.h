#pragma once
#include "gameNode.h"
class mouseOverShip : public gameNode
{
private:
	image*	_shipTop;
	image*	_shipCenter;
	image*	_shipBottom;

	RECT	_rcUnit;
	string	_unitName;
	float	_x, _y;
	int		_frame;

	bool _isSetUp;
	
public:
	mouseOverShip();
	~mouseOverShip();

	HRESULT init();
	void release();
	void update();
	void render();

	void setUnit(string unitName);
};

