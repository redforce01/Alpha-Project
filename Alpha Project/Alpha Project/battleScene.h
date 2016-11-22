#pragma once
#include "gameNode.h"
#include "battleLoading.h"
#include "battleUI.h"
#include "battleMap.h"
#include "battleManager.h"

#include "unitAvailability.h"

class battleScene : public gameNode
{
private:
	battleLoading* _battleLoading;
	battleUI* _battleUI;
	battleMap* _battleMap;

	battleManager* _battleManager;

	unitAvailability* _unitAvailability;

public:
	battleScene();
	~battleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

