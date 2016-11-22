#include "stdafx.h"
#include "callShipUI.h"


callShipUI::callShipUI()
{
}


callShipUI::~callShipUI()
{
}

HRESULT callShipUI::init()
{
	_btnCallUnit = new button;
	_btnCallFrigate = new button;
	_btnCallDestroyer = new button;
	_btnCallCruiser = new button;
	_btnCallCarrier = new button;
	_btnCallBattle = new button;

	_btnCallUnit->init("Unit", 20, 50, functionCallUnit, this, true);
	_btnCallFrigate->init("Frigate", 80, 50, functionCallFrigate, this, true);
	_btnCallDestroyer->init("Destroyer", 160, 50, functionCallDestroyer, this, true);
	_btnCallCruiser->init("Cruiser", 260, 50, functionCallCruiser, this, true);
	_btnCallCarrier->init("Carrier", 340, 50, functionCallCarrier, this, true);
	_btnCallBattle->init("Battle", 420, 50, functionCallBattle, this, true);

	_callUnit		= false;
	_callFrigate	= false;
	_callDestroyer	= false;
	_callCruiser	= false;
	_callCarrier	= false;
	_callBattle		= false;

	return S_OK;
}

void callShipUI::release()
{
	_btnCallUnit->release();
	_btnCallFrigate->release();
	_btnCallDestroyer->release();
	_btnCallCruiser->release();
	_btnCallCarrier->release();
	_btnCallBattle->release();

	SAFE_DELETE(_btnCallUnit);
	SAFE_DELETE(_btnCallFrigate);
	SAFE_DELETE(_btnCallDestroyer);
	SAFE_DELETE(_btnCallCruiser);
	SAFE_DELETE(_btnCallCarrier);
	SAFE_DELETE(_btnCallBattle);
}

void callShipUI::update()
{
	_btnCallUnit->update();
	if (_callUnit)
	{
		_btnCallFrigate->update();
		_btnCallDestroyer->update();
		_btnCallCruiser->update();
		_btnCallCarrier->update();
		_btnCallBattle->update();
	}
}

void callShipUI::render()
{
	_btnCallUnit->render();

	if (_callUnit)
	{
		_btnCallFrigate->render();
		_btnCallDestroyer->render();
		_btnCallCruiser->render();
		_btnCallCarrier->render();
		_btnCallBattle->render();
	}

}

void callShipUI::functionCallUnit(void * obj)
{
	callShipUI* _callShipUI = (callShipUI*)obj;
	if (!_callShipUI->_callUnit) _callShipUI->_callUnit = true;
	else if (_callShipUI->_callUnit) _callShipUI->_callUnit = false;
}

void callShipUI::functionCallFrigate(void * obj)
{
	callShipUI* _callShipUI = (callShipUI*)obj;
	_callShipUI->_callFrigate = true;
	_callShipUI->_callDestroyer = false;
	_callShipUI->_callCruiser = false;
	_callShipUI->_callCarrier = false;
	_callShipUI->_callBattle = false;

	_callShipUI->_selectCardType = CARD_FF;
}

void callShipUI::functionCallDestroyer(void * obj)
{
	callShipUI* _callShipUI = (callShipUI*)obj;
	_callShipUI->_callFrigate = false;
	_callShipUI->_callDestroyer = true;
	_callShipUI->_callCruiser = false;
	_callShipUI->_callCarrier = false;
	_callShipUI->_callBattle = false;

	_callShipUI->_selectCardType = CARD_DD;
}

void callShipUI::functionCallCruiser(void * obj)
{
	callShipUI* _callShipUI = (callShipUI*)obj;
	_callShipUI->_callFrigate = false;
	_callShipUI->_callDestroyer = false;
	_callShipUI->_callCruiser = true;
	_callShipUI->_callCarrier = false;
	_callShipUI->_callBattle = false;

	_callShipUI->_selectCardType = CARD_CL;
}

void callShipUI::functionCallCarrier(void * obj)
{
	callShipUI* _callShipUI = (callShipUI*)obj;
	_callShipUI->_callFrigate = false;
	_callShipUI->_callDestroyer = false;
	_callShipUI->_callCruiser = false;
	_callShipUI->_callCarrier = true;
	_callShipUI->_callBattle = false;

	_callShipUI->_selectCardType = CARD_CV;
}

void callShipUI::functionCallBattle(void * obj)
{
	callShipUI* _callShipUI = (callShipUI*)obj;
	_callShipUI->_callFrigate = false;
	_callShipUI->_callDestroyer = false;
	_callShipUI->_callCruiser = false;
	_callShipUI->_callCarrier = false;
	_callShipUI->_callBattle = true;

	_callShipUI->_selectCardType = CARD_BB;
}
