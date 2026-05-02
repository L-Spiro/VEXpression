#pragma once

#include "../Strings/Strings.h"
#include "Result.h"

#include <vector>

namespace ve {

	class							ExecutionContext;

	/**
	 * Represents exact C-style data types for strict parameter casting and truncation.
	 **/
	enum class DataType {
		Int8,
		UInt8,
		Int16,
		UInt16,
		Int32,
		UInt32,
		Int64,
		UInt64,
		BFloat16,
		Float16,
		Float,
		Double,
		Pointer,
		Object,
		String,
		Integer,
		Any,
		Variadic
	};

	/**
	 * Metadata and type-enforcement for a single function parameter.
	 **/
	struct ParameterDef {
		DataType					type = DataType::Any;
		const char*					name = nullptr;
		StringId					description = StringId::None;
	};

	/**
	 * Callback signature for built-in intrinsic functions.
	 **/
	using IntrinsicCallback = Result (*)(ExecutionContext* ctx, const std::vector<Result>& args);

	/**
	 * Complete definition of a registered function, including documentation metadata.
	 **/
	struct FunctionDef {
		const char*					name = nullptr;
		StringId					description = StringId::None;
		std::vector<ParameterDef>	parameters;
		IntrinsicCallback			callback = nullptr;
		bool						variadic = false;
		bool						operateOnVectorElements = false;
	};

}	// namespace ve
