#include "..\include\d3d_app.h"

void D3DApplication::init3D(HWND hWnd, int nScreenWidth, int nScreenHeight)
{
	// Init D3D
	// create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;

	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	
	// toggling between full screen and window
	scd.BufferDesc.Width = nScreenWidth;
	scd.BufferDesc.Height = nScreenHeight;
	
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = hWnd;                                // the window to be used
	scd.SampleDesc.Count = 4;                               // how many multisamples simply AA
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// allow full-screen switching

	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_pSwapchain,
		&m_pDevice,
		NULL,
		&m_pDevContext);

	// Setting up BackBuffer render target
	// get the address of the back buffer for woring with swap chain
	ID3D11Texture2D* pBackBuffer;
	m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer adress to create the render target
	// this require like other so we could render to back offer then swap
	m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pBackBuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	m_pDevContext->OMSetRenderTargets(1, &m_pBackBuffer, NULL);

	// Setting up viewport to render on it
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;

	m_pDevContext->RSSetViewports(1, &viewport);
}



void D3DApplication::clean3D(void)
{
	// force to be window to propperly release COMs
	m_pSwapchain->SetFullscreenState(FALSE, NULL);

	m_pSwapchain->Release();
	m_pDevice->Release();
	m_pDevContext->Release();
	m_pBackBuffer->Release();
}

void D3DApplication::renderFrame(void)
{
	// clear the previous frame with color
	m_pDevContext->ClearRenderTargetView(m_pBackBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

	// call game render here

	// switching back buffer and front
	m_pSwapchain->Present(0, 0);
}
