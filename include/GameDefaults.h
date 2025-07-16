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
constexpr int GAME_EXIT_CODE{0};
constexpr int D_WIDTH{1000};
constexpr int D_HEIGHT{750};
constexpr int D_XY_START{0};
constexpr int MAX_GRID{10};
constexpr int O_WIDTH{D_WIDTH / MAX_GRID};
constexpr int O_HEIGHT{D_HEIGHT / MAX_GRID};
constexpr int SHIP_SPEED{6};
constexpr int ENEMY_SPEED{3};
constexpr int O_CENTER_X{O_WIDTH / 2};
constexpr int O_CENTER_Y{O_HEIGHT / 2};
const std::string END_GAME = "End_Game";

//Enum
enum class GridObject {
    None = 0,
    Planet1 = 1,
    Planet2 = 2,
    Planet3 = 3,
};

//Functions
void PresentSwapChain(RenderManager* render_manager);
