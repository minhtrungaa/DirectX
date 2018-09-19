/*
	Handle the window respond to create a window and init DirectX
	TODO: later support OpenGL/Vulkan
*/

#include "stdafx.h"
#include "d3d_app.h"

class Application
{
public:
	void Init(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, int nCmdShow);
	int Run(int nWidth, int nHeight, char* cpWindowTitle);
	HWND& getHWND();

private:
	D3DApplication* m_pD3DApp;
	HWND m_hWND;
	HINSTANCE m_hInstance;
	HINSTANCE m_hPrevInstance;	// Not using
	LPSTR m_lpCmdLine;	// Not using
	int m_nCmdShow;

	bool m_bRequestQuit;
};