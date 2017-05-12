/*
* FILE          : GameLoop.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Main game window
* REFERENCE     : Foubert, R. et al. (2017) "A1 Bounty Hunting Lab", Graphics, Animation, and Sound (PROG2215). In-class labwork, 
*                 Feb. 15, 2017. Software Engineering Technology, Conestoga College ITAL: Kitchener, ON.
*/

//Imports
#include <windows.h>
#include "RenderManager.h"
#include "Level1.h"
#include "GameStateManager.h"
#include "GameDefaults.h"
#include <iostream>
#include <string>
#define DEBUG

//Variables
RenderManager* render_manager;

/*
* FUNCTION    : WindowProc
* DESCRIPTION : Window call back function
* PARAMETERS  : HWND   hWnd   : A handle to the window.
*               UINT   uMsg   : System messages.
*               WPARAM wParam : Additional message information.
*               LPARAM lParam : Additional message information.
* RETURNS     : LRESULT : result of the message processing.
*/
LRESULT CALLBACK WindowProc(
	HWND   hWnd,   //A handle to the window.
	UINT   uMsg,   //System messages.
	WPARAM wParam, //Additional message information.
	LPARAM lParam  //Additional message information.
) {
	//Check for messages
	switch (uMsg)
	{
		//Case when window is closed
		case WM_DESTROY:
			{
				//Close window
				PostQuitMessage(GAME_EXIT_CODE);
				return 0;
			}
	default: ;
	}

	//Return default window call
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
};

/*
* FUNCTION    : wWinMain
* DESCRIPTION : Main Window call
* PARAMETERS  : HINSTANCE hInstance     : Handle to current instance.
*               HINSTANCE hPrevInstance : Handle to previouse instance.
*               LPWSTR    lpCmdLine     : Command line string.
*               int       nCmdShow      : How window is shown.
* RETURNS     : LRESULT : result of the message processing.
*/
int WINAPI wWinMain(
	HINSTANCE hInstance,     //Handle to current instance.
	HINSTANCE hPrevInstance, //Handle to previouse instance.s
	LPWSTR lpCmdLine,        //Command line string.
	int nCmdShow             //How window is shown.
)
{
	//Assign window properties
	WNDCLASSEX window_class;
	ZeroMemory(&window_class, sizeof(WNDCLASSEX));
	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
	window_class.hInstance = hInstance;
	window_class.lpfnWndProc = WindowProc;
	window_class.lpszClassName = "MainWindow";
	window_class.style = CS_HREDRAW | CS_VREDRAW; //Redraw if resized horizontally and vertically

	//Register window class for creation calls
	RegisterClassEx(&window_class);

	//Window rectangle
	RECT window_rect = { D_XY_START, D_XY_START, D_WIDTH,  D_HEIGHT};
	AdjustWindowRectEx(&window_rect, WS_CAPTION, false, WS_EX_OVERLAPPEDWINDOW);

	//Create window
	HWND window_handle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,               //Extended window style
		"MainWindow",                         //Window class name
		"DirectXShell1",                      //Window title bar
		WS_OVERLAPPEDWINDOW,                  //Window style
		100,                                  //Initial x coordinate
		100,                                  //Initial y coordinate
		window_rect.right - window_rect.left, //Width of window
		window_rect.bottom - window_rect.top, //Width of height
		NULL,                                 //Parent of window, no parent = NULL
		NULL,                                 //Window menu, no menu = NULL
		hInstance,                            //Handle to the instance of the window
		0                                     //No Multiple windows so 0
	);
	//Check that window exists
	if (!window_handle) return -1;

	//Create render manager
	render_manager = new RenderManager();
	//Check for initialization of render manager
	if (!render_manager->Init(window_handle))
	{
		delete render_manager;
		return -1;
	}
	//Send render manager
	GameLevel::Init(render_manager);
	//Show the Window
	ShowWindow(window_handle, nCmdShow);
	//Load Level
	GameStateManager::LoadInitialLevel(new Level1());
	//Ship coordinates
	int x = 0 + O_CENTER_X;
	int y = 300 + O_CENTER_Y;

	//Infinite loop
	MSG msg;
	msg.message = WM_NULL;

	while (msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//Translate keystroke to message
			TranslateMessage(&msg);
			switch (msg.message)
			{
				case WM_LBUTTONUP:
				{
					x = LOWORD(msg.lParam);
					y = HIWORD(msg.lParam);
#ifdef DEBUG
					std::string s = "X : " + std::to_string(x) + " Y : " + std::to_string(y) + "\n";
					OutputDebugStringA(s.c_str());
#endif
				}
			}
			//Send message to window
			DispatchMessage(&msg);
		}
		else
		{
			//Render
			render_manager->BeginDraw();
			GameStateManager::Render();
			render_manager->EndDraw();
			PresentSwapChain(render_manager);
			try
			{
				GameStateManager::Update(x, y);
			}
			//End game
			catch (std::exception e)
			{
				std::string s = e.what();
				if (s == END_GAME)
				{
					x = 0 + O_CENTER_X;
					y = 300 + O_CENTER_Y;
				}
			}
			catch(std::pair<int,int> pair)
			{
				x = pair.first;
				y = pair.second;
			}
		}
	}

	delete render_manager;
	return 0;
}