#include "stdafx.h"
#include "unitList.h"


unitList::unitList()
{
}


unitList::~unitList()
{
}

HRESULT unitList::init(UNIT_CLASS unitClass)
{	
	int xNum = 0;
	_listSize = 0;

	for (unsigned int i = 0; i < DATABASE->getShipList().size(); i++)
	{
		if (DATABASE->getShipElementData(DATABASE->getShipList()[i])->shipClass != getShipClass(unitClass)) continue;
		else
		{
			tagUnitCard tempCard;
			ZeroMemory(&tempCard, sizeof(tempCard));
			tempCard.x = (xNum * 120) + 20, tempCard.y = 80;
			tempCard.unitName = DATABASE->getShipList()[i];
			tempCard.unitClass = unitClass;

			char strUnitImageName[128] = "";
			char strUnitImageKey[128] = "component_";
			strcat_s(strUnitImageKey, DATABASE->getShipElementData(tempCard.unitName)->shipClass.c_str());
			strcat_s(strUnitImageKey, "_");
			strcat_s(strUnitImageName, strUnitImageKey);
			strcat_s(strUnitImageName, tempCard.unitName.c_str());

			tempCard.unitCard = IMAGEMANAGER->findImage(strUnitImageName);
			tempCard.rc = RectMake(tempCard.x, tempCard.y, tempCard.unitCard->getWidth(), tempCard.unitCard->getHeight());
			tempCard.rcName = RectMake(tempCard.rc.left, tempCard.rc.bottom, tempCard.unitCard->getWidth(), 20);
			tempCard.availability = DATABASE->getAvailableList().find(DATABASE->getShipList()[i])->second->unitAvailability;

			_vUnitList.push_back(tempCard);
			xNum++;
		}
	}

	_listSize = _vUnitList.size();

	return S_OK;
}

void unitList::release()
{
}

void unitList::update()
{
}

void unitList::render()
{
	int unitListSize = _vUnitList.size();
	for (int i = 0; i < unitListSize; i++)
	{
		HPEN myPen, oldPen, borderPen;
		HBRUSH myBrush, oldBrush, nameBrush;
		myPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
		borderPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		
		nameBrush = CreateSolidBrush(RGB(52, 64, 69));
		oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
		oldPen = (HPEN)SelectObject(getMemDC(), myPen);
		Rectangle(getMemDC(), _vUnitList[i].rc.left, _vUnitList[i].rc.top, _vUnitList[i].rc.right, _vUnitList[i].rc.bottom);
		FillRect(getMemDC(), &_vUnitList[i].rcName, nameBrush);
		_vUnitList[i].unitCard->render(getMemDC(), _vUnitList[i].rc.left, _vUnitList[i].rc.top);

		SelectObject(getMemDC(), borderPen);
		MoveToEx(getMemDC(), _vUnitList[i].rc.left, _vUnitList[i].rc.top, 0);
		LineTo(getMemDC(), _vUnitList[i].rc.left, _vUnitList[i].rcName.bottom);
		LineTo(getMemDC(), _vUnitList[i].rc.right, _vUnitList[i].rcName.bottom);
		LineTo(getMemDC(), _vUnitList[i].rc.right, _vUnitList[i].rc.top);
		LineTo(getMemDC(), _vUnitList[i].rc.left, _vUnitList[i].rc.top);

		SelectObject(getMemDC(), oldPen);
		SelectObject(getMemDC(), oldBrush);
		DeleteObject(myPen);
		DeleteObject(borderPen);
		DeleteObject(myBrush);
		DeleteObject(nameBrush);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		DrawText(getMemDC(), _vUnitList[i].unitName.c_str(), strlen(_vUnitList[i].unitName.c_str()), &_vUnitList[i].rcName, DT_CENTER);

		char str[128];
		sprintf_s(str, "(%d)", _vUnitList[i].availability);
		TextOut(getMemDC(), _vUnitList[i].rc.right - 25, _vUnitList[i].rc.bottom - 20, str, strlen(str));
		SetTextColor(getMemDC(), RGB(0, 0, 0));

	}
	
}
