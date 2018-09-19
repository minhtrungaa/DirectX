#include "application.h"

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
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
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
		300,    // x-position of the window
		200,    // y-position of the window
		wr.right - wr.left,    // width of the window after adjust overlap border
		wr.bottom - wr.top,    // height of the window after adjust overlap border
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		m_hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(m_hWND, m_nCmdShow);

	m_pD3DApp->init3D(m_hWND);

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

		// TODO: Update game loop here
		m_pD3DApp->renderFrame();
	}

	m_pD3DApp->clean3D();
	delete m_pD3DApp;

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

HWND & Application::getHWND()
{
	return m_hWND;
}
