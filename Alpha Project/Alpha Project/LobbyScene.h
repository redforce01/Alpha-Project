#pragma once
#include "gameNode.h"
#include "button.h"
#include "lobbyUI.h"
class LobbyScene : public gameNode
{
private:
	image* _background;
	lobbyUI* _lobbyUI;

public:
	LobbyScene();
	~LobbyScene();

	HRESULT init();
	void release();
	void update();
	void render();
};