#include <Windows.h>
#include "stdafx.h"
#include "application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application App;
	App.Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return App.Run(1280, 720, "My Window title");
}