#pragma once
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include "Swapchain.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

class Swapchain;

class Graphics
{
private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	ID3D11RenderTargetView* backbuffer;
	ID3D11Buffer* pVBuffer;
	ID3D11InputLayout* pLayout;

	ID3D11VertexShader* pVS;
	ID3D11PixelShader* pPS;
	
public:
	static Graphics* GraphicsSingleton();

public:
	void InitializeD3D();
	void CleanD3D(void);

	void RenderFrame(void);
	void InitializePipeline(void);
	void InitializeGraphics();

	struct VERTEX {
		FLOAT X, Y, Z;
		D3DXCOLOR Color;
	};

public:
	Swapchain* CreateSwapChain();
	ID3D11DeviceContext* GetDeviceContext();

private:
	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;

private:
	friend class Swapchain;
};

