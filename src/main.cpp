#include "Engine/ExecutionContext.h"
#include "Engine/Result.h"
#include "Foundation/Text.h"
#include "OS/OS.h"

#include <bit>
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
			if (res.value.objectVal) {
				std::string utf8Str;
				
				if (res.value.objectVal->toString(utf8Str, 0, 0)) {
					std::cout << utf8Str << " (Object)\n";
				}
				else {
					std::cout << "[Object String Conversion Failed]\n";
				}
			}
			else {
				std::cout << "[Null Object Pointer]\n";
			}
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
#ifdef _WIN32
    ::SetConsoleOutputCP(65001); 
#endif
	std::cout << "--- VEXpression Engine Test ---\n\n";

	ve::ExecutionContext context;
	auto Cool = HUGE_VALF / 2;
	
	std::u8string testExprU8 = std::u8string( u8"val = (float)uint32_t(90.2 * 1000)" );

	std::string testExpr(reinterpret_cast<const char*>(testExprU8.data()), testExprU8.size());
	std::cout << "Evaluating: " << testExpr << "\r\n\r\n";
	if (!context.compile(testExpr)) {
		std::cout << "Syntax Error\n";
	}
	else {
		try {
			context.setUserValue(ve::Result::make(3));
			context.setParm(ve::Result::make(4.5), 9);
			ve::Result res = context.execute();
	
			printResult(res);
		}
		catch (...) {
		}
	}
	
	return 0;
}