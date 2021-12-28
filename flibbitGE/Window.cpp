#include "Window.h"

Window* window = NULL;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_CREATE: {
		window->onCreate();
	} break;
	case WM_DESTROY: {
		PostQuitMessage(0);
		window->onExit();
		return 0;
	} break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
}

Window::Window()
{
}

Window::~Window()
{
}

bool Window::InitializeWindow(int scrWidth, int scrHeight) {

	m_screenWidth = scrWidth;
	m_screenHeight = scrHeight;

	WNDCLASSEXW windowClass = { 0 };

	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WinProc;
	windowClass.hInstance = NULL;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"WNDClass";

	if (!::RegisterClassExW(&windowClass)) return false;

	if (!window) window = this;

	RECT windowClientRect{ 0, 0, scrWidth, scrHeight };
	::AdjustWindowRect(&windowClientRect, WS_OVERLAPPEDWINDOW, NULL);

	m_hWnd = ::CreateWindowExW(NULL, L"WNDClass",
		L"Just a regular window", WS_OVERLAPPEDWINDOW,
		10, 10,
		windowClientRect.right - windowClientRect.left,
		windowClientRect.bottom - windowClientRect.top,
		NULL, NULL, NULL, this);

	if (!m_hWnd) return false;

	::ShowWindow(m_hWnd, SW_SHOW);
	::UpdateWindow(m_hWnd);

	m_isRunning = true;
	return true;
}

bool Window::ReleaseWindow() {
	if (!::DestroyWindow(m_hWnd)) return false;
	return true;
}

bool Window::Cycle() {
	MSG message;
	while (true) {
		if (::PeekMessageW(&message, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&message);
			::DispatchMessageW(&message);

			if (message.message == WM_QUIT) break;
		}
	}

	window->onCycle();
	Sleep(1);
	
	return true;
}

bool Window::IsRunning() {
	return m_isRunning;
}

int Window::GetScreenSize(int axis)
{
	if (axis == 0) return m_screenWidth;
	else if (axis == 1) return m_screenHeight;
	else -1;
}

void Window::onCreate()
{
}

void Window::onExit()
{
	m_isRunning = false;
}

void Window::onCycle()
{
}
