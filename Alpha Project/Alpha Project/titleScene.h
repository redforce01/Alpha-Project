#pragma once
#include "gameNode.h"
#include "titleUI.h"

class titleScene : public gameNode
{
private:
	image* _background;
	RECT _rcBackground;

	image* _login;
	RECT _rcLogin;

	image* _ship;
	RECT _rcShip;
	
	image* _plane;
	RECT _rcPlane;
	int _nPlaneFrame;
	int _nPlaneTime;
	int _nPlaneImgNumber;
	bool _bShowPlane;
	int _nPlaneX;

	titleUI* _titleUI;

public:
	titleScene();
	~titleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

