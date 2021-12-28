#include "WindowApp.h"

WindowApp::WindowApp()
{
}

WindowApp::~WindowApp()
{
}

void WindowApp::onCreate()
{
	Window::onCreate();
	Graphics::GraphicsSingleton()->InitializeD3D();
	m_swapChain = Graphics::GraphicsSingleton()->CreateSwapChain();
	m_swapChain->Initialize(this->m_hWnd, GetScreenSize(0), GetScreenSize(1));

	// Set up the viewport

	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;
	m_viewport.Width = GetScreenSize(0);
	m_viewport.Height = GetScreenSize(1);

	Graphics::GraphicsSingleton()->GetDeviceContext()->RSSetViewports(1, &m_viewport);

}

void WindowApp::onExit()
{
	Window::onExit();
	Graphics::GraphicsSingleton()->CleanD3D();
	m_swapChain->Release();
}

void WindowApp::onCycle()
{
	Window::onCycle();
}

