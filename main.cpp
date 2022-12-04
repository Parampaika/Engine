#include <iostream>
#include "wrapper.h"
#include "engine.h"


class TestAdding {
public:
	int addTwo(int a, int b) {
		return a + b;
	}
};

class TestMut {
public:
	int mutTwo(int a, int b, int c) {
		return a * b / c;
	}
};



int main(void) {
	try {
		TestAdding A;
 		Wrapper wrapper1(&A, &TestAdding::addTwo, { {"arg1", 0}, {"arg2", 0} });
		Engine engine;
		engine.register_command(&wrapper1, "sum");
		std::cout << "5 + 12 = " << engine.execute("sum", { {"arg1", 5}, {"arg2", 12} }) << std::endl;

		TestMut B;
		Wrapper wrapper2(&B, &TestMut::mutTwo, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });
		Engine engine1;
		engine1.register_command(&wrapper2, "command");
		std::cout << "5 * 12 / 5 = " << engine1.execute("command", { {"arg1", 5}, {"arg2", 12}, {"arg3", 5} }) << std::endl;

	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}