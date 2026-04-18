#pragma once

#include "../Strings/Strings.h"
#include "Result.h"

#include <vector>

namespace ve {

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
		Float,
		Double,
		Pointer
	};

	/**
	 * Metadata and type-enforcement for a single function parameter.
	 **/
	struct ParameterDef {
		DataType					type;
		const char*					name;
		StringId					description;
	};

	/**
	 * Callback signature for built-in intrinsic functions.
	 **/
	using IntrinsicCallback = Result (*)(const std::vector<Result>& args);

	/**
	 * Complete definition of a registered function, including documentation metadata.
	 **/
	struct FunctionDef {
		const char*					name;
		StringId					description;
		std::vector<ParameterDef>	parameters;
		IntrinsicCallback			callback;
	};

}	// namespace ve
