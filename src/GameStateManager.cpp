/*
* FILE          : GameStateManager.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Manage the game state
*/
#include "GameStateManager.h"


std::unique_ptr<GameLevel> GameStateManager::current_level;
bool GameStateManager::Loading;

GameStateManager::GameStateManager()
{
}

void GameStateManager::Init()
{
        Loading = true;
        current_level.reset();
}

void GameStateManager::LoadInitialLevel(std::unique_ptr<GameLevel> level)
{
        current_level = std::move(level);
        Loading = true;
        if (current_level) {
                current_level->Load();
        }
        Loading = false;

}

void GameStateManager::SwitchLevel(std::unique_ptr<GameLevel> level)
{
        Loading = true;
        if (current_level) {
                current_level->Unload();
        }
        if (level) {
                level->Load();
        }
        current_level = std::move(level);
        Loading = false;
}

void GameStateManager::Render()
{
        if (Loading || !current_level)
                return;
        current_level->Render();
}

void GameStateManager::Update(int x, int y)
{
        if (Loading || !current_level)
                return;
        current_level->Update(x,y);
}

