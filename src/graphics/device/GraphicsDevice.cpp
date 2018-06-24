#include "GraphicsDevice.h"
#include "../buffer/VertexBuffer.h"
#include "../buffer/IndexBuffer.h"
#include <bgfx/platform.h>

VF::Graphics::GraphicsDevice::GraphicsDevice(VF::Window::IWindow * window, Viewport viewPort) {
	this->window = window;
	this->viewPort = viewPort;
}

bool VF::Graphics::GraphicsDevice::Init() {
	bgfx::PlatformData pd;
	memset(&pd, 0, sizeof(pd));
	pd.nwh = window->GetWindowHandle();
	bgfx::setPlatformData(pd);
	bgfx::Init init;
	init.type = bgfx::RendererType::Direct3D11;
	init.resolution.width = 640;
	init.resolution.height = 480;
	bgfx::init(init);
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
	);
	return true;
}

void VF::Graphics::GraphicsDevice::Clear() {
	bgfx::setViewRect(0, 0, 0, 640, 480);
	bgfx::touch(0);
}

void VF::Graphics::GraphicsDevice::Present() {
	bgfx::frame();
}

void VF::Graphics::GraphicsDevice::DrawPrimitives(VertexBuffer * vertexBuffer, Effect * effect) {
	vertexBuffer->SetBuffer();

	bgfx::setState(BGFX_STATE_DEFAULT);

	effect->Apply();

	bgfx::submit(0, effect->GetShader()->programHandle);
}

void VF::Graphics::GraphicsDevice::DrawIndexedPrimitives(VertexBuffer * vertexBuffer, IndexBuffer * indexBuffer, Effect * effect) {
	vertexBuffer->SetBuffer();
	indexBuffer->SetBuffer();

	uint64_t state = 0            
		| BGFX_STATE_WRITE_RGB       
		| BGFX_STATE_WRITE_A         
		| BGFX_STATE_WRITE_Z         
		| BGFX_STATE_DEPTH_TEST_LESS 
		| BGFX_STATE_CULL_CCW         
		| BGFX_STATE_MSAA;           

	bgfx::setState(BGFX_STATE_DEFAULT);

	effect->Apply();

	bgfx::submit(0, effect->GetShader()->programHandle);
}

void VF::Graphics::GraphicsDevice::Shutdown() {

}