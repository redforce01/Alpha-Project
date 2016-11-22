#pragma once
#include "loading.h"
class startLoading : public loading
{
private:
	image* _background;
	float _fLoadingElapsedTime;
	int _nloadingImgNumber;
	int _nBackgroundAlpha;
	bool _bAlphaChange;
	bool _bAlphaUp;
	bool _bAlphaDown;

	image* _loading;
	RECT _rcLoading;
	int _nLoadingFrame;
	int _nLoadingTime;

public:
	startLoading();
	~startLoading();

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

public:
	void addLoadItemShip();
	void addLoadItemField();
	void addLoadItemHarbor();
	void addLoadItemLobby();
	void addLoadItemWorldMap();
	void addLoadItemTitle();

	void addLoadItemInterface();
	void addLoadItemSound();


	//void loadImage(string keyName, int width, int height);
	//void loadImage(string keyName, const char* fileName, int x, int y, int width, int height, bool trans, COLORREF transColor);
	//void loadImage(string keyName, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	//void loadFrameImage(string keyName, const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	//void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	//void loadSound(string keyName, const char* fileName, bool loop, bool background);
};

