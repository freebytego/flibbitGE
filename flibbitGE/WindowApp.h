#pragma once
#include "Window.h"
#include "Graphics.h"
#include "Swapchain.h"

class WindowApp : public Window
{
public:
	WindowApp();
	~WindowApp();
	// Inherited via Window
	virtual void onCreate() override;
	virtual void onExit() override;
	virtual void onCycle() override;
private:
	Swapchain* m_swapChain;
	D3D11_VIEWPORT m_viewport;
};

