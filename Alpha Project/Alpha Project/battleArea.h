#pragma once
#include "gameNode.h"

#define AREA_RADIAN_SIZE 500
class battleArea : public gameNode
{
private:
	image*	_areaFlag;
	RECT	_rcAreaFlag;
	int		_frame;
	int		_frameTime;

	RECT _rcArea;
	float _x, _y;

	BATTLE_AREA_TYPE _areaType;

public:
	battleArea();
	~battleArea();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

public:
	void InitArea(float x, float y, int flagNumber);

	void functionMoveLeft(int cameraSpeed);
	void functionMoveRight(int cameraSpeed);
	void functionMoveUp(int cameraSpeed);
	void functionMoveDown(int cameraSpeed);

public:
	void setAreaMaster(BATTLE_AREA_TYPE masterType);
};

