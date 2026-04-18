#include "Engine/ExecutionContext.h"
#include "Engine/Result.h"
#include "Foundation/Text.h"
#include <iostream>
#include <string>

/**
 * A simple helper function to print the strongly-typed Result union.
 **/
void printResult(const ve::Result& res) {
	std::cout << "Result: ";
	switch (res.type) {
		case ve::NumericConstant::Unsigned : {
			std::cout << ve::Text::toUnsigned( res.value.uintVal ) << " (Unsigned)\n";
			break;
		}
		case ve::NumericConstant::Signed : {
			std::cout << ve::Text::toSigned( res.value.intVal ) << " (Signed)\n";
			break;
		}
		case ve::NumericConstant::Floating : {
			std::cout << ve::Text::toDouble( res.value.doubleVal ) << " (Floating)\n";
			break;
		}
		case ve::NumericConstant::Object : {
			std::cout << "[Object Pointer]\n";
			break;
		}
		case ve::NumericConstant::Invalid : {}
		default : {
			std::cout << "[Invalid or Uninitialized]\n";
			break;
		}
	}
	std::cout << "\n";
}

int main() {
	std::cout << "--- VEXpression Engine Test ---\n\n";

	ve::ExecutionContext context;
	auto Cool = 3600 / 500;
	auto Cool2 = Cool / 1;
	auto Cool3 = Cool2 + 89.05;
	
	std::string testExpr = "B = powf(A = M_E, 2);\r\nB + A // Expected: 10.1073379273896950536482108873315155506134033203125";
	std::cout << "Evaluating: " << testExpr << "\n";
	
	context.compile(testExpr);
	try {
		ve::Result res = context.execute();
	
		printResult(res);
	}
	catch (...) {
	}
	
	return 0;
}