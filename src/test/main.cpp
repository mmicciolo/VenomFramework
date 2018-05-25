#include <vector>

#include "ITest.h"
#include "Test1 (Window)\Test1Window.h"
#include "Test2 (Input)\Test2Input.h"

namespace TestTypes {
	enum Types {
		Test1Window,
		Test2Input
	};
}


std::vector<ITest *> tests;
TestTypes::Types testType = TestTypes::Test2Input;

void SetupTests() {
	tests.push_back(new Test1Window());
	tests.push_back(new Test2Input());
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