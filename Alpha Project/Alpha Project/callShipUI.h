#pragma once
#include "gameNode.h"
#include "button.h"

class callShipUI : public gameNode
{
private:
	button* _btnCallUnit;
	button* _btnCallFrigate;
	button* _btnCallDestroyer;
	button* _btnCallCruiser;
	button* _btnCallCarrier;
	button* _btnCallBattle;

	bool _callUnit;
	bool _callFrigate;
	bool _callDestroyer;
	bool _callCruiser;
	bool _callCarrier;
	bool _callBattle;

	SELECT_UNITCARD_TYPE _selectCardType;

public:
	callShipUI();
	~callShipUI();

	HRESULT init();
	void release();
	void update();
	void render();

	SELECT_UNITCARD_TYPE getSelectCardType() { return _selectCardType; }

	static void functionCallUnit(void *obj);
	static void functionCallFrigate(void *obj);
	static void functionCallDestroyer(void *obj);
	static void functionCallCruiser(void *obj);
	static void functionCallCarrier(void *obj);
	static void functionCallBattle(void *obj);

	bool getFlagUnit() { return _callUnit; }
	bool getFlagFrigate() { return _callFrigate; }
	bool getFlagDestroyer() { return _callDestroyer; }
	bool getFlagCruiser() { return _callCruiser; }
	bool getFlagCarrier() { return _callCarrier; }
	bool getFlagBattle() { return _callBattle; }

	void setFlagUnit(bool flag) { _callUnit = flag; }
	void setFlagFrigate(bool flag) { _callFrigate = flag; }
	void setFlagDestroyer(bool flag) { _callDestroyer = flag; }
	void setFlagCruiser(bool flag) { _callCruiser = flag; }
	void setFlagCarrier(bool flag) { _callCarrier = flag; }
	void setFlagBattle(bool flag) { _callBattle = flag; }
};

