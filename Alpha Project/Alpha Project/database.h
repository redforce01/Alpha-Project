#pragma once

#include "singletonBase.h"

#include <vector>
#include <map>

class soundData;

class UnitAvailability
{
public:
	string unitName;
	string shipClass;
	int unitAvailability;
	int callInCost;
	
	
	UnitAvailability() {};
	~UnitAvailability() {};
};

class bulletElements
{
public:
	string bulletName;
	string bulletImageKey;
	int imageWidth;
	int imageHeight;
	int maxFrameX;
	int maxFrameY;
	
	bulletElements() {};
	~bulletElements() {};
};

#define BASIC_TURRET_INTERPOLATE (36 * 2)
class turretElements
{
public:
	string turretName;
	string turretImageKey;
	int imageWidth;
	int imageHeight;
	int maxFrameX;
	int maxFrameY;

	string cylinderImageKey;
	int cylinderImageWidth;
	int cylinderImageHeight;
	int cylinderMaxFrameX;
	int cylinderMaxFrameY;

	vector<int> interpolateX;
	vector<int> interpolateY;

	turretElements() {};
	~turretElements() {};
};

class shipElements
{
public:
	string shipName;
	string shipClass;

	int shipDP;
	int shipWeight;

	int shipDefenExTop;
	int shipDefenPeTop;
	int shipDefenExBottom;
	int shipDefenPeBottom;

	float shipInchTop;
	float shipInchBottom;

	string shipRaderName;
	int shipRange;
	int shipAccuracy;

	string shipEngineName;
	int shipEnginePower;
	int shipMinSpeed;
	int shipMaxSpeed;

	string imageFieldLocation;
	int imageFieldWidth;
	int imageFieldHeight;

	string imageHarborLocation;
	int imageHarborWidth;
	int imageHarborHeight;

	int turretSize;
	vector<int> fieldTurretDistance;

	shipElements() {};
	~shipElements() {};
};

class database : public singletonBase<database>
{
private:
	typedef vector<string> arrBulletElements;
	typedef vector<string>::iterator iterBulletElements;
	typedef map<string, bulletElements*> arrBulletElement;
	typedef map<string, bulletElements*>::iterator iterBulletElement;


	typedef vector<string> arrShipElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, shipElements*> arrShipElement;
	typedef map<string, shipElements*>::iterator iterShipElement;

	typedef vector<string> arrShipList;
	typedef vector<string>::iterator iterShipList;
	//typedef map<string, shipElements*> arrShipListElement;
	//typedef map<string, shipElements*>::iterator iterShipListElement;

	typedef vector<string> arrTurretElements;
	typedef vector<string>::iterator iterTurretElements;
	typedef map<string, turretElements*> arrTurretElement;
	typedef map<string, turretElements*>::iterator iterTurretElement;

	typedef vector<string> arrAvailableElements;
	typedef vector<string>::iterator iterAvailableElements;
	typedef map<string, UnitAvailability*> arrAvailableElement;
	typedef map<string, UnitAvailability*>::iterator iterAvailableElement;

	typedef vector<string> arrSoundElements;
	typedef vector<string>::iterator iterSoundElements;
	typedef map<string, soundData*> arrSoundElement;
	typedef map<string, soundData*>::iterator iterSoundElement;

private:
	arrBulletElement _mTotalBulletElement;
	arrShipElement _mTotalShipElement;
	arrShipList _mTotalShipList;
	arrTurretElement _mTotalTurretList;
	arrAvailableElement _mTotalAvailableList;

	arrSoundElement _mTotalSoundElement;
public:
	database();
	~database();

	HRESULT init();
	void release();

	void loadShipData(string name);
	void loadShipList(string name);
	void loadTurretData(string name);

	void loadAvailability(string name);

	bulletElements* getBulletElementData(string str) { return _mTotalBulletElement.find(str)->second; }
	shipElements* getShipElementData(string str) { return _mTotalShipElement.find(str)->second; }
	arrShipList getShipList() { return _mTotalShipList; }
	turretElements* getTurretList(string str) { return _mTotalTurretList.find(str)->second; }
	arrAvailableElement getAvailableList() { return _mTotalAvailableList; }

	soundData* getSoundData(string str) { return _mTotalSoundElement.find(str)->second; }	
	
};