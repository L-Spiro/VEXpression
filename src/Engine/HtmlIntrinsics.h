#pragma once

#include "../Foundation/Html.h"
#include "../Foundation/Text.h"
#include "ExecutionContext.h"
#include "String.h"

namespace ve {

	/**
	 * Provides built-in intrinsic function callbacks for exposing the HTML entity table to scripts.
	 **/
	class HtmlIntrinsics {
	public :
		// == Functions.

		/**
		 * Intrinsic callback: htmlCount()
		 * 
		 * \param ctx			The execution context for allocation.
		 * \return				Returns an Unsigned Result containing the total number of HTML entities.
		 **/
		static Result						htmlCount(ExecutionContext* ctx) {
			static_cast<void>(ctx);
			return Result{ .type = NumericConstant::Unsigned, .value = { .uintVal = static_cast<uint64_t>(Html::totalNames()) } };
		}

		/**
		 * Intrinsic callback: htmlName(index)
		 * 
		 * \param ctx			The execution context for allocation.
		 * \param arg			The index of the entity to look up.
		 * \return				Returns a String Result containing the entity name, or invalid if out of bounds.
		 **/
		static Result						htmlName(ExecutionContext* ctx, const Result& arg) {
			size_t idx = 0;
			
			if (arg.type == NumericConstant::Signed) {
				if (arg.value.intVal < 0) {
					return Result{ .type = NumericConstant::Invalid };
				}
				idx = static_cast<size_t>(arg.value.intVal);
			}
			else if (arg.type == NumericConstant::Unsigned) {
				idx = static_cast<size_t>(arg.value.uintVal);
			}
			else {
				return Result{ .type = NumericConstant::Invalid };
			}

			std::string name;
			Html::getName(name, idx);
			
			if (!name.empty()) {
				String* strObj = ctx->allocateObject<String>();
				
				if (strObj) {
					strObj->assignUtf8(name.data(), name.length());
					return strObj->createResult();
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}

		/**
		 * Intrinsic callback: htmlChar(index) OR htmlChar(name)
		 * 
		 * \param ctx			The execution context for allocation.
		 * \param arg			The index (numeric) or name (string) of the entity to resolve.
		 * \return				Returns a String Result containing the 1 or 2 UTF-8 characters, or invalid if not found.
		 **/
		static Result						htmlChar(ExecutionContext* ctx, const Result& arg) {
			uint64_t code = static_cast<uint64_t>(Html::InvalidCode::Invalid);
			
			if (arg.type == NumericConstant::Signed || arg.type == NumericConstant::Unsigned) {
				size_t idx = 0;
				
				if (arg.type == NumericConstant::Signed) {
					if (arg.value.intVal >= 0) {
						idx = static_cast<size_t>(arg.value.intVal);
					}
					else {
						return Result{ .type = NumericConstant::Invalid };
					}
				}
				else {
					idx = static_cast<size_t>(arg.value.uintVal);
				}
				
				std::string name;
				Html::getName(name, idx);
				
				if (!name.empty()) {
					code = Html::getCode(name.c_str(), name.length());
				}
			}
			else if (arg.type == NumericConstant::Object && arg.value.objectVal != nullptr) {
				if (arg.value.objectVal->type() == BuiltInType_String) {
					std::wstring wStr;
					
					// Assuming ToStringFlag_None is 0 or explicitly handled
					if (arg.value.objectVal->toString(wStr, 0, 0)) {
						std::string name;
						name.reserve(wStr.length());
						
						// Fast cast since HTML names are strictly ASCII
						for (size_t i = 0; i < wStr.length(); ++i) {
							name.push_back(static_cast<char>(wStr[i]));
						}
						
						code = Html::getCode(name.c_str(), name.length());
					}
				}
			}
			
			if (code != static_cast<uint64_t>(Html::InvalidCode::Invalid)) {
				std::string utf8Payload;
				uint32_t lower = static_cast<uint32_t>(code & 0xFFFFFFFF);
				uint32_t upper = static_cast<uint32_t>(code >> 32);
				
				Text::appendUtf8(utf8Payload, lower);
				
				if (upper != 0) {
					Text::appendUtf8(utf8Payload, upper);
				}
				
				String* strObj = ctx->allocateObject<String>();
				
				if (strObj) {
					strObj->assignUtf8(utf8Payload.data(), utf8Payload.length());
					return strObj->createResult();
				}
			}
			
			return Result{ .type = NumericConstant::Invalid };
		}
	};

}	// namespace ve
