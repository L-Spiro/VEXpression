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
	auto Cool = ((0xBadBeefBull << 1ULL) + 36) / 500;;
	auto Cool2 = --Cool;
	
	std::string testExpr = "Cool = ((0xBadBeefBull << 1ULL) + 36) / 500;;\r\n--Cool / 1";
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