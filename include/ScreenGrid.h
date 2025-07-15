/*
* FILE          : ScreenGrid.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : ScreenGrid header file
*/
#pragma once
#include <vector>

class ScreenGrid
{
public:
	std::vector<std::vector<std::vector<float>>> grid_space;
	ScreenGrid();
	ScreenGrid(int ship_x, int ship_y);
	~ScreenGrid();
};

