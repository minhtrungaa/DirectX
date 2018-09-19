#pragma once
/*
	Handle Direct X init pipe line
*/

#include "stdafx.h"

class D3DApplication
{
public:
	static void init3D(HWND hWnd, int nScreenWidth = -1, int nScreenHeight = -1);	// setup Direct3D driver
	static void clean3D(void);	// release the Direct3D driver
	static void renderFrame(void); // render single frame using the backbuffer to render to viewport
	static void clearFrame(void);
	static void swapBuffer(void);

	// the pointer to the swap chain interface
	static IDXGISwapChain* m_pSwapchain;
											  
	// the pointer to our Direct3D device interface
	static ID3D11Device* m_pDevice;
	
	// the pointer to our Direct3D device context
	static ID3D11DeviceContext* m_pDevContext;

	// back buffer for swap chain
	static ID3D11RenderTargetView* m_pBackBuffer;
};