/*
* FILE          : GameStateManager.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : GameStateManager header file
*/
#pragma once
#include "GameLevel.h"

class GameStateManager
{
private:
	GameStateManager();
	static  GameLevel* current_level;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* level);
	static void SwitchLevel(GameLevel* level);
	static void Render();
	static void Update(int x, int y);
};

