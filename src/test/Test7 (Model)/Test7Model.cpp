#include "Test7Model.h"
#include "../../graphics/buffer/VertexDeclaration.h"
#include "../../graphics/buffer/IndexBuffer.h"
#include "../../graphics/model/Model.h"
#include "../../graphics/model/ModelMesh.h"
#include "../../graphics/model/ModelMeshPart.h"

void Test7Model::CreateVertexBuffer() {
	VF::Graphics::VertexDeclaration ** vertices = new VF::Graphics::VertexDeclaration*[4];
	vertices[0] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(1.0f, 1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(1.0f, 1.0f, 0.5f, 1.0f)))->end();
	vertices[1] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(-1.0f, 1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)))->end();
	vertices[2] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(-1.0f, -1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(0.5f, 1.0f, 1.0f, 1.0f)))->end();
	vertices[3] = (new VF::Graphics::VertexDeclaration())->begin()->addVertexElement(new VF::Graphics::PositionVertexElement(VF::Math::Vector3(1.0f, -1.0f, 0.0f)))
		->addVertexElement(new VF::Graphics::ColorVertexElement(VF::Math::Vector4(1.0f, 0.5f, 1.0f, 1.0f)))->end();
	vertexBuffer = new VF::Graphics::VertexBuffer(graphicsDevice, 4);
	vertexBuffer->SetData(vertices);
}

void Test7Model::CreateIndexBuffer() {
	static unsigned int indices[6] = { 0, 1, 2,
		2, 3, 0 };
	indexBuffer = new VF::Graphics::IndexBuffer(graphicsDevice, 6);
	indexBuffer->SetData(indices);
}

void Test7Model::CreateEffect() {
	basicEffect = new VF::Graphics::BasicEffect();
	basicEffect->projectionViewWorld.projection = camera->GetProjectionMatrix();
	basicEffect->projectionViewWorld.view = camera->GetViewMatrix();
	basicEffect->projectionViewWorld.world = VF::Math::rotate(VF::Math::Matrix4(1.0f), VF::Math::radians(90.0f), VF::Math::Vector3(1, 0, 0)) * VF::Math::translate(VF::Math::mat4(1.0f), VF::Math::Vector3(0, 0, 0));
}

void Test7Model::CreateModel() {
	VF::Graphics::ModelMeshPart * modelMeshPart = new VF::Graphics::ModelMeshPart();
	modelMeshPart->vertexBuffer = vertexBuffer;
	modelMeshPart->indexBuffer = indexBuffer;
	modelMeshPart->effect = basicEffect;
	std::vector<VF::Graphics::ModelMeshPart *> modelMeshParts; modelMeshParts.push_back(modelMeshPart);
	VF::Graphics::ModelMesh * modelMesh = new VF::Graphics::ModelMesh(graphicsDevice, modelMeshParts);
	std::vector<VF::Graphics::ModelMesh *> modelMeshes; modelMeshes.push_back(modelMesh);
	model = new VF::Graphics::Model(graphicsDevice, modelMeshes);
}

void Test7Model::SetupCamera() {
	VF::Camera::PerspectiveProjectionParameters parameters;
	parameters.fieldOfView = 45.0f;
	parameters.width = 640;
	parameters.height = 480;
	parameters.nearClip = 0.1f;
	parameters.farClip = 1000.0f;
	camera = new VF::Camera::FirstPersonCamera(parameters, VF::Math::Vector3(0, 0, -10), VF::Math::Vector3(0, 0, 0));
	VF::Input::Mouse::SetMouseInputMode(window, true, false);
}

void Test7Model::Init() {
	monitorManager = new VF::Window::MonitorManager();
	monitor = monitorManager->GetPrimaryMonitor();
	monitors = monitorManager->GetMonitors();
	windowManager = new VF::Window::WindowManager();
	window = new VF::Window::Window(640, 480, "Test 6 Camera");
	windowManager->AddWindow(window);
	VF::Graphics::Viewport viewPort;
	graphicsDevice = new VF::Graphics::GraphicsDevice(window, viewPort);
	graphicsDevice->Init();
	SetupCamera();
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateEffect();
	CreateModel();
}

void Test7Model::Update() {
	if (window->IsOpen()) {
		windowManager->PollForEvents();
		graphicsDevice->Clear();
		UpdateCamera();
		Draw();
		graphicsDevice->Present();
	}
	else {
		running = false;
	}
}

void Test7Model::Draw() {
	model->Draw(camera->GetProjectionMatrix(), camera->GetViewMatrix(), VF::Math::Matrix4(1.0f));
}

void Test7Model::UpdateCamera() {
	VF::Input::Keyboard::GetState(window, keyboardState);
	VF::Input::Mouse::GetState(window, mouseState);
	camera->Move(window, keyboardState, mouseState);
	if (keyboardState.IsKeyDown(VF::Input::Keys::Escape)) {
		running = false;
	}
	camera->Update();
}

void Test7Model::Shutdown() {
	graphicsDevice->Shutdown();
	windowManager->ShutDown();
}