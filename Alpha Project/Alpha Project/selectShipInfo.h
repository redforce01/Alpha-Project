#pragma once
#include "gameNode.h"
class selectShipInfo : public gameNode
{
private:
	image* _infoGuide;
	RECT _rcInfoGuide;	
	image* _infoText;
	RECT _rcInfoText;
	image* _infoReload;
	image* _infoReloadBack;
	RECT _rcinfoReload;

	float _guideX, _guideY;

	float _reloadTime;

public:
	selectShipInfo();
	~selectShipInfo();

	HRESULT init();
	void release();
	void update();
	void render();

	void setGuidePos(POINT pos) { _guideX = pos.x, _guideY = pos.y; }
};

