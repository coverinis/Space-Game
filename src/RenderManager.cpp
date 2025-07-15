/*
* FILE          : RenderManager.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Manage rendering the screen
*/
#include "RenderManager.h"

using namespace D2D1;

RenderManager::RenderManager()
{
	factory_ = NULL;
	render_target_ = NULL;
	dxgiBackBuffer = NULL;
	dxgiFactory = NULL;
	dxgiAdapter = NULL;
	dxgiDevice = NULL;
	context = NULL;
	device = NULL;
	Direct2DBackBuffer = NULL;
	DXGISwapChain = NULL;
	render_target_ = NULL;
	Direct2DDevice = NULL;
	Direct3DContext = NULL;
	Direct3DDevice = NULL;
}


RenderManager::~RenderManager()
{
	if (factory_) factory_->Release();
	if (render_target_) render_target_->Release();
	if (dxgiBackBuffer) dxgiBackBuffer->Release();
	if (dxgiFactory) dxgiFactory->Release();
	if (dxgiAdapter) dxgiAdapter->Release();
	if (dxgiDevice) dxgiDevice->Release();
	if (context) context->Release();
	if (device) device->Release();

	// Direct2D 1.1
	if (Direct2DBackBuffer) Direct2DBackBuffer->Release();
	if (DXGISwapChain) DXGISwapChain->Release();
	if (Direct2DDevice) Direct2DDevice->Release();
	if (Direct3DContext) Direct3DContext->Release();
	if (Direct3DDevice) Direct3DDevice->Release();
}

bool RenderManager::Init(HWND window_handle)
{
	/*Reference: Katy, D. (2013, September 26). Direct2D 1.1 Migration Guide for Windows 7 Developers. Retrieved February 18, 2017, 
	*            from https://katyscode.wordpress.com/2013/01/23/migrating-existing-direct2d-applications-to-use-direct2d-1-1-functionality-in-windows-7/ */
	//Create a single head factory
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, reinterpret_cast<void **>(&factory_));
	//Check successful creation
	if (hr != S_OK) return false;

	//Get render area
	RECT rect;
	GetClientRect(window_handle, &rect);

	//Create a render target
	// Set feature levels supported by our application
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	// This flag adds support for surfaces with a different color channel ordering
	// than the API default. It is required for compatibility with Direct2D.
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION,
		&device, &returnedFeatureLevel, &context);
	//Check successful creation
	if (hr != S_OK) return false;

	hr = device->QueryInterface(__uuidof(ID3D11Device1), (void **)&Direct3DDevice);
	//Check successful creation
	if (hr != S_OK) return false;

	hr = context->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&Direct3DContext);
	//Check successful creation
	if (hr != S_OK) return false;

	hr = Direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);
	//Check successful creation
	if (hr != S_OK) return false;

	hr = factory_->CreateDevice(dxgiDevice, &Direct2DDevice);
	//Check successful creation
	if (hr != S_OK) return false;

	hr = Direct2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &render_target_);
	//Check successful creation
	if (hr != S_OK) return false;

	// Get the GPU we are using
	hr = dxgiDevice->GetAdapter(&dxgiAdapter);
	//Check successful creation
	if (hr != S_OK) return false;

	// Get the DXGI factory instance
	hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
	//Check successful creation
	if (hr != S_OK) return false;

	// Describe Windows 7-compatible Windowed swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	// Create DXGI swap chain targeting a window handle (the only Windows 7-compatible option)
	hr = dxgiFactory->CreateSwapChainForHwnd(Direct3DDevice, window_handle, &swapChainDesc, nullptr, nullptr, &DXGISwapChain);
	//Check successful creation
	if (hr != S_OK) return false;

	// Get the back buffer as an IDXGISurface (Direct2D doesn't accept an ID3D11Texture2D directly as a render target)
	hr = DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));
	//Check successful creation
	if (hr != S_OK) return false;

	// Get screen DPI
	FLOAT dpiX, dpiY;
	factory_->GetDesktopDpi(&dpiX, &dpiY);

	// Create a Direct2D surface (bitmap) linked to the Direct3D texture back buffer via the DXGI back buffer
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), dpiX, dpiY);

	hr = render_target_->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &Direct2DBackBuffer);
	//Check successful creation
	if (hr != S_OK) return false;

	// Set surface as render target in Direct2D device context
	render_target_->SetTarget(Direct2DBackBuffer);

	//Final return
	return true;
}

void RenderManager::ClearScreen(float r, float g, float b)
{
	render_target_->Clear(ColorF(r, g, b));
}

ID2D1DeviceContext* RenderManager::GetRenderTarget()
{
	return  render_target_;
}

ID2D1Factory1* RenderManager::GetFactory()
{
	return factory_;
}

IDXGISwapChain1* RenderManager::GetSwapChain()
{
	return DXGISwapChain;
}
