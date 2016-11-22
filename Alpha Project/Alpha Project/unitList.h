#pragma once
#include "gameNode.h"

struct tagUnitCard
{
	RECT rc;
	image* unitCard;
	float x, y;
	string unitName;
	UNIT_CLASS unitClass;
	RECT rcName;

	int availability;
};
class unitList : public gameNode
{
private:
	vector<tagUnitCard> _vUnitList;
	vector<tagUnitCard>::iterator _viUnitList;

	int _listSize;
public:
	unitList();
	~unitList();

	HRESULT init(UNIT_CLASS unitClass);
	void release();
	void update();
	void render();

	vector<tagUnitCard> getUnitList() { return _vUnitList; }
	int getListSize() { return _listSize; }
};

