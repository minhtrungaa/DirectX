#include <Windows.h>
#include "stdafx.h"
#include "application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application D3App;
	D3App.Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	return D3App.Run(1280, 720, "My Window title");
}