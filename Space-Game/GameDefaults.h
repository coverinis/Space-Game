/*
* FILE          : GameDefault.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : GameDefault header file
*/
#pragma once
#include <D3D11_1.h>
#include "RenderManager.h"
#include <string>

//Constants
const int GAME_EXIT_CODE = 0;
const int D_WIDTH = 1000;
const int D_HEIGHT = 750;
const int D_XY_START = 0;
const int MAX_GRID = 10;
const int O_WIDTH = D_WIDTH / MAX_GRID;
const int O_HEIGHT = D_HEIGHT / MAX_GRID;
const int SHIP_SPEED = 6;
const int ENEMY_SPEED = 3;
const int O_CENTER_X = O_WIDTH / 2;
const int O_CENTER_Y = O_HEIGHT / 2;
const std::string END_GAME = "End_Game";

//Enum
enum GRID_OBJECT
{
	NONE = 0,
	PLANET1 = 1,
	PLANET2 = 2,
	PLANET3 = 3,

};

//Functions
void PresentSwapChain(RenderManager* render_manager);
