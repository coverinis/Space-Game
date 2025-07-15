/*
* FILE          : Level1.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Level1 header file
*/
#pragma once
#include "GameLevel.h"
#include <vector>
#include "ScreenGrid.h"
#include <tuple>
#include "GameObject.h"
#include "Wave.h"

class Level1: public GameLevel
{
	int ship_x_ = 0;
	int ship_y_ = 4;
	AssetManager* scene_asset_manager_;
	std::vector<CWave> audio_ = {
		CWave(),
		CWave(),
		CWave(),
		CWave()
	};
	std::vector<unsigned long> playtime = {
		0,
		0
	};
	std::vector<unsigned long> time = {
		0,
		0
	};
	std::vector<GameObject> objects_;

	ScreenGrid* grid_;
public:
	Level1();
	~Level1();

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(float x, float y) override;
};

