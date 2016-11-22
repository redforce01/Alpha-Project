#pragma once

#include "gameNode.h"

#include "titleScene.h"
#include "LobbyScene.h"
#include "shipyardScene.h"
#include "worldMapScene.h"
#include "battleScene.h"

#include "startLoading.h"

#include "TestScene.h"
#include "mouseCursor.h"

class gameStudy : public gameNode
{
private:
	mouseCursor* _mouseCursor;

public:
	gameStudy();
	virtual ~gameStudy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

