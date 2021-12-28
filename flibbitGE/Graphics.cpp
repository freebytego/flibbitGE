#include "Graphics.h"

Graphics* Graphics::GraphicsSingleton()
{
	static Graphics engine;
	return &engine;
}

void Graphics::InitializeD3D() {
	// Init D3D
	D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL,
		NULL, NULL, D3D11_SDK_VERSION, &m_device, NULL, &m_deviceContext);
	
	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	//InitializePipeline();
	//InitializeGraphics();
}

void Graphics::CleanD3D(void) {

	pVS->Release();
	pPS->Release();
	pVBuffer->Release();
	pLayout->Release();
	backbuffer->Release();
	m_device->Release();
	m_deviceContext->Release();

	m_dxgi_adapter->Release();
	m_dxgi_device->Release();
	m_dxgi_factory->Release();
}

void Graphics::RenderFrame(void) {
	// Clearing the backbuffer and filling it with the deep blue color
	m_deviceContext->ClearRenderTargetView(backbuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

	// Drawing a triangle
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	m_deviceContext->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_deviceContext->Draw(6, 0);

	// Swapping the buffers
	//swapchain->Present(0, 0);
}

void Graphics::InitializePipeline(void) {
	// Load shaders and compile them
	ID3D10Blob* VS, * PS;
	D3DX11CompileFromFile(L"shaders.shader", 0, 0,
		"VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile(L"shaders.shader", 0, 0,
		"PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	// Encapsulate shaders
	m_device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	m_device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	m_deviceContext->VSSetShader(pVS, 0, 0);
	m_deviceContext->PSSetShader(pPS, 0, 0);

	// Create the Input Layout Object

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	m_device->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	m_deviceContext->IASetInputLayout(pLayout);
}

void Graphics::InitializeGraphics()
{
	VERTEX TriangleVertices[] =
	{
		{-0.5f, -0.5f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)},
		{-0.5f, 0.5, 0.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)},
		{0.5f, -0.5f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)},
		{0.5f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f)},
	};

	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(TriangleVertices);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	m_device->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	m_deviceContext->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, TriangleVertices, sizeof(TriangleVertices));
	m_deviceContext->Unmap(pVBuffer, NULL);

}

Swapchain* Graphics::CreateSwapChain()
{
	return new Swapchain();
}

ID3D11DeviceContext* Graphics::GetDeviceContext()
{
	return this->m_deviceContext;
}
