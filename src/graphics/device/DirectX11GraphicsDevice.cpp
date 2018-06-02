#include "DirectX11GraphicsDevice.h"
#include "../buffer/DirectX11VertexBuffer.h"
#include "../effect/IEffect.h"
#include "D3Dcompiler.h"

VF::Graphics::DirectX11GraphicsDevice::DirectX11GraphicsDevice() {

}

VF::Graphics::DirectX11GraphicsDevice::DirectX11GraphicsDevice(VF::Window::IWindow * window) {
	this->window = window;
	viewPort = new VF::Graphics::Viewport(window->GetMonitor()->GetPosition()->x, window->GetMonitor()->GetPosition()->y,
		window->width, window->height);
}

void VF::Graphics::DirectX11GraphicsDevice::Init() {
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = (HWND) window->GetWindowHandle();
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		NULL,
		&deviceContext);

	ID3D11Texture2D *pBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	device->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer);
	pBackBuffer->Release();

	deviceContext->OMSetRenderTargets(1, &backBuffer, NULL);

	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = (FLOAT) viewPort->GetX();
	viewport.TopLeftY = (FLOAT) viewPort->GetY();
	viewport.Width = (FLOAT) viewPort->GetWidth();
	viewport.Height = (FLOAT) viewPort->GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, &viewport);
}

void VF::Graphics::DirectX11GraphicsDevice::Clear() {
	float color[4] = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };
	deviceContext->ClearRenderTargetView(backBuffer, color);
}

void VF::Graphics::DirectX11GraphicsDevice::Present() {
	swapChain->Present(0, 0);
}

void VF::Graphics::DirectX11GraphicsDevice::DrawPrimitives(IVertexBuffer * vertexBuffer, IEffect * effect) {

	DirectX11VertexBuffer * vb = (DirectX11VertexBuffer *)vertexBuffer;

	vb->SetBuffer();
	vb->SetInputLayout(effect);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	effect->Apply();

	deviceContext->Draw(3, 0);
}

void VF::Graphics::DirectX11GraphicsDevice::DrawIndexedPrimitives() {

}

void VF::Graphics::DirectX11GraphicsDevice::Shutdown() {
	deviceContext->Release();
	swapChain->Release();
	device->Release();
}

void * VF::Graphics::DirectX11GraphicsDevice::GetDevice() {
	return (void * ) device;
}