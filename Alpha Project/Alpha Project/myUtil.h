#pragma once

namespace MY_CUSTOM_UTIL
{
	enum WORLDMAP_EVENT_TYPE
	{
		WORLDMAP_BATTLE, WORLDMAP_EVENT
	};

	enum BATTLE_TILE_TYPE
	{
		BATTLE_TILE_NULL, BATTLE_TILE_BLOCK
	};

	enum BATTLE_WIN_TYPE
	{
		BATTLE_VICTORY_POINT, BATTLE_ANNIHILATION
	};

	enum UNIT_TYPE
	{
		UNIT_PLAYER, UNIT_ENEMY
	};

	enum BATTLE_AREA_TYPE
	{
		BATTLE_AREA_NORMAL, BATTLE_AREA_PLAYER, BATTLE_AREA_ENEMY
	};

	enum UNIT_CLASS
	{
		FF, DD, CL, CA, CV, BB
	};

	enum SELECT_UNITCARD_TYPE
	{
		CARD_FF, CARD_DD, CARD_CL, CARD_CV, CARD_BB
	};

	enum SHIP_ORDER_MOVEMENT_STATE
	{
		SHIP_ORDER_MOVEMENT_FAST, SHIP_ORDER_MOVEMENT_STOP, SHIP_ORDER_MOVEMENT_PARALLEL,
		SHIP_ORDER_MOVEMENT_SLOW, SHIP_ORDER_MOVEMENT_NULL
	};

	enum ANGLE_DIRECTION
	{
		ANGLE_LT, ANGLE_LB, ANGLE_RT, ANGLE_RB
	};

	enum CAMERA_DIRECTION
	{
		CAMERA_DIRECTION_LT, CAMERA_DIRECTION_LB, CAMERA_DIRECTION_RT, CAMERA_DIRECTION_RB,
		CAMERA_DIRECTION_L, CAMERA_DIRECTION_R, CAMERA_DIRECTION_T, CAMERA_DIRECTION_B,
		CAMERA_DIRECTION_NULL, CAMERA_DIRECTION_STOP
	};

	enum RADAR_DOT_TYPE
	{
		RADAR_DOT_YELLOW, RADAR_DOT_RED,
		RADAR_DOT_BLUE, RADAR_DOT_MY
	};
	
	string getShipClass(UNIT_CLASS unitClass);
	UNIT_CLASS getShipClass(string unitClass);

	bool getOnWindowScreen(RECT *rc);

	float RadianToDegree(float rad);
	float DegreeToRadian(float degree);

	HDC makeBlackAndWhite(HDC hdc, int startX, int startY, int endX, int endY);
}
