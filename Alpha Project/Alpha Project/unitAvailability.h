#pragma once

struct tagUNIT_AVAILABILITY
{
	string unitName;
	int unitAvailability;
	int callInCost;
};
class unitAvailability
{
private:
	typedef map<string, tagUNIT_AVAILABILITY> arrUnitCount;
	typedef map<string, tagUNIT_AVAILABILITY>::iterator iterUnitCount;

	typedef map<UNIT_CLASS, arrUnitCount*> arrUnits;
	typedef map<UNIT_CLASS, arrUnitCount*>::iterator iterUnits;

private:
	arrUnits	_vAvailableList;
	iterUnits	_viAvailableList;

public:
	unitAvailability();
	~unitAvailability();

	HRESULT init();
	void release();

	tagUNIT_AVAILABILITY getAvailableList(UNIT_CLASS type, string str) { return _vAvailableList.find(type)->second->find(str)->second; }
};

