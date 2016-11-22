#pragma once
#include "gameNode.h"
#include "progressBarA.h"
class shipInfoUI : public gameNode
{
private:
	image* _background;
	image* _contents;
	image* _frame;
	RECT _rcInfo;

	string _showShipName;
	bool _bHasShip;
	bool _bLoadData;

	string _shipName;
	string _shipClass;
	int _shipDP;
	int _shipWeight;

	int _shipDefenExTop;
	int _shipDefenPeTop;
	int _shipDefenExBottom;
	int _shipDefenPeBottom;

	float _shipInchTop;
	float _shipInchBottom;

	image* _rader;
	string _shipRaderName;
	int _shipRange;
	int _shipAccuracy;
	
	image* _engine;
	string _shipEngineName;
	int _shipEnginePower;
	int _shipMinSpeed;
	int _shipMaxSpeed;

	vector<image*> _vShipDP;
	vector<image*> _vShipWeight;
	vector<image*> _vShipDefenExtop;
	vector<image*> _vShipDefenPetop;
	vector<image*> _vShipDefenExBottom;
	vector<image*> _vShipDefenPeBottom;
	vector<image*> _vShipInchTop;
	vector<image*> _vShipInchBottom;
	vector<image*> _vShipRange;
	vector<image*> _vShipAccuracy;
	vector<image*> _vShipEnginePower;
	vector<image*> _vShipMinSpeed;
	vector<image*> _vShipMaxSpeed;

	progressBarA* _progressBarDP;
	progressBarA* _progressBarWeight;

	
public:
	shipInfoUI();
	~shipInfoUI();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void setHasShip(bool flag) { _bHasShip = flag; }
	void setChangeData(bool flag) { _bLoadData = flag; }
	void setShowShipName(string shipName) { _showShipName = shipName; }
	
};

