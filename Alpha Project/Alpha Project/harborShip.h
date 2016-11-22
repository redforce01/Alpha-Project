#pragma once
#include "gameNode.h"

#define ALPHA_CHANGE_SPEED 5
class harborShip : public gameNode
{
private:	
	image* _shipTop;
	image* _shipCenter;
	image* _shipBottom;

	RECT _rcShip;
	int _shipX, _shipY;
	
	vector<image*> _vTurret;
	vector<RECT> _vRcTurret;
	
	string _shipName;
	bool _bHasShip;	

public:
	bool _bChanged;
	float _alphaValue;

public:
	harborShip();
	~harborShip();

	HRESULT init();
	void relaese();
	void update();
	void render();

	void setShipName(string shipName) { _shipName = shipName; }
	void setHasShip(bool flag) { _bHasShip = flag; }
};

