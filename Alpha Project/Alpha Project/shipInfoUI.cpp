#include "stdafx.h"
#include "shipInfoUI.h"


shipInfoUI::shipInfoUI()
{
}


shipInfoUI::~shipInfoUI()
{
}

HRESULT shipInfoUI::init()
{
	_background = IMAGEMANAGER->findImage("shipinfo_back");
	_contents	= IMAGEMANAGER->findImage("shipinfo_contents");
	_frame		= IMAGEMANAGER->findImage("shipinfo_frame");
	_rcInfo = RectMake(0, 0, _background->getWidth(), _background->getHeight());

	_rader	= IMAGEMANAGER->findImage("rader");
	_engine = IMAGEMANAGER->findImage("engine");

	_bHasShip = false;
	_bLoadData = false;

	_showShipName = "";	
	_shipName = "";
	_shipClass = "";
	_shipRaderName = "";
	_shipEngineName = "";

	_shipDP = _shipWeight = 0;
	_shipDefenExTop = _shipDefenPeTop = _shipDefenExBottom = _shipDefenPeBottom = 0;
	_shipInchTop = _shipInchBottom = 0;
	_shipRange = _shipAccuracy = 0;
	_shipEnginePower = _shipMinSpeed = _shipMaxSpeed = 0;

	_progressBarDP = new progressBarA;
	_progressBarDP->init("progressbarRH", "progressbarWH", "progressbarBack", 15, 63, 194, 5);
	_progressBarWeight = new progressBarA;
	_progressBarWeight->init("progressbarRH", "progressbarWH", "progressbarBack", 15, 85, 194, 5);

	return S_OK;
}

void shipInfoUI::release()
{
	_progressBarDP->release();
	_progressBarWeight->release();

	SAFE_DELETE(_progressBarDP);
	SAFE_DELETE(_progressBarWeight);
}

void shipInfoUI::update()
{
	if (_bHasShip)
	{
		if (!_bLoadData)
		{
			_bLoadData = true;

			_shipName			= DATABASE->getShipElementData(_showShipName)->shipName;
			_shipClass			= DATABASE->getShipElementData(_showShipName)->shipClass;
			_shipDP				= DATABASE->getShipElementData(_showShipName)->shipDP;
			_shipWeight			= DATABASE->getShipElementData(_showShipName)->shipWeight;

			_shipDefenExTop		= DATABASE->getShipElementData(_showShipName)->shipDefenExTop;
			_shipDefenPeTop		= DATABASE->getShipElementData(_showShipName)->shipDefenPeTop;
			_shipDefenExBottom	= DATABASE->getShipElementData(_showShipName)->shipDefenExBottom;
			_shipDefenPeBottom	= DATABASE->getShipElementData(_showShipName)->shipDefenPeBottom;

			_shipInchTop		= DATABASE->getShipElementData(_showShipName)->shipInchTop;
			_shipInchBottom		= DATABASE->getShipElementData(_showShipName)->shipInchBottom;

			_shipRaderName		= DATABASE->getShipElementData(_showShipName)->shipRaderName;
			_shipRange			= DATABASE->getShipElementData(_showShipName)->shipRange;
			_shipAccuracy		= DATABASE->getShipElementData(_showShipName)->shipAccuracy;

			_shipEngineName		= DATABASE->getShipElementData(_showShipName)->shipEngineName;
			_shipEnginePower	= DATABASE->getShipElementData(_showShipName)->shipEnginePower;
			_shipMinSpeed		= DATABASE->getShipElementData(_showShipName)->shipMinSpeed;
			_shipMaxSpeed		= DATABASE->getShipElementData(_showShipName)->shipMaxSpeed;

			_vShipDP				= NUMBERINGMANAGER->getNumber(_shipDP, SC_M);
			_vShipWeight			= NUMBERINGMANAGER->getNumber(_shipWeight, SC_M);
			_vShipDefenExtop		= NUMBERINGMANAGER->getNumber(_shipDefenExTop, NWH);
			_vShipDefenPetop		= NUMBERINGMANAGER->getNumber(_shipDefenPeTop, NWH);
			_vShipDefenExBottom		= NUMBERINGMANAGER->getNumber(_shipDefenExBottom, NWH);
			_vShipDefenPeBottom		= NUMBERINGMANAGER->getNumber(_shipDefenPeBottom, NWH);
			_vShipInchTop			= NUMBERINGMANAGER->getNumber(_shipInchTop, NWH);
			_vShipInchBottom		= NUMBERINGMANAGER->getNumber(_shipInchBottom, NWH);
			_vShipRange				= NUMBERINGMANAGER->getNumber(_shipRange, NWH);
			_vShipAccuracy			= NUMBERINGMANAGER->getNumber(_shipAccuracy, NWH);
			_vShipEnginePower		= NUMBERINGMANAGER->getNumber(_shipEnginePower, NWH);
			_vShipMinSpeed			= NUMBERINGMANAGER->getNumber(_shipMinSpeed, NWH);
			_vShipMaxSpeed			= NUMBERINGMANAGER->getNumber(_shipMaxSpeed, NWH);

		}
	}	

	_progressBarDP->gauge(_shipDP, _shipDP, 23.0f);
	_progressBarWeight->gauge(_shipWeight, _shipWeight, 20.0f);
	_progressBarDP->update();
	_progressBarWeight->update();

}

void shipInfoUI::render()
{
	_background->render(getMemDC(), _rcInfo.left, _rcInfo.top);
	_contents->render(getMemDC(), _rcInfo.left, _rcInfo.top);
	_frame->render(getMemDC(), _rcInfo.left, _rcInfo.top);

	_rader->render(getMemDC(), _rcInfo.left + 20, _rcInfo.top + 190);
	_engine->render(getMemDC(), _rcInfo.left + 20, _rcInfo.top + 260);

	if (_bHasShip)
	{
		HFONT myFont, oldFont;

		myFont = CreateFont(13, 0, 0, 0, 500, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("±Ã¼­Ã¼"));
		oldFont = (HFONT)SelectObject(getMemDC(), myFont);

		// ======================= SHIP NAME / CLASS ======================= //
		TextOut(getMemDC(), 50, 17, _shipName.c_str(), _shipName.size());
		TextOut(getMemDC(), 50, 32, _shipClass.c_str(), _shipClass.size());

		// ======================= SHIP DP / WEIGHT ======================= //
		for (int i = 0; i < _vShipDP.size(); i++)
			_vShipDP[i]->frameRender(getMemDC(), 100 + (i * 8), 47, _vShipDP[i]->getFrameX(), _vShipDP[i]->getFrameY());
		for (int i = 0; i < _vShipWeight.size(); i++)
			_vShipWeight[i]->frameRender(getMemDC(), 100 + (i * 8), 71, _vShipWeight[i]->getFrameX(), _vShipWeight[i]->getFrameY());
		TextOut(getMemDC(), 150, 47, "/", 1);
		TextOut(getMemDC(), 150, 71, "/", 1);
		for (int i = 0; i < _vShipDP.size(); i++)
			_vShipDP[i]->frameRender(getMemDC(), 160 + (i * 8), 47, _vShipDP[i]->getFrameX(), _vShipDP[i]->getFrameY());
		for (int i = 0; i < _vShipWeight.size(); i++)
			_vShipWeight[i]->frameRender(getMemDC(), 160 + (i * 8), 71, _vShipWeight[i]->getFrameX(), _vShipWeight[i]->getFrameY());

		// ======================= SHIP ARMOR ======================= //
		for (int i = 0; i < _vShipDefenExtop.size(); i++)
			_vShipDefenExtop[i]->frameRender(getMemDC(), 136 + (i * 8), 136, _vShipDefenExtop[i]->getFrameX(), _vShipDefenExtop[i]->getFrameY());
		for (int i = 0; i < _vShipDefenPetop.size(); i++)
			_vShipDefenPetop[i]->frameRender(getMemDC(), 80 + (i * 8), 136, _vShipDefenPetop[i]->getFrameX(), _vShipDefenPetop[i]->getFrameY());
		for (int i = 0; i < _vShipDefenExBottom.size(); i++)
			_vShipDefenExBottom[i]->frameRender(getMemDC(), 136 + (i * 8), 150, _vShipDefenExBottom[i]->getFrameX(), _vShipDefenExBottom[i]->getFrameY());
		for (int i = 0; i < _vShipDefenPeBottom.size(); i++)
			_vShipDefenPeBottom[i]->frameRender(getMemDC(), 80 + (i * 8), 150, _vShipDefenPeBottom[i]->getFrameX(), _vShipDefenPeBottom[i]->getFrameY());
		for (int i = 0; i < _vShipInchTop.size(); i++)
			_vShipInchTop[i]->frameRender(getMemDC(), 70 + (i * 8), 121, _vShipInchTop[i]->getFrameX(), _vShipInchTop[i]->getFrameY());
		for (int i = 0; i < _vShipInchBottom.size(); i++)
			_vShipInchBottom[i]->frameRender(getMemDC(), 70 + (i * 8), 162, _vShipInchBottom[i]->getFrameX(), _vShipInchBottom[i]->getFrameY());
		
		// ======================= SHIP FCS ======================= //
		TextOut(getMemDC(), 80, 195, _shipRaderName.c_str(), _shipRaderName.size());
		for (int i = 0; i < _vShipRange.size(); i++)
			_vShipRange[i]->frameRender(getMemDC(), 160 + (i * 8), 213, _vShipRange[i]->getFrameX(), _vShipRange[i]->getFrameY());
		for (int i = 0; i < _vShipAccuracy.size(); i++)
			_vShipAccuracy[i]->frameRender(getMemDC(), 160 + (i * 8), 225, _vShipAccuracy[i]->getFrameX(), _vShipAccuracy[i]->getFrameY());

		// ======================= SHIP ENGINE ======================= //
		TextOut(getMemDC(), 80, 259, _shipEngineName.c_str(), _shipEngineName.size());
		for (int i = 0; i < _vShipEnginePower.size(); i++)
			_vShipEnginePower[i]->frameRender(getMemDC(), 135 + (i * 8), 277, _vShipEnginePower[i]->getFrameX(), _vShipEnginePower[i]->getFrameY());
		for (int i = 0; i < _vShipMinSpeed.size(); i++)
			_vShipMinSpeed[i]->frameRender(getMemDC(), 135 + (i * 8), 290, _vShipMinSpeed[i]->getFrameX(), _vShipMinSpeed[i]->getFrameY());
		for (int i = 0; i < _vShipMaxSpeed.size(); i++)
			_vShipMaxSpeed[i]->frameRender(getMemDC(), 165 + (i * 8), 290, _vShipMaxSpeed[i]->getFrameX(), _vShipMaxSpeed[i]->getFrameY());

		SelectObject(getMemDC(), oldFont);
		DeleteObject(myFont);
	}

	_progressBarDP->render();
	_progressBarWeight->render();

}
