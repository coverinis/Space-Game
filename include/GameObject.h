/*
* FILE          : GameObject.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : GameObject header file
*/
#pragma once
#include "AssetManager.h"

class GameObject
{
public:
	float x = 0;
	float y = 0;
	float angle = 0;
	AssetManager* asset_manager_;
	GameObject(AssetManager* asset_manager, float x, float y, float angle);
	virtual ~GameObject();
};

