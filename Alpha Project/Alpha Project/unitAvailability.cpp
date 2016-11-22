#include "stdafx.h"
#include "unitAvailability.h"


unitAvailability::unitAvailability()
{
}


unitAvailability::~unitAvailability()
{
}

HRESULT unitAvailability::init()
{
	UNIT_CLASS type;

	arrUnitCount* availableFF = new arrUnitCount;
	arrUnitCount* availableDD = new arrUnitCount;
	arrUnitCount* availableCL = new arrUnitCount;
	arrUnitCount* availableCA = new arrUnitCount;
	arrUnitCount* availableCV = new arrUnitCount;

	_vAvailableList.insert(pair<UNIT_CLASS, arrUnitCount*>(FF, availableFF));
	_vAvailableList.insert(pair<UNIT_CLASS, arrUnitCount*>(DD, availableDD));
	_vAvailableList.insert(pair<UNIT_CLASS, arrUnitCount*>(CL, availableCL));
	_vAvailableList.insert(pair<UNIT_CLASS, arrUnitCount*>(CV, availableCA));
	_vAvailableList.insert(pair<UNIT_CLASS, arrUnitCount*>(BB, availableCV));

	for (unsigned int i = 0; i < DATABASE->getShipList().size(); i++)
	{
		

		if ( getShipClass( DATABASE->getAvailableList().find( DATABASE->getShipList()[i])->second->shipClass ) == FF) type = FF;
		else if ( getShipClass(DATABASE->getAvailableList().find(DATABASE->getShipList()[i])->second->shipClass) == DD) type = DD;
		else if ( getShipClass( DATABASE->getAvailableList().find( DATABASE->getShipList()[i])->second->shipClass ) == CL) type = CL;
		else if ( getShipClass( DATABASE->getAvailableList().find( DATABASE->getShipList()[i])->second->shipClass ) == CV) type = CV;
		else if ( getShipClass( DATABASE->getAvailableList().find( DATABASE->getShipList()[i])->second->shipClass ) == BB) type = BB;

		tagUNIT_AVAILABILITY temp;
		ZeroMemory(&temp, sizeof(tagUNIT_AVAILABILITY));

		temp.unitName = DATABASE->getAvailableList().find(DATABASE->getShipList()[i])->second->unitName;
		temp.callInCost = DATABASE->getAvailableList().find(DATABASE->getShipList()[i])->second->callInCost;
		temp.unitAvailability = DATABASE->getAvailableList().find(DATABASE->getShipList()[i])->second->unitAvailability;

		_viAvailableList = _vAvailableList.find(type);
		_viAvailableList->second->insert(pair<string, tagUNIT_AVAILABILITY>(temp.unitName, temp));
	}


	return S_OK;
}

void unitAvailability::release()
{
}
