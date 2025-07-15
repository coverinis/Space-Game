/*
* FILE          : ScreenGrid.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Game grid
*/
#include "ScreenGrid.h"
#include "GameDefaults.h"
#include <ctime>
#include <string>


ScreenGrid::ScreenGrid()
{
	grid_space = std::vector<std::vector<std::vector<float>>>(10, std::vector<std::vector<float>>(10, std::vector<float>(3)));
	srand((int)time(NULL));
	//Create 10x10 grid
	for (int x = 0; x < MAX_GRID; ++x)
	{
		for (int y = 0; y < MAX_GRID; ++y)
		{
			//store render coordinates
			grid_space[x][y][0] = x * D_WIDTH / MAX_GRID;
			grid_space[x][y][1] = y * D_HEIGHT / MAX_GRID;
			//reserve space for default ship position
			if(x == 0 && y == 4)
			{
				grid_space[x][y][2] = NONE;
			}
			//Randomly fill grid space
			else if ((rand() % 20 + 1) == 20)
			{
				//Randomly generate planet
				switch (rand() % 3)
				{
				case 0:
					grid_space[x][y][2] = PLANET1;
					break;
				case 1:
					grid_space[x][y][2] = PLANET2;
					break;
				case 2:
					grid_space[x][y][2] = PLANET3;
					break;
				default:
					break;
				}
			}
			else
			{
				grid_space[x][y][2] = NONE;
			}
		}
	}
}

ScreenGrid::ScreenGrid(int ship_x, int ship_y)
{
	//check for valid input
	if(ship_x >= MAX_GRID || ship_x < 0)
	{
		ship_x = 0;
	}
	if (ship_y >= MAX_GRID || ship_y < 0)
	{
		ship_y = 0;
	}

	grid_space = std::vector<std::vector<std::vector<float>>>(10, std::vector<std::vector<float>>(10, std::vector<float>(3)));
	srand((int)time(NULL));
	//Create 10x10 grid
	for (int x = 0; x < MAX_GRID; ++x)
	{
		for (int y = 0; y < MAX_GRID; ++y)
		{
			//store render coordinates
			grid_space[x][y][0] = x * D_WIDTH / MAX_GRID;
			grid_space[x][y][1] = y * D_HEIGHT / MAX_GRID;

			//reserve space for provided ship position
			if (x == ship_x && y == ship_y)
			{
				grid_space[x][y][2] = NONE;
			}
			//Randomly fill grid space
			else if ((rand() % 20 + 1) == 20)
			{
				//Randomly generate planet
				switch (rand() % 3)
				{
				case 0:
					grid_space[x][y][2] = PLANET1;
					break;
				case 1:
					grid_space[x][y][2] = PLANET2;
					break;
				case 2:
					grid_space[x][y][2] = PLANET3;
					break;
				default:
					break;
				}
			}
			else
			{
				grid_space[x][y][2] = NONE;
			}
		}
	}
}


ScreenGrid::~ScreenGrid()
{
}
