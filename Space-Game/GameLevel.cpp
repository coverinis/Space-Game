/*
* FILE          : GameLevel.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Interface for game level
*/
#include "GameLevel.h"

RenderManager* GameLevel::render_manager;

void GameLevel::Init(RenderManager* manager)
{
	render_manager = manager;
}
