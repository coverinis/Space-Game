/*
* FILE          : GameStateManager.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : GameStateManager header file
*/
#pragma once
#include "GameLevel.h"
#include <memory>

class GameStateManager
{
private:
        GameStateManager();
        static std::unique_ptr<GameLevel> current_level;
public:
	static bool Loading;
	static void Init();
        static void LoadInitialLevel(std::unique_ptr<GameLevel> level);
        static void SwitchLevel(std::unique_ptr<GameLevel> level);
	static void Render();
	static void Update(int x, int y);
};

