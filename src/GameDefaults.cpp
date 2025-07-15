/*
* FILE          : GameDefault.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Game defaul functions
*/
#pragma once
#include "GameDefaults.h"


void PresentSwapChain(RenderManager* render_manager)
{
	DXGI_PRESENT_PARAMETERS dxgi_present_parameters = { 0 };
	dxgi_present_parameters.DirtyRectsCount = 0;
	dxgi_present_parameters.pDirtyRects = nullptr;
	dxgi_present_parameters.pScrollRect = nullptr;
	dxgi_present_parameters.pScrollOffset = nullptr;

	render_manager->GetSwapChain()->Present1(1, 0, &dxgi_present_parameters);
}
