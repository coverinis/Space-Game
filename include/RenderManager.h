/*
* FILE          : RenderManager.h
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : RenderManager header file
*/
#pragma once
#include <d2d1_1.h>
#include <D3D11_1.h>

class RenderManager
{

	// Direct3D device
	ID3D11Device1 *Direct3DDevice;

	// Direct3D device context
	ID3D11DeviceContext1 *Direct3DContext;

	// Direct2D device
	ID2D1Device *Direct2DDevice;

	//ID2D1HwndRenderTarget* render_target_;
	ID2D1DeviceContext* render_target_;

	// DXGI swap chain
	IDXGISwapChain1 *DXGISwapChain;

	// Direct2D target rendering bitmap
	// (linked to DXGI back buffer which is linked to Direct3D pipeline)
	ID2D1Bitmap1 *Direct2DBackBuffer;

	// Create Direct3D device and context
	ID3D11Device *device;
	ID3D11DeviceContext *context;
	D3D_FEATURE_LEVEL returnedFeatureLevel;

	IDXGIDevice *dxgiDevice;
	IDXGIAdapter *dxgiAdapter;
	IDXGIFactory2 *dxgiFactory;
	IDXGISurface *dxgiBackBuffer;

	//ID2D1Factory* factory_;
	ID2D1Factory1* factory_;
public:
	RenderManager();
	~RenderManager();

	bool Init(HWND window_handle);
	void BeginDraw() { render_target_->BeginDraw(); }
	void EndDraw() { render_target_->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	//ID2D1RenderTarget* GetRenderTarget();
	ID2D1DeviceContext* GetRenderTarget();
	//ID2D1Factory* GetFactory();
	ID2D1Factory1* GetFactory();

	IDXGISwapChain1* GetSwapChain();
};

