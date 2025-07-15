/*
* FILE          : GameObject.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Base class for game objects
*/
#include "GameObject.h"
#include <memory>



GameObject::GameObject(std::unique_ptr<AssetManager> asset_manager, float x, float y, float angle)
    : x(x), y(y), angle(angle), asset_manager_(std::move(asset_manager))
{
}

GameObject::~GameObject()
{
}
