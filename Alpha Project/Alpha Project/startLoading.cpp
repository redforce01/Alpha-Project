#include "stdafx.h"
#include "startLoading.h"


startLoading::startLoading()
{
}


startLoading::~startLoading()
{
}

HRESULT startLoading::init()
{
	IMAGEMANAGER->addImage("introBackground_1", "image/intro/loading1.bmp", 1280, 660, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("introBackground_2", "image/intro/loading2.bmp", 1280, 660, true, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("introBackground_3", "image/intro/loading3.bmp", 1280, 660, true, RGB(0, 0, 0));

	_background = IMAGEMANAGER->findImage("introBackground_1");
	_fLoadingElapsedTime = 0.f;
	_nloadingImgNumber = 0;
	_nBackgroundAlpha = 255;
	_bAlphaChange = false;
	_bAlphaUp = false;
	_bAlphaDown = true;

	_loading = IMAGEMANAGER->addFrameImage("introloading", "image/intro/loading.bmp", 4320, 60, 72, 1, true, RGB(0, 0, 0));
	_rcLoading = RectMakeCenter(CENTERX, WINSIZEY - _loading->getFrameHeight() - 5, _loading->getFrameWidth(), _loading->getFrameHeight());
	_nLoadingFrame = 0;
	_nLoadingTime = 0.f;


	addLoadItemShip();
	addLoadItemField();
	addLoadItemHarbor();
	addLoadItemLobby();
	addLoadItemWorldMap();
	addLoadItemTitle();
	addLoadItemInterface();
	addLoadItemSound();

	return S_OK;
}

void startLoading::release()
{
}

void startLoading::update()
{
	_nLoadingTime++;
	if (_nLoadingTime % 2 == 0)
	{
		_loading->setFrameX(_nLoadingFrame);
		_nLoadingFrame++;
		if (_nLoadingFrame > _loading->getMaxFrameX()) _nLoadingFrame = 0;
	}

	_fLoadingElapsedTime += TIMEMANAGER->getElapsedTime();
	if (!_bAlphaChange)
	{
		if (_fLoadingElapsedTime > 3.0f)
		{
			_fLoadingElapsedTime = 0.f;
			_bAlphaChange = true;
		}
	}


	if (_bAlphaChange)
	{
		if (_bAlphaDown)
		{
			_nBackgroundAlpha -= 5;
			if (_nBackgroundAlpha == 0)
			{
				_bAlphaDown = false;
				_bAlphaUp = true;
				_nloadingImgNumber++;
			}
		}

		if (_bAlphaUp)
		{
			_nBackgroundAlpha += 5;
			if (_nBackgroundAlpha == 255)
			{
				_bAlphaDown = true;
				_bAlphaUp = false;
				_bAlphaChange = false;
			}
		}

	}

	if (_nloadingImgNumber % 3 == 0) _background = IMAGEMANAGER->findImage("introBackground_1");
	else if (_nloadingImgNumber % 2 == 0) _background = IMAGEMANAGER->findImage("introBackground_2");
	else if (_nloadingImgNumber % 1 == 0) _background = IMAGEMANAGER->findImage("introBackground_3");
	if (FALSE == loadNext()) SCENEMANAGER->changeScene("titleScene");
	else loadNext();
	
}

void startLoading::render()
{
	_background->alphaRender(getMemDC(), 0, 0, _nBackgroundAlpha);
	_loading->frameRender(getMemDC(), _rcLoading.left, _rcLoading.top, _loading->getFrameX(), _loading->getFrameY());
}

void startLoading::addLoadItemShip()
{
	loadImage("harbor_top_Fletcher", "image/ships/Fletcher/Harbor_top_Fletcher.bmp", 506, 235, true, RGB(0, 0, 0));
	loadImage("harbor_bottom_Fletcher", "image/ships/Fletcher/harbor_bottom_Fletcher.bmp", 506, 235, true, RGB(0, 0, 0));
	loadImage("harbor_top_Midway", "image/ships/Midway/harbor_top_Midway.bmp", 1198, 582, true, RGB(0, 0, 0));
	loadImage("harbor_bottom_Midway", "image/ships/Midway/harbor_bottom_Midway.bmp", 1198, 582, true, RGB(0, 0, 0));
}

void startLoading::addLoadItemField()
{
	//BATTLE MAP TILE
	loadImage("battle_tile_1", "image/battle/tile.bmp", 128, 64, true, RGB(0, 0, 0));

	//BATTLE UI
	loadImage("battle_bottomExtend", "image/battle/InterfaceBackHall_2.bmp", 1094, 160, true, RGB(255, 0, 255));
	loadImage("battle_ScoreScreen", "image/battle/ScoreScreen.bmp", 1024, 40, true, RGB(0, 0, 0));

	//BATTLE MINIMAP
	loadFrameImage("battle_minimap", "image/battle/Minimap.bmp", 14336, 160, 14, 1, true, RGB(0, 0, 0));
	loadFrameImage("battle_minimap_frame", "image/battle/MinimapFrame.bmp", 14336, 160, 14, 1, true, RGB(0, 0, 0));
	loadFrameImage("battle_minimap_shadow", "image/battle/MinimapSh.bmp", 14436, 160, 14, 1, true, RGB(0, 0, 0));
	loadImage("battle_minimap_grid", "image/battle/Grid_stand.bmp", 1024, 160, true, RGB(0, 0, 0));
	loadImage("battle_minimap_grid_shadow", "image/battle/Grid_Sh_stand.bmp", 1024, 160, true, RGB(0, 0, 0));

	//BATTLE UI COMPONENT
	loadImage("component_BB_Alaska", "image/component/component_BB_Alaska.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_BB_Guam", "image/component/component_BB_Guam.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_BB_Iowa", "image/component/component_BB_Iowa.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_BB_Nevada", "image/component/component_BB_Nevada.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_BB_NewMexico(1930)", "image/component/component_BB_NewMexico(1930).bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_BB_Pennsylvania(1930)", "image/component/component_BB_Pennsylvania(1930).bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CL_Atlanta", "image/component/component_CL_Atlanta.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CL_Brooklyn", "image/component/component_CL_Brooklyn.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CL_Cleveland", "image/component/component_CL_Cleveland.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CL_Omaha", "image/component/component_CL_Omaha.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CL_Portland", "image/component/component_CL_Portland.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CV_Bogue", "image/component/component_CV_Bogue.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CV_Essex", "image/component/component_CV_Essex.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CV_Lexington", "image/component/component_CV_Lexington.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CV_Midway", "image/component/component_CV_Midway.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_CV_Yorktown", "image/component/component_CV_Yorktown.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_DD_DDXProject", "image/component/component_DD_DDXProject.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_DD_Fletcher", "image/component/component_DD_Fletcher.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));
	loadImage("component_DD_Somers", "image/component/component_DD_Somers.bmp", UNITCARD_WIDTH, UNITCARD_HEIGHT, false, RGB(0, 0, 0));

}

void startLoading::addLoadItemHarbor()
{
	loadImage("shipyardBackground", "image/shipyard/harbor.bmp", 1600, 1200, true, RGB(0, 0, 0));
	loadImage("topExtendUI", "image/shipyard/topExtendUI.bmp", 1280, 53, true, RGB(0, 0, 0));
	loadImage("shipinfo_back", "image/shipyard/shipinfo_back.bmp", 237, 363, true, RGB(0, 0, 0));
	loadImage("shipinfo_contents", "image/shipyard/shipinfo_contents.bmp", 237, 363, true, RGB(0, 0, 0));
	loadImage("shipinfo_frame", "image/shipyard/shipinfo_frame.bmp", 237, 376, true, RGB(0, 0, 0));
	loadImage("rader", "image/shipyard/FCS.bmp", 50, 50, true, RGB(0, 0, 0));
	loadImage("engine", "image/shipyard/Engine.bmp", 50, 50, true, RGB(0, 0, 0));


	loadFrameImage("btnArrowLeft", "image/shipyard/btnArrowLeft.bmp", 300, 100, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRight", "image/shipyard/btnArrowRight.bmp", 300, 100, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowLaunch", "image/shipyard/btnArrowLaunch.bmp", 300, 100, 3, 1, true, RGB(0, 0, 0));


	loadFrameImage("btnBuy", "image/shipyard/btnBuy.bmp", 93, 19, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnSell", "image/shipyard/btnSell.bmp", 93, 19, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnRepair", "image/shipyard/btnRepair.bmp", 93, 19, 3, 1, true, RGB(0, 0, 0));


	loadFrameImage("btnShipyard", "image/shipyard/btnShipyard.bmp", 147, 16, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnBattle", "image/shipyard/btnBattle.bmp", 147, 16, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnDepot", "image/shipyard/btnDepot.bmp", 147, 16, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnTrade", "image/shipyard/btnTrade.bmp", 147, 16, 3, 1, true, RGB(0, 0, 0));
}

void startLoading::addLoadItemLobby()
{	
	loadImage("lobbyBackground", "image/lobby/background.bmp", 1280, 720, false, false);
	loadFrameImage("shipYardButton", "image/lobby/shipyardButton.bmp", 210, 31, 2, 1, true, RGB(0, 0, 0));
}

void startLoading::addLoadItemWorldMap()
{
	loadImage("worldMap", "image/worldMap/worldMap.bmp", 4261, 2067, true, RGB(0, 0, 0));

	loadFrameImage("btnArrowLeftUpN", "image/worldmap/btnArrowLeftUpN.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowLeftUpO", "image/worldmap/btnArrowLeftUpO.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowLeftUpP", "image/worldmap/btnArrowLeftUpP.bmp", 1100, 100, 11, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowLeftDownN", "image/worldmap/btnArrowLeftDownN.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowLeftDownO", "image/worldmap/btnArrowLeftDownO.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowLeftDownP", "image/worldmap/btnArrowLeftDownP.bmp", 1100, 100, 11, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRightUpN", "image/worldmap/btnArrowRightUpN.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRightUpO", "image/worldmap/btnArrowRightUpO.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRightUpP", "image/worldmap/btnArrowRightUpP.bmp", 1100, 100, 11, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRightDownN", "image/worldmap/btnArrowRightDownN.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRightDownO", "image/worldmap/btnArrowRightDownO.bmp", 1000, 100, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("btnArrowRightDownP", "image/worldmap/btnArrowRightDownP.bmp", 1100, 100, 11, 1, true, RGB(0, 0, 0));


}

void startLoading::addLoadItemTitle()
{
	loadImage("titleBackground", "image/title/background.bmp", 1280, 720, false, false);
	loadImage("titleLogin", "image/title/Login.bmp", 1024, 768, true, RGB(0, 0, 0));
	loadImage("titleShip", "image/title/Login_Ship.bmp", 723, 171, true, RGB(0, 0, 0));

	loadFrameImage("joinButton", "image/title/joinButton.bmp", 192, 32, 3, 1, true, RGB(0, 0, 0));
	loadFrameImage("cancelButton", "image/title/cancelButton.bmp", 192, 32, 3, 1, true, RGB(0, 0, 0));

	loadFrameImage("opPlane_1", "image/title/opPlane_1.bmp", 20000, 600, 25, 1, true, RGB(0, 0, 0));
	loadFrameImage("opPlane_2", "image/title/opPlane_2.bmp", 20000, 600, 25, 1, true, RGB(0, 0, 0));
	loadFrameImage("opPlane_3", "image/title/opPlane_3.bmp", 20000, 600, 25, 1, true, RGB(0, 0, 0));
	loadFrameImage("opPlane_4", "image/title/opPlane_4.bmp", 20000, 600, 25, 1, true, RGB(0, 0, 0));
}

void startLoading::addLoadItemInterface()
{
	loadFrameImage("mouseCursor_pyramid", "image/cursor/mouseCursor_pyramid.bmp", 1100, 90, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("mouseCursor_compass", "image/cursor/mouseCursor_compass.bmp", 1100, 90, 10, 1, true, RGB(0, 0, 0));
	loadFrameImage("mouseCursor_CompassShadow", "image/cursor/CompassShadow.bmp", 1100, 90, 10, 1, true, RGB(0, 0, 0));
}

void startLoading::addLoadItemSound()
{
}
