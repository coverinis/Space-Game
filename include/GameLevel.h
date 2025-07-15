/*
* FILE          : GameLevel.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : GameLevel header file
*/
#pragma once
#include "RenderManager.h"
#include "AssetManager.h"
#include "GameDefaults.h"
#include <mmsystem.h>
#include "Wave.h"

class GameLevel
{
protected:
	static RenderManager* render_manager;
public:
	virtual ~GameLevel() = default;
	static  void Init(RenderManager* manager);
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Render() = 0;
	virtual void Update(float x, float y) = 0;
};

