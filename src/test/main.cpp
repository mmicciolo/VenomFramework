#include <vector>

#include "ITest.h"
#include "Test1 (Window)\Test1Window.h"
#include "Test2 (Input)\Test2Input.h"
#include "Test3 (GraphicsDevice)\Test3GraphicsDevice.h"
#include "Test4 (VertexBuffer)\Test4VertexBuffer.h"
#include "Test5 (IndexBuffer)\Test5IndexBuffer.h"
#include "Test6 (Camera)\Test6Camera.h"

namespace TestTypes {
	enum Types {
		Test1Window,
		Test2Input,
		Test3GraphicsDevice,
		Test4VertexBuffer,
		Test5IndexBuffer,
		Test6Camera
	};
}


std::vector<ITest *> tests;
TestTypes::Types testType = TestTypes::Test5IndexBuffer;

void SetupTests() {
	tests.push_back(new Test1Window());
	tests.push_back(new Test2Input());
	tests.push_back(new Test3GraphicsDevice());
	tests.push_back(new Test4VertexBuffer());
	tests.push_back(new Test5IndexBuffer());
	tests.push_back(new Test6Camera());
}

int main() {

	SetupTests();

	ITest * test = tests.at(testType);

	test->Init();

	while (test->Running()) {
		test->Update();
	}

	test->Shutdown();
}