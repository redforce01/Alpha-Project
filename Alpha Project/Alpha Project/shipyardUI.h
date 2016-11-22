#pragma once
#include "gameNode.h"
#include "shipInfoUI.h"
#include "topExtendUI.h"
#include "arrowUI.h"
#include "shipyardCtrlUI.h"
#include "harborShip.h"
class shipyardUI : public gameNode
{
private:
	shipInfoUI* _shipInfoUI;
	topExtendUI* _topExtendUI;
	shipyardCtrlUI* _shipyardCtrlUI;
	arrowUI* _arrowUI;

	harborShip* _harborShip;
private:
	int _shipListSize;
	vector<string> _vShipList;

	int _showShipNumber;


public:
	shipyardUI();
	~shipyardUI();

	HRESULT init();
	void release();
	void update();
	void render();
};

