#include <Windows.h>
#include "stdafx.h"
#include "application.h"
#include "main_scene.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application App;
	MainScene* MyScene = new MainScene();
	App.Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	App.setStartUpScene(MyScene);
	return App.Run(1440, 900, "My Window title");
}