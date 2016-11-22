#pragma once
#include "gameNode.h"

class mapTile : public gameNode
{
public:
	image* _tile;
	RECT _rcTile;
	float _x, _y;
	BATTLE_TILE_TYPE _type;

public:
	mapTile();
	~mapTile();
};

