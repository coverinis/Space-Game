/*
* FILE          : GameObject.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Base class for game objects
*/
#include "GameObject.h"



GameObject::GameObject(AssetManager* asset_manager, float x, float y, float angle)
{
	this->asset_manager_ = asset_manager;
	this->x = x;
	this->y = y;
	this->angle = angle;
}

GameObject::~GameObject()
{
}
