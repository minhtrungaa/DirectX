#pragma once
/*
	Handle Direct X init pipe line
*/

#include "stdafx.h"

class D3DApplication
{
public:
	void init3D(HWND hWnd, int nScreenWidth = -1, int nScreenHeight = -1);	// setup Direct3D driver
	void clean3D(void);	// release the Direct3D driver
	void renderFrame(void); // render single frame using the backbuffer to render to viewport
	void clearFrame(void);
	void swapBuffer(void);

	// the pointer to the swap chain interface
	IDXGISwapChain* m_pSwapchain;
											  
	// the pointer to our Direct3D device interface
	ID3D11Device* m_pDevice;
	
	// the pointer to our Direct3D device context
	ID3D11DeviceContext* m_pDevContext;

	// back buffer for swap chain
	ID3D11RenderTargetView* m_pBackBuffer;
};