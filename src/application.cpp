#include "application.h"
#include <stdio.h>

ID3D11InputLayout *pLayout;            // the pointer to the input layout
ID3D11VertexShader *pVS;               // the pointer to the vertex shader
ID3D11PixelShader *pPS;                // the pointer to the pixel shader
ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer

									   // a struct to define a single vertex
struct VERTEX { FLOAT X, Y, Z; D3DXCOLOR Color; };

// this is the function that creates the shape to render
void InitGraphics()
{
	// create a triangle using the VERTEX struct
	// TODO: read vertex from file here
	VERTEX OurVertices[] =
	{
		{ 0.0f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
		{ 0.45f, -0.5, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
		{ -0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) }
	};


	// create the vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	D3DApplication::m_pDevice->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


												   // copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	D3DApplication::m_pDevContext->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	D3DApplication::m_pDevContext->Unmap(pVBuffer, NULL);                                      // unmap the buffer
}


// this function loads and prepares the shaders
void InitPipeline()
{
	// load and compile the two shaders
	ID3D10Blob *VS, *PS;
	D3DX11CompileFromFile("shaders\\shader.shader", 0, 0, "VShader", "vs_5_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile("shaders\\shader.shader", 0, 0, "PShader", "ps_5_0", 0, 0, 0, &PS, 0, 0);

	// encapsulate both shaders into shader objects
	D3DApplication::m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	D3DApplication::m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	// set the shader objects
	D3DApplication::m_pDevContext->VSSetShader(pVS, 0, 0);
	D3DApplication::m_pDevContext->PSSetShader(pPS, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	D3DApplication::m_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	D3DApplication::m_pDevContext->IASetInputLayout(pLayout);
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Application::Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// holding the member

	m_hInstance = hInstance;
	m_nCmdShow = nCmdShow;

	m_pD3DApp = new D3DApplication();

	m_bRequestQuit = false;
}

int Application::Run(int nWidth, int nHeight, char* cpWindowTitle)
{
	// the handle for the window, filled by a function

	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	// wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "MainWnd";

	// register the window class
	RegisterClassEx(&wc);

	// Adjust for render graphic onto client side with the size input for window
	RECT wr = { 0, 0, nWidth, nHeight }; // config size here
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);	// adjusting here

	// create the window and use the result as the handle
	m_hWND = CreateWindowEx(NULL,
		"MainWnd",    // name of the window class
		cpWindowTitle,   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		240,    // x-position of the window
		93,    // y-position of the window
		wr.right - wr.left,    // width of the window after adjust overlap border
		wr.bottom - wr.top,    // height of the window after adjust overlap border
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		m_hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(m_hWND, m_nCmdShow);

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);


	//m_pD3DApp->init3D(m_hWND, nWidth, nHeight);
	D3DApplication::init3D(m_hWND, nWidth, nHeight);
	InitPipeline();
	InitGraphics();

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg;

	// Using peekmessage instead
	// wait for the next message in the queue, store the result in 'msg'
	//while (GetMessage(&msg, NULL, 0, 0))
	//{
	//	// translate keystroke messages into the right format
	//	TranslateMessage(&msg);

		// send the message to the WindowProc function
	//	DispatchMessage(&msg);
	//}

	m_pScene->Init();

	// enter Application loop
	while (!m_bRequestQuit) // TODO: Using variable and set it to false when comes to exit the loop/application
	{
		// check event by using PeekMessage
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate event input
			TranslateMessage(&msg);

			// send or dispatch message to WinProc function
			DispatchMessage(&msg);

			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				m_bRequestQuit = true;
		}

		m_pScene->Scene::Update(0);
		m_pScene->Update(0);

		// TODO: Update game loop here
		//m_pD3DApp->renderFrame();
		//m_pD3DApp->clearFrame();
		D3DApplication::clearFrame();
		m_pScene->Render();

		// select which vertex buffer to display
		UINT stride = sizeof(VERTEX);
		UINT offset = 0;
		D3DApplication::m_pDevContext->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

		// select which primtive type we are using
		D3DApplication::m_pDevContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// draw the vertex buffer to the back buffer
		D3DApplication::m_pDevContext->Draw(3, 0);

		//m_pD3DApp->swapBuffer();
		D3DApplication::swapBuffer();
	}

	D3DApplication::clean3D();
	//m_pD3DApp->clean3D();
	//delete m_pD3DApp;

	pLayout->Release();
	pVS->Release();
	pPS->Release();
	pVBuffer->Release();

	delete m_pScene;

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

HWND & Application::getHWND()
{
	return m_hWND;
}

void Application::setStartUpScene(Scene * pScene)
{
	m_pScene = pScene;
}
