#include "Swapchain.h"

bool Swapchain::Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight)
{
	ID3D11Device* device = Graphics::GraphicsSingleton()->m_device;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Width = screenWidth;
	scd.BufferDesc.Height = screenHeight;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT HR = Graphics::GraphicsSingleton()->m_dxgi_factory->CreateSwapChain(
		device, &scd, &m_swapChain
	);

	if (FAILED(HR)) return false;

	HRESULT HS = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pBackBuffer);
	Graphics::GraphicsSingleton()->m_device->CreateRenderTargetView(m_pBackBuffer, NULL, &m_backbuffer);
	m_pBackBuffer->Release();
	Graphics::GraphicsSingleton()->GetDeviceContext()->OMSetRenderTargets(1, &m_backbuffer, NULL);

    return true;
}

bool Swapchain::Release()
{
	m_swapChain->SetFullscreenState(FALSE, NULL);
	m_swapChain->Release();
	delete this;
    return true;
}
