/*
* FILE          : GameStateManager.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Manage the game state
*/
#include "GameStateManager.h"


GameLevel* GameStateManager::current_level;
bool GameStateManager::Loading;

GameStateManager::GameStateManager()
{
}

void GameStateManager::Init()
{
	Loading = true;
	current_level = NULL;
}

void GameStateManager::LoadInitialLevel(GameLevel* level)
{
	current_level = level;
	Loading = true;
	current_level->Load();
	Loading = false;

}

void GameStateManager::SwitchLevel(GameLevel* level)
{
	Loading = true;
	current_level->Unload();
	level->Load();
	delete current_level;
	current_level = level;
	Loading = false;
}

void GameStateManager::Render()
{
	if(Loading) return;
	current_level->Render();
}

void GameStateManager::Update(int x, int y)
{
	if(Loading) return;
	current_level->Update(x,y);
}

