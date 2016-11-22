#include "stdafx.h"
#include "database.h"

#include "soundData.h"

database::database()
{
}


database::~database()
{
}

HRESULT database::init()
{
	loadShipData("database/shipData(Test).txt");
	loadShipList("database/shipList.txt");
	loadTurretData("database/turretData.txt");
	loadAvailability("database/unitAvailable.txt");

	return S_OK;
}

void database::release()
{
	iterBulletElement mIter = _mTotalBulletElement.begin();

	for (; mIter != _mTotalBulletElement.end(); ++mIter)
	{
		SAFE_DELETE(mIter->second);
	}

	_mTotalBulletElement.clear();
}

void database::loadShipData(string name)
{
	//데이터 읽어온다
	arrShipElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	for (unsigned int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			shipElements* em = new shipElements;
			str = vTemp[i + 1];
			_mTotalShipElement.insert(pair<string, shipElements*>(vTemp[i + 1], em));
			if (i != 0) count += 37;
			continue;
		}

		iterShipElement mIter = _mTotalShipElement.find(str);
		if (i == count + 1) mIter->second->shipName = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->shipClass = vTemp[i].c_str();
		else if (i == count + 3) mIter->second->shipDP = atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->shipWeight = atoi(vTemp[i].c_str());

		else if (i == count + 5) mIter->second->shipDefenExTop = atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->shipDefenPeTop = atoi(vTemp[i].c_str());
		else if (i == count + 7) mIter->second->shipDefenExBottom = atoi(vTemp[i].c_str());
		else if (i == count + 8) mIter->second->shipDefenPeBottom = atoi(vTemp[i].c_str());
		else if (i == count + 9) mIter->second->shipInchTop = (float)atof(vTemp[i].c_str());
		else if (i == count + 10) mIter->second->shipInchBottom = (float)atof(vTemp[i].c_str());

		else if (i == count + 11) mIter->second->shipRaderName = vTemp[i].c_str();
		else if (i == count + 12) mIter->second->shipRange = atoi(vTemp[i].c_str());
		else if (i == count + 13) mIter->second->shipAccuracy = atoi(vTemp[i].c_str());

		else if (i == count + 14) mIter->second->shipEngineName = vTemp[i].c_str();
		else if (i == count + 15) mIter->second->shipEnginePower = atoi(vTemp[i].c_str());
		else if (i == count + 16) mIter->second->shipMinSpeed = atoi(vTemp[i].c_str());
		else if (i == count + 17) mIter->second->shipMaxSpeed = atoi(vTemp[i].c_str());

		else if (i == count + 18) mIter->second->imageFieldLocation = vTemp[i].c_str();
		else if (i == count + 19) mIter->second->imageFieldWidth = atoi(vTemp[i].c_str());
		else if (i == count + 20) mIter->second->imageFieldHeight = atoi(vTemp[i].c_str());

		else if (i == count + 21) mIter->second->imageHarborLocation = vTemp[i].c_str();
		else if (i == count + 22) mIter->second->imageHarborWidth = atoi(vTemp[i].c_str());
		else if (i == count + 23) mIter->second->imageHarborHeight = atoi(vTemp[i].c_str());

		else if (i == count + 24) mIter->second->turretSize = atoi(vTemp[i].c_str());		

		else if (i == count + 25) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 26) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 27) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 28) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 29) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 30) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));

		else if (i == count + 31) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 32) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 33) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 34) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 35) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
		else if (i == count + 36) mIter->second->fieldTurretDistance.push_back(atoi(vTemp[i].c_str()));
	}

	vTemp.clear();
}

void database::loadShipList(string name)
{
	arrShipList vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());
	
	string str;
	int count = 0;

	for (unsigned int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			_mTotalShipList.push_back(vTemp[i + 1]);
		}
	}

	vTemp.clear();
}

void database::loadTurretData(string name)
{
	//데이터 읽어온다
	arrTurretElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	for (unsigned int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			turretElements* em = new turretElements;
			str = vTemp[i + 1];
			_mTotalTurretList.insert(pair<string, turretElements*>(vTemp[i + 1], em));
			if (i != 0) count += 12;
			continue;
		}

		iterTurretElement mIter = _mTotalTurretList.find(str);
		if (i == count + 1) mIter->second->turretName = vTemp[i];
		else if (i == count + 2) mIter->second->turretImageKey= vTemp[i];
		else if (i == count + 3) mIter->second->imageWidth = atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->imageHeight = atoi(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->maxFrameX = atoi(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->maxFrameY = atoi(vTemp[i].c_str());

		else if (i == count + 7) mIter->second->cylinderImageKey = vTemp[i];
		else if (i == count + 8) mIter->second->cylinderImageWidth = atoi(vTemp[i].c_str());
		else if (i == count + 9) mIter->second->cylinderImageHeight = atoi(vTemp[i].c_str());
		else if (i == count + 10) mIter->second->cylinderMaxFrameX = atoi(vTemp[i].c_str());
		else if (i == count + 11) mIter->second->cylinderMaxFrameY = atoi(vTemp[i].c_str());
		
		////Turret No.1 _X
		//else if (i == count + 12) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 13) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 14) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 15) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 16) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 17) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 18) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 19) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 20) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 21) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 22) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 23) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 24) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 25) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 26) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 27) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 28) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 29) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 30) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 31) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 32) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 33) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 34) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 35) mIter->second->interpolateX.push_back(atoi(vTemp[i].c_str()));

		////Turret No.1 _Y
		//else if (i == count + 12) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 13) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 14) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 15) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 16) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 17) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 18) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 19) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 20) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 21) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 22) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 23) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 24) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 25) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 26) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 27) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 28) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 29) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 30) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 31) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 32) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 33) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 34) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
		//else if (i == count + 35) mIter->second->interpolateY.push_back(atoi(vTemp[i].c_str()));
	}

	vTemp.clear();
}

void database::loadAvailability(string name)
{
	arrAvailableElements vTemp;
	vTemp = TXTDATA->txtLoad(name.c_str());

	string str;
	int count = 0;

	for (unsigned int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			UnitAvailability* em = new UnitAvailability;
			str = vTemp[i + 1];
			_mTotalAvailableList.insert(pair<string, UnitAvailability*>(vTemp[i + 1], em));
			if (i != 0) count += 5;
			continue;
		}

		iterAvailableElement mIter = _mTotalAvailableList.find(str);
		if (i == count + 1) mIter->second->unitName = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->shipClass = vTemp[i].c_str();
		else if (i == count + 3) mIter->second->unitAvailability = atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->callInCost = atoi(vTemp[i].c_str());
	}

	
	vTemp.clear();
}
