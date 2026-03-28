#include "Engine/ExecutionContext.h"
#include "Engine/Result.h"
#include <iostream>
#include <string>

/**
 * A simple helper function to print the strongly-typed Result union.
 **/
void printResult(const ve::Result& res) {
	std::cout << "Result: ";
	switch (res.type) {
		case ve::NumericConstant::Unsigned : {
			std::cout << res.value.uintVal << " (Unsigned)\n";
			break;
		}
		case ve::NumericConstant::Signed : {
			std::cout << res.value.intVal << " (Signed)\n";
			break;
		}
		case ve::NumericConstant::Floating : {
			std::cout << res.value.doubleVal << " (Floating)\n";
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
	auto coolType = 0xBadBeefULL + 634U;
	
	std::string testExpr = "0xBadBeefULL + 634U";
	std::cout << "Evaluating: " << testExpr << "\n";
	
	context.compile(testExpr);
	
	ve::Result res = context.execute();
	
	printResult(res);
	
	return 0;
}