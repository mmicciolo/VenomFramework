#include "DirectX11GraphicsDevice.h"
#include "../buffer/DirectX11VertexBuffer.h"
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

	Init2();
}

void VF::Graphics::DirectX11GraphicsDevice::Clear() {
	float color[4] = { 0.392156899f, 0.584313750f, 0.929411829f, 1.000000000f };
	deviceContext->ClearRenderTargetView(backBuffer, color);
}

void VF::Graphics::DirectX11GraphicsDevice::Present() {
	swapChain->Present(0, 0);
}

void VF::Graphics::DirectX11GraphicsDevice::Init2() {

	HRESULT h;

	/*struct VertexType
	{
		DirectX::XMFLOAT3 position;
	};

	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;
	VertexType* vertices = new VertexType[3];
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;

	vertices[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertices[1].position = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertices[2].position = DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f);

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * 3;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	h = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);*/

	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	ID3D10Blob* errorMessage = 0;

	h = D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vertexShaderBuffer, &errorMessage);
	h = D3DCompileFromFile(L"shader.hlsl", NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pixelShaderBuffer, &errorMessage);

	h = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	h = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);

	D3D11_INPUT_ELEMENT_DESC polygonLayout[1];
	unsigned int numElements;

	// This setup needs to match the VertexType stucture in the ModelClass and in the shader.
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	h = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);

	D3D11_BUFFER_DESC matrixBufferDesc;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	h = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

}

void VF::Graphics::DirectX11GraphicsDevice::DrawPrimitives(IVertexBuffer * vertexBuffer) {
	DirectX11VertexBuffer * vb = (DirectX11VertexBuffer *)vertexBuffer;
	//deviceContext->IASetVertexBuffers(0, 1, &vb->vertexBuffer, &stride, 0);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(0, 0, 0);

	DirectX::XMVECTOR eyePosition = DirectX::XMVectorSet(0, 0, -10, 1);
	DirectX::XMVECTOR focusPoint = DirectX::XMVectorSet(0, 0, 0, 1);
	DirectX::XMVECTOR upDirection = DirectX::XMVectorSet(0, 1, 0, 0);
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixLookAtLH(eyePosition, focusPoint, upDirection);

	DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 640 / 480, 0.1f, 100.0f);

	worldMatrix = DirectX::XMMatrixTranspose(worldMatrix);
	viewMatrix = DirectX::XMMatrixTranspose(viewMatrix);
	projectionMatrix = DirectX::XMMatrixTranspose(projectionMatrix);

	deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	unsigned int stride = 12;
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vb->vertexBuffer, &stride, &offset);
	//deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	deviceContext->VSSetConstantBuffers(0, 1, &m_matrixBuffer);

	// Render the triangle.
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