#pragma once
#include "gameNode.h"
#include "progressBarA.h"

class battleLoading : public gameNode
{
private:
	bool _bCompleteLoading;

	image* _loadingBackground;
	progressBarA* _loadingBar;
	int _loadingCount;
	float _timeLoading;

public:
	battleLoading();
	~battleLoading();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getLoadingComplete() { return _bCompleteLoading; }
};

