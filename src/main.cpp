#include "Engine/ExecutionContext.h"
#include "Engine/Result.h"
#include "Foundation/Text.h"
#include "OS/OS.h"

#include <bit>
#include <cmath>
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
	
	std::u8string testExprU8 = std::u8string(
u8"samples1 = linspace( 0.0, 1, 16, false );\r\n"
u8"samples2 = linspace( 0.1, 1, 16, false );\r\n"
u8"samples3 = linspace( 0.2, 1, 16, false );\r\n"
u8"samples4 = linspace( 0.3, 1, 16, false );\r\n"
u8"fracArray = linspace( 0.5 - 0.3, 0.5 + 0.3, 16, false );\r\n"
u8"s1p2 = __m512( samples3 );\r\n"
u8"half = _mm512_set1_ps( 1.0f / 2.0f );\r\n"
u8"sNeg1p2 = __m512( samples1 );\r\n"
u8"quarter = _mm512_set1_ps( 1.0f / 4.0f );\r\n"
u8"\r\n"
u8"// float y1MinusM1 = samples[1+2] - samples[-1+2];\r\n"
u8"y1MinusM1 = _mm512_sub_ps( s1p2, sNeg1p2 );\r\n"
u8"\r\n"
u8"// Load the inputs.\r\n"
u8"s0p2 = __m512( samples2 );\r\n"
u8"\r\n"
u8"// float c0 = (1.0f / 2.0f) * samples[0+2] + (1.0f / 4.0f) * (samples[-1+2] + samples[1+2]);\r\n"
u8"c0 = _mm512_add_ps( _mm512_mul_ps( half, s0p2 ), _mm512_mul_ps( quarter, _mm512_add_ps( sNeg1p2, s1p2 ) ) );\r\n"
u8"\r\n"
u8"// Load the inputs.\r\n"
u8"s2p2 = __m512( samples4 );\r\n"
u8"\r\n"
u8"// float c1 = (1.0f / 2.0f) * y1MinusM1;\r\n"
u8"c1 = _mm512_mul_ps( half, y1MinusM1 );\r\n"
u8"\r\n"
u8"// Load the inputs.\r\n"
u8"thisFrac = __m512( fracArray );\r\n"
u8"\r\n"
u8"// float c2 = (1.0f / 4.0f) * (samples[2+2] - samples[0+2] - y1MinusM1);\r\n"
u8"c2 = _mm512_mul_ps( quarter, _mm512_sub_ps( _mm512_sub_ps( s2p2, s0p2 ), y1MinusM1 ) );\r\n"
u8"\r\n"
u8"// return (c2 * thisFrac + c1) * thisFrac + c0;\r\n"
u8"result = _mm512_add_ps( _mm512_mul_ps( _mm512_add_ps( _mm512_mul_ps( c2, thisFrac ), c1 ), thisFrac ), c0 );" );

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
