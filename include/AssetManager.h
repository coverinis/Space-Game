/*
* FILE          : AssetManager.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : AssetManager header file
*/
#pragma once
#include <wincodec.h>
#include <d2d1effects_2.h>
#include <D3D11.h>
#include <wrl/client.h>
#include "RenderManager.h"
#include "GameDefaults.h"
#include <vector>

class AssetManager
{
	RenderManager* render_manager_; //reference to render manager
	ID2D1Bitmap1* bitmap_;          //Bitmap converted to Direct2D
	ID2D1Image* image_;
public:
	AssetManager(wchar_t* file_name, RenderManager* render_manager, float r, float g, float b, float t);
	~AssetManager();

	void Draw();
	void Draw(float x, float y, float angle);
};

