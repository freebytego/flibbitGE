#pragma once
#include <D3D11.h>
#include "Graphics.h"

class Swapchain
{
public:
	bool Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight);
	bool Release();
	HRESULT GetBuffer(UINT buffer, ID3D11Texture2D* pBackBuffer);

private:
	IDXGISwapChain* m_swapChain;

	ID3D11Texture2D* m_pBackBuffer;
	ID3D11RenderTargetView* m_backbuffer;

};

