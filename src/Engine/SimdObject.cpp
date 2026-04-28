#include "SimdObject.h"

namespace ve {

	// == Members.
	const SimdRegisterInfo SimdObject::simdRegisterProperties[] = {
		//name				componentType		componentCount	registerSize				alignment					instructionSet
		{ "__m64",			DataType::Int32,	2,				sizeof(simde__m64),			alignof(simde__m64),		InstructionSet::MMX },
		{ "__m128",			DataType::Float,	4,				sizeof(simde__m128),		alignof(simde__m128),		InstructionSet::SSE },
		{ "__m128d",		DataType::Double,	2,				sizeof(simde__m128d),		alignof(simde__m128d),		InstructionSet::SSE },
		{ "__m128i",		DataType::Int32,	4,				sizeof(simde__m128i),		alignof(simde__m128i),		InstructionSet::SSE },
		{ "__m256",			DataType::Float,	8,				sizeof(simde__m256),		alignof(simde__m256),		InstructionSet::AVX },
		{ "__m256d",		DataType::Double,	4,				sizeof(simde__m256d),		alignof(simde__m256d),		InstructionSet::AVX },
		{ "__m256i",		DataType::Int32,	8,				sizeof(simde__m256i),		alignof(simde__m256i),		InstructionSet::AVX },
		{ "__m512",			DataType::Float,	16,				sizeof(simde__m512),		alignof(simde__m512),		InstructionSet::AVX512 },
		{ "__m512d",		DataType::Double,	8,				sizeof(simde__m512d),		alignof(simde__m512d),		InstructionSet::AVX512 },
		{ "__m512i",		DataType::Int32,	16,				sizeof(simde__m512i),		alignof(simde__m512i),		InstructionSet::AVX512 },
		{ "v128_t",			DataType::Int32,	4,				sizeof(simde_v128_t),		alignof(simde_v128_t),		InstructionSet::WASM },
		{ "int8x8_t",		DataType::Int8,		8,				sizeof(simde_int8x8_t),		alignof(simde_int8x8_t),	InstructionSet::NEON },
		{ "int16x4_t",		DataType::Int16,	4,				sizeof(simde_int16x4_t),	alignof(simde_int16x4_t),	InstructionSet::NEON },
		{ "int32x2_t",		DataType::Int32,	2,				sizeof(simde_int32x2_t),	alignof(simde_int32x2_t),	InstructionSet::NEON },
		{ "int64x1_t",		DataType::Int64,	1,				sizeof(simde_int64x1_t),	alignof(simde_int64x1_t),	InstructionSet::NEON },
		{ "uint8x8_t",		DataType::UInt8,	8,				sizeof(simde_uint8x8_t),	alignof(simde_uint8x8_t),	InstructionSet::NEON },
		{ "uint16x4_t",		DataType::UInt16,	4,				sizeof(simde_uint16x4_t),	alignof(simde_uint16x4_t),	InstructionSet::NEON },
		{ "uint32x2_t",		DataType::UInt32,	2,				sizeof(simde_uint32x2_t),	alignof(simde_uint32x2_t),	InstructionSet::NEON },
		{ "uint64x1_t",		DataType::UInt64,	1,				sizeof(simde_uint64x1_t),	alignof(simde_uint64x1_t),	InstructionSet::NEON },
		{ "float32x2_t",	DataType::Float,	2,				sizeof(simde_float32x2_t),	alignof(simde_float32x2_t),	InstructionSet::NEON },
		{ "float64x1_t",	DataType::Double,	1,				sizeof(simde_float64x1_t),	alignof(simde_float64x1_t),	InstructionSet::NEON },
		{ "int8x16_t",		DataType::Int8,		16,				sizeof(simde_int8x16_t),	alignof(simde_int8x16_t),	InstructionSet::NEON },
		{ "int16x8_t",		DataType::Int16,	8,				sizeof(simde_int16x8_t),	alignof(simde_int16x8_t),	InstructionSet::NEON },
		{ "int32x4_t",		DataType::Int32,	4,				sizeof(simde_int32x4_t),	alignof(simde_int32x4_t),	InstructionSet::NEON },
		{ "int64x2_t",		DataType::Int64,	2,				sizeof(simde_int64x2_t),	alignof(simde_int64x2_t),	InstructionSet::NEON },
		{ "uint8x16_t",		DataType::UInt8,	16,				sizeof(simde_uint8x16_t),	alignof(simde_uint8x16_t),	InstructionSet::NEON },
		{ "uint16x8_t",		DataType::UInt16,	8,				sizeof(simde_uint16x8_t),	alignof(simde_uint16x8_t),	InstructionSet::NEON },
		{ "uint32x4_t",		DataType::UInt32,	4,				sizeof(simde_uint32x4_t),	alignof(simde_uint32x4_t),	InstructionSet::NEON },
		{ "uint64x2_t",		DataType::UInt64,	2,				sizeof(simde_uint64x2_t),	alignof(simde_uint64x2_t),	InstructionSet::NEON },
		{ "float32x4_t",	DataType::Float,	4,				sizeof(simde_float32x4_t),	alignof(simde_float32x4_t),	InstructionSet::NEON },
		{ "float64x2_t",	DataType::Double,	2,				sizeof(simde_float64x2_t),	alignof(simde_float64x2_t),	InstructionSet::NEON }
	};

	/**
	 * Serializes the object into a string representation.
	 *
	 * \param returnString	The output parameter where the string representation will be appended.
	 * \param depth			The current recursion depth (used for indenting or catching circular references).
	 * \param flags			Formatting flags dictating how the string should be generated.
	 * \return				Returns true if the object was successfully converted to a string.
	 **/
	bool SimdObject::toString(std::string& returnString, uint32_t depth, uint32_t flags) const {
		auto formatArray = [&returnString]<typename T>(const char* prefix, const T* vals, size_t count) {
			returnString += prefix;
			returnString += "[";
			for (size_t i = 0; i < count; ++i) {
				if constexpr (sizeof(T) == 1) {
					returnString += std::to_string(static_cast<int>(vals[i]));
				} else {
					returnString += std::to_string(vals[i]);
				}
				if (i < count - 1) {
					returnString += ", ";
				}
			}
			returnString += "]";
		};

		switch (regType) {
			case Simd_m64 : {
				int32_t vals[2];
				std::memcpy(vals, &reg.m64, sizeof(vals));
				formatArray("__m64", vals, 2);
				return true;
			}
			case Simd_m128 : {
				float vals[4];
				std::memcpy(vals, &reg.m128, sizeof(vals));
				formatArray("__m128", vals, 4);
				return true;
			}
			case Simd_m128d : {
				double vals[2];
				std::memcpy(vals, &reg.m128d, sizeof(vals));
				formatArray("__m128d", vals, 2);
				return true;
			}
			case Simd_m128i : {
				int32_t vals[4];
				std::memcpy(vals, &reg.m128i, sizeof(vals));
				formatArray("__m128i", vals, 4);
				return true;
			}
			case Simd_m256 : {
				float vals[8];
				std::memcpy(vals, &reg.m256, sizeof(vals));
				formatArray("__m256", vals, 8);
				return true;
			}
			case Simd_m256d : {
				double vals[4];
				std::memcpy(vals, &reg.m256d, sizeof(vals));
				formatArray("__m256d", vals, 4);
				return true;
			}
			case Simd_m256i : {
				int32_t vals[8];
				std::memcpy(vals, &reg.m256i, sizeof(vals));
				formatArray("__m256i", vals, 8);
				return true;
			}
			case Simd_m512 : {
				float vals[16];
				std::memcpy(vals, &reg.m512, sizeof(vals));
				formatArray("__m512", vals, 16);
				return true;
			}
			case Simd_m512d : {
				double vals[8];
				std::memcpy(vals, &reg.m512d, sizeof(vals));
				formatArray("__m512d", vals, 8);
				return true;
			}
			case Simd_m512i : {
				int32_t vals[16];
				std::memcpy(vals, &reg.m512i, sizeof(vals));
				formatArray("__m512i", vals, 16);
				return true;
			}
			case Simd_v128 : {
				int32_t vals[4];
				std::memcpy(vals, &reg.v128, sizeof(vals));
				formatArray("v128_t", vals, 4);
				return true;
			}
			case Simd_int8x8 : {
				int8_t vals[8];
				std::memcpy(vals, &reg.int8x8, sizeof(vals));
				formatArray("int8x8_t", vals, 8);
				return true;
			}
			case Simd_int16x4 : {
				int16_t vals[4];
				std::memcpy(vals, &reg.int16x4, sizeof(vals));
				formatArray("int16x4_t", vals, 4);
				return true;
			}
			case Simd_int32x2 : {
				int32_t vals[2];
				std::memcpy(vals, &reg.int32x2, sizeof(vals));
				formatArray("int32x2_t", vals, 2);
				return true;
			}
			case Simd_int64x1 : {
				int64_t vals[1];
				std::memcpy(vals, &reg.int64x1, sizeof(vals));
				formatArray("int64x1_t", vals, 1);
				return true;
			}
			case Simd_uint8x8 : {
				uint8_t vals[8];
				std::memcpy(vals, &reg.uint8x8, sizeof(vals));
				formatArray("uint8x8_t", vals, 8);
				return true;
			}
			case Simd_uint16x4 : {
				uint16_t vals[4];
				std::memcpy(vals, &reg.uint16x4, sizeof(vals));
				formatArray("uint16x4_t", vals, 4);
				return true;
			}
			case Simd_uint32x2 : {
				uint32_t vals[2];
				std::memcpy(vals, &reg.uint32x2, sizeof(vals));
				formatArray("uint32x2_t", vals, 2);
				return true;
			}
			case Simd_uint64x1 : {
				uint64_t vals[1];
				std::memcpy(vals, &reg.uint64x1, sizeof(vals));
				formatArray("uint64x1_t", vals, 1);
				return true;
			}
			case Simd_float32x2 : {
				float vals[2];
				std::memcpy(vals, &reg.float32x2, sizeof(vals));
				formatArray("float32x2_t", vals, 2);
				return true;
			}
			case Simd_float64x1 : {
				double vals[1];
				std::memcpy(vals, &reg.float64x1, sizeof(vals));
				formatArray("float64x1_t", vals, 1);
				return true;
			}
			case Simd_int8x16 : {
				int8_t vals[16];
				std::memcpy(vals, &reg.int8x16, sizeof(vals));
				formatArray("int8x16_t", vals, 16);
				return true;
			}
			case Simd_int16x8 : {
				int16_t vals[8];
				std::memcpy(vals, &reg.int16x8, sizeof(vals));
				formatArray("int16x8_t", vals, 8);
				return true;
			}
			case Simd_int32x4 : {
				int32_t vals[4];
				std::memcpy(vals, &reg.int32x4, sizeof(vals));
				formatArray("int32x4_t", vals, 4);
				return true;
			}
			case Simd_int64x2 : {
				int64_t vals[2];
				std::memcpy(vals, &reg.int64x2, sizeof(vals));
				formatArray("int64x2_t", vals, 2);
				return true;
			}
			case Simd_uint8x16 : {
				uint8_t vals[16];
				std::memcpy(vals, &reg.uint8x16, sizeof(vals));
				formatArray("uint8x16_t", vals, 16);
				return true;
			}
			case Simd_uint16x8 : {
				uint16_t vals[8];
				std::memcpy(vals, &reg.uint16x8, sizeof(vals));
				formatArray("uint16x8_t", vals, 8);
				return true;
			}
			case Simd_uint32x4 : {
				uint32_t vals[4];
				std::memcpy(vals, &reg.uint32x4, sizeof(vals));
				formatArray("uint32x4_t", vals, 4);
				return true;
			}
			case Simd_uint64x2 : {
				uint64_t vals[2];
				std::memcpy(vals, &reg.uint64x2, sizeof(vals));
				formatArray("uint64x2_t", vals, 2);
				return true;
			}
			case Simd_float32x4 : {
				float vals[4];
				std::memcpy(vals, &reg.float32x4, sizeof(vals));
				formatArray("float32x4_t", vals, 4);
				return true;
			}
			case Simd_float64x2 : {
				double vals[2];
				std::memcpy(vals, &reg.float64x2, sizeof(vals));
				formatArray("float64x2_t", vals, 2);
				return true;
			}
			default : {
				return false;
			}
		}
	}

	/**
	 * Converts the object to a fundamental numeric constant type if possible.
	 *
	 * \param targetType	The target numeric type to convert to.
	 * \return				Returns a Result containing the converted value, or an error state if invalid.
	 **/
	Result SimdObject::convertTo(NumericConstant targetType) const {
		return Result{};
	}

	/**
	 * Initializes the internal state of the object using a raw Result value.
	 *
	 * \param val			The Result value to initialize from.
	 * \return				Returns true if initialization was successful, false otherwise.
	 **/
	bool SimdObject::initializeFrom(const Result& val) {
		if (val.type != NumericConstant::Object || !val.value.objectVal) {
			return false;
		}

		if (!(val.value.objectVal->type() & BuiltInType_Simd)) {
			return false;
		}

		SimdObject* src = static_cast<SimdObject*>(val.value.objectVal);
		const SimdRegisterInfo& destInfo = simdRegisterProperties[regType];
		const SimdRegisterInfo& srcInfo = simdRegisterProperties[src->regType];

		if (destInfo.componentCount != srcInfo.componentCount) {
			return false;
		}

		for (size_t i = 0; i < destInfo.componentCount; ++i) {
			Result comp = src->arrayAccess(i);
			Result casted = context->castArgument(comp, destInfo.componentType);
			
			if (casted.type == NumericConstant::Invalid) {
				return false;
			}
			
			this->arrayAssign(i, casted);
		}

		return true;
	}

	/**
	 * Accesses an element within the object using a single index.
	 *
	 * \param idx			The zero-based index of the element to access.
	 * \return				Returns a Result containing the accessed element.
	 **/
	Result SimdObject::arrayAccess(int64_t idx) {
		size_t linIdx = arrayIndexToLinearIndex(idx, arrayLength());
		if (linIdx == InvalidIndex) {
			return Result{};
		}

		const SimdRegisterInfo& info = simdRegisterProperties[regType];
		const uint8_t* base = reinterpret_cast<const uint8_t*>(&reg);

		switch (info.componentType) {
			case DataType::Int8 : {
				return Result::make(static_cast<int64_t>(reinterpret_cast<const int8_t*>(base)[linIdx]));
			}
			case DataType::UInt8 : {
				return Result::make(static_cast<uint64_t>(reinterpret_cast<const uint8_t*>(base)[linIdx]));
			}
			case DataType::Int16 : {
				return Result::make(static_cast<int64_t>(reinterpret_cast<const int16_t*>(base)[linIdx]));
			}
			case DataType::UInt16 : {
				return Result::make(static_cast<uint64_t>(reinterpret_cast<const uint16_t*>(base)[linIdx]));
			}
			case DataType::Int32 : {
				return Result::make(static_cast<int64_t>(reinterpret_cast<const int32_t*>(base)[linIdx]));
			}
			case DataType::UInt32 : {
				return Result::make(static_cast<uint64_t>(reinterpret_cast<const uint32_t*>(base)[linIdx]));
			}
			case DataType::Int64 : {
				return Result::make(reinterpret_cast<const int64_t*>(base)[linIdx]);
			}
			case DataType::UInt64 : {
				return Result::make(reinterpret_cast<const uint64_t*>(base)[linIdx]);
			}
			case DataType::Float16 : {}
			case DataType::BFloat16 : {}
			case DataType::Float : {
				return Result::make(static_cast<double>(reinterpret_cast<const float*>(base)[linIdx]));
			}
			case DataType::Double : {
				return Result::make(reinterpret_cast<const double*>(base)[linIdx]);
			}
			default : {
				return Result{};
			}
		}
	}

	/**
	 * Accesses an element or sub-range within the object using complex indexing or slicing.
	 *
	 * \param idx0			The primary index or slice start.
	 * \param idx1			The secondary index or slice end.
	 * \param mask			A bitmask defining the specific access behavior.
	 * \return				Returns a Result containing the accessed element or range.
	 **/
	Result SimdObject::arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) {
		return Result{};
	}

	/**
	 * Assigns a value directly to a specified index within the SIMD register.
	 *
	 * \param index			The zero-based or negative offset index.
	 * \param rhs			The result to insert or overwrite with.
	 * \return				Returns the assigned value on success, or Invalid on failure.
	 **/
	Result SimdObject::arrayAssign(int64_t index, const Result& rhs) {
		size_t linIdx = arrayIndexToLinearIndex(index, arrayLength());
		if (linIdx == InvalidIndex) { return Result{}; }

		const SimdRegisterInfo& info = simdRegisterProperties[regType];
		uint8_t* base = reinterpret_cast<uint8_t*>(&reg);

		Result casted = context->castArgument(rhs, info.componentType);
		if (casted.type == NumericConstant::Invalid) { return Result{}; }

		switch (info.componentType) {
			case DataType::Int8 : {
				reinterpret_cast<int8_t*>(base)[linIdx] = static_cast<int8_t>(casted.value.intVal);
				break;
			}
			case DataType::UInt8 : {
				reinterpret_cast<uint8_t*>(base)[linIdx] = static_cast<uint8_t>(casted.value.uintVal);
				break;
			}
			case DataType::Int16 : {
				reinterpret_cast<int16_t*>(base)[linIdx] = static_cast<int16_t>(casted.value.intVal);
				break;
			}
			case DataType::UInt16 : {
				reinterpret_cast<uint16_t*>(base)[linIdx] = static_cast<uint16_t>(casted.value.uintVal);
				break;
			}
			case DataType::Int32 : {
				reinterpret_cast<int32_t*>(base)[linIdx] = static_cast<int32_t>(casted.value.intVal);
				break;
			}
			case DataType::UInt32 : {
				reinterpret_cast<uint32_t*>(base)[linIdx] = static_cast<uint32_t>(casted.value.uintVal);
				break;
			}
			case DataType::Int64 : {
				reinterpret_cast<int64_t*>(base)[linIdx] = casted.value.intVal;
				break;
			}
			case DataType::UInt64 : {
				reinterpret_cast<uint64_t*>(base)[linIdx] = casted.value.uintVal;
				break;
			}
			case DataType::Float16 : {}
			case DataType::BFloat16 : {}
			case DataType::Float : {
				reinterpret_cast<float*>(base)[linIdx] = static_cast<float>(casted.value.doubleVal);
				break;
			}
			case DataType::Double : {
				reinterpret_cast<double*>(base)[linIdx] = casted.value.doubleVal;
				break;
			}
			default : {
				return Result{};
			}
		}

		return casted;
	}

	/**
	 * Retrieves the total number of elements contained in the object.
	 *
	 * \return				Returns the element count as a size_t.
	 **/
	size_t SimdObject::arrayLength() const {
		return simdRegisterProperties[regType].componentCount;
	}

	// == Operators.
#define VE_SIMD_CMP_CASE(REG_ENUM, REG_MEM, FUNC)																					\
	case REG_ENUM : {																												\
		auto res = FUNC(reg.REG_MEM, rhsSimd->reg.REG_MEM);																			\
		std::memcpy(&outObj->reg.REG_MEM, &res, sizeof(outObj->reg.REG_MEM));														\
		break;																														\
	}

#define VE_SIMD_CMP_OP(OP_NAME,																										\
		FN_M64, FN_M128, FN_M128D, FN_M128I,																						\
		FN_M256, FN_M256D, FN_M256I,																								\
		FN_M512, FN_M512D, FN_M512I,																								\
		FN_V128,																													\
		FN_I8X8, FN_I16X4, FN_I32X2, FN_I64X1,																						\
		FN_U8X8, FN_U16X4, FN_U32X2, FN_U64X1,																						\
		FN_F32X2, FN_F64X1,																											\
		FN_I8X16, FN_I16X8, FN_I32X4, FN_I64X2,																						\
		FN_U8X16, FN_U16X8, FN_U32X4, FN_U64X2,																						\
		FN_F32X4, FN_F64X2)																											\
	Result SimdObject::OP_NAME(const Result& rhs) const {																			\
		if (rhs.type != NumericConstant::Object || !rhs.value.objectVal || !(rhs.value.objectVal->type() & BuiltInType_Simd)) {		\
			return Result{};																										\
		}																															\
		const SimdObject* rhsSimd = static_cast<const SimdObject*>(rhs.value.objectVal);											\
		if (regType != rhsSimd->regType) {																							\
			return Result{};																										\
		}																															\
		SimdObject* outObj = context->allocateObject<SimdObject>();																	\
		if (!outObj) {																												\
			return Result{};																										\
		}																															\
		outObj->regType = regType;																									\
		switch (regType) {																											\
			VE_SIMD_CMP_CASE(Simd_m64, m64, FN_M64)																					\
			VE_SIMD_CMP_CASE(Simd_m128, m128, FN_M128)																				\
			VE_SIMD_CMP_CASE(Simd_m128d, m128d, FN_M128D)																			\
			VE_SIMD_CMP_CASE(Simd_m128i, m128i, FN_M128I)																			\
			VE_SIMD_CMP_CASE(Simd_m256, m256, FN_M256)																				\
			VE_SIMD_CMP_CASE(Simd_m256d, m256d, FN_M256D)																			\
			VE_SIMD_CMP_CASE(Simd_m256i, m256i, FN_M256I)																			\
			VE_SIMD_CMP_CASE(Simd_m512, m512, FN_M512)																				\
			VE_SIMD_CMP_CASE(Simd_m512d, m512d, FN_M512D)																			\
			VE_SIMD_CMP_CASE(Simd_m512i, m512i, FN_M512I)																			\
			VE_SIMD_CMP_CASE(Simd_v128, v128, FN_V128)																				\
			VE_SIMD_CMP_CASE(Simd_int8x8, int8x8, FN_I8X8)																			\
			VE_SIMD_CMP_CASE(Simd_int16x4, int16x4, FN_I16X4)																		\
			VE_SIMD_CMP_CASE(Simd_int32x2, int32x2, FN_I32X2)																		\
			VE_SIMD_CMP_CASE(Simd_int64x1, int64x1, FN_I64X1)																		\
			VE_SIMD_CMP_CASE(Simd_uint8x8, uint8x8, FN_U8X8)																		\
			VE_SIMD_CMP_CASE(Simd_uint16x4, uint16x4, FN_U16X4)																		\
			VE_SIMD_CMP_CASE(Simd_uint32x2, uint32x2, FN_U32X2)																		\
			VE_SIMD_CMP_CASE(Simd_uint64x1, uint64x1, FN_U64X1)																		\
			VE_SIMD_CMP_CASE(Simd_float32x2, float32x2, FN_F32X2)																	\
			VE_SIMD_CMP_CASE(Simd_float64x1, float64x1, FN_F64X1)																	\
			VE_SIMD_CMP_CASE(Simd_int8x16, int8x16, FN_I8X16)																		\
			VE_SIMD_CMP_CASE(Simd_int16x8, int16x8, FN_I16X8)																		\
			VE_SIMD_CMP_CASE(Simd_int32x4, int32x4, FN_I32X4)																		\
			VE_SIMD_CMP_CASE(Simd_int64x2, int64x2, FN_I64X2)																		\
			VE_SIMD_CMP_CASE(Simd_uint8x16, uint8x16, FN_U8X16)																		\
			VE_SIMD_CMP_CASE(Simd_uint16x8, uint16x8, FN_U16X8)																		\
			VE_SIMD_CMP_CASE(Simd_uint32x4, uint32x4, FN_U32X4)																		\
			VE_SIMD_CMP_CASE(Simd_uint64x2, uint64x2, FN_U64X2)																		\
			VE_SIMD_CMP_CASE(Simd_float32x4, float32x4, FN_F32X4)																	\
			VE_SIMD_CMP_CASE(Simd_float64x2, float64x2, FN_F64X2)																	\
			default : {																												\
				context->deallocateObject(outObj);																					\
				return Result{};																									\
			}																														\
		}																															\
		return outObj->createResult();																								\
	}

	VE_SIMD_CMP_OP(operator==,
		veUnsupported, simde_mm_cmpeq_ps, simde_mm_cmpeq_pd, simde_mm_cmpeq_epi32,
		ve_mm256_cmpeq_ps, ve_mm256_cmpeq_pd, simde_mm256_cmpeq_epi32,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		simde_vceq_s8, simde_vceq_s16, simde_vceq_s32, veUnsupported,
		simde_vceq_u8, simde_vceq_u16, simde_vceq_u32, veUnsupported,
		simde_vceq_f32, veUnsupported,
		simde_vceqq_s8, simde_vceqq_s16, simde_vceqq_s32, veUnsupported,
		simde_vceqq_u8, simde_vceqq_u16, simde_vceqq_u32, veUnsupported,
		simde_vceqq_f32, veUnsupported
	)

	VE_SIMD_CMP_OP(operator!=,
		veUnsupported, simde_mm_cmpneq_ps, simde_mm_cmpneq_pd, veUnsupported,
		ve_mm256_cmpneq_ps, ve_mm256_cmpneq_pd, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

	VE_SIMD_CMP_OP(operator<,
		veUnsupported, simde_mm_cmplt_ps, simde_mm_cmplt_pd, simde_mm_cmplt_epi32,
		ve_mm256_cmplt_ps, ve_mm256_cmplt_pd, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		simde_vclt_s8, simde_vclt_s16, simde_vclt_s32, veUnsupported,
		simde_vclt_u8, simde_vclt_u16, simde_vclt_u32, veUnsupported,
		simde_vclt_f32, veUnsupported,
		simde_vcltq_s8, simde_vcltq_s16, simde_vcltq_s32, veUnsupported,
		simde_vcltq_u8, simde_vcltq_u16, simde_vcltq_u32, veUnsupported,
		simde_vcltq_f32, veUnsupported
	)

	VE_SIMD_CMP_OP(operator>,
		veUnsupported, simde_mm_cmpgt_ps, simde_mm_cmpgt_pd, simde_mm_cmpgt_epi32,
		ve_mm256_cmpgt_ps, ve_mm256_cmpgt_pd, simde_mm256_cmpgt_epi32,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		simde_vcgt_s8, simde_vcgt_s16, simde_vcgt_s32, veUnsupported,
		simde_vcgt_u8, simde_vcgt_u16, simde_vcgt_u32, veUnsupported,
		simde_vcgt_f32, veUnsupported,
		simde_vcgtq_s8, simde_vcgtq_s16, simde_vcgtq_s32, veUnsupported,
		simde_vcgtq_u8, simde_vcgtq_u16, simde_vcgtq_u32, veUnsupported,
		simde_vcgtq_f32, veUnsupported
	)

	VE_SIMD_CMP_OP(operator<=,
		veUnsupported, simde_mm_cmple_ps, simde_mm_cmple_pd, veUnsupported,
		ve_mm256_cmple_ps, ve_mm256_cmple_pd, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		simde_vcle_s8, simde_vcle_s16, simde_vcle_s32, veUnsupported,
		simde_vcle_u8, simde_vcle_u16, simde_vcle_u32, veUnsupported,
		simde_vcle_f32, veUnsupported,
		simde_vcleq_s8, simde_vcleq_s16, simde_vcleq_s32, veUnsupported,
		simde_vcleq_u8, simde_vcleq_u16, simde_vcleq_u32, veUnsupported,
		simde_vcleq_f32, veUnsupported
	)

	VE_SIMD_CMP_OP(operator>=,
		veUnsupported, simde_mm_cmpge_ps, simde_mm_cmpge_pd, veUnsupported,
		ve_mm256_cmpge_ps, ve_mm256_cmpge_pd, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		simde_vcge_s8, simde_vcge_s16, simde_vcge_s32, veUnsupported,
		simde_vcge_u8, simde_vcge_u16, simde_vcge_u32, veUnsupported,
		simde_vcge_f32, veUnsupported,
		simde_vcgeq_s8, simde_vcgeq_s16, simde_vcgeq_s32, veUnsupported,
		simde_vcgeq_u8, simde_vcgeq_u16, simde_vcgeq_u32, veUnsupported,
		simde_vcgeq_f32, veUnsupported
	)

#undef VE_SIMD_CMP_OP
#undef VE_SIMD_CMP_CASE


#define VE_SIMD_BINARY_CASE(REG_ENUM, REG_MEM, FUNC)																				\
	case REG_ENUM : {																												\
		outObj->reg.REG_MEM = FUNC(reg.REG_MEM, rhsSimd->reg.REG_MEM);																\
		break;																														\
	}

#define VE_SIMD_BINARY_OP(OP_NAME,																									\
		FN_M64, FN_M128, FN_M128D, FN_M128I,																						\
		FN_M256, FN_M256D, FN_M256I,																								\
		FN_M512, FN_M512D, FN_M512I,																								\
		FN_V128,																													\
		FN_I8X8, FN_I16X4, FN_I32X2, FN_I64X1,																						\
		FN_U8X8, FN_U16X4, FN_U32X2, FN_U64X1,																						\
		FN_F32X2, FN_F64X1,																											\
		FN_I8X16, FN_I16X8, FN_I32X4, FN_I64X2,																						\
		FN_U8X16, FN_U16X8, FN_U32X4, FN_U64X2,																						\
		FN_F32X4, FN_F64X2)																											\
	Result SimdObject::OP_NAME(const Result& rhs) const {																			\
		if (rhs.type != NumericConstant::Object || !rhs.value.objectVal || !(rhs.value.objectVal->type() & BuiltInType_Simd)) {		\
			return Result{};																										\
		}																															\
		const SimdObject* rhsSimd = static_cast<const SimdObject*>(rhs.value.objectVal);											\
		if (regType != rhsSimd->regType) {																							\
			return Result{};																										\
		}																															\
		SimdObject* outObj = context->allocateObject<SimdObject>();																	\
		if (!outObj) {																												\
			return Result{};																										\
		}																															\
		outObj->regType = regType;																									\
		switch (regType) {																											\
			VE_SIMD_BINARY_CASE(Simd_m64, m64, FN_M64)																				\
			VE_SIMD_BINARY_CASE(Simd_m128, m128, FN_M128)																			\
			VE_SIMD_BINARY_CASE(Simd_m128d, m128d, FN_M128D)																		\
			VE_SIMD_BINARY_CASE(Simd_m128i, m128i, FN_M128I)																		\
			VE_SIMD_BINARY_CASE(Simd_m256, m256, FN_M256)																			\
			VE_SIMD_BINARY_CASE(Simd_m256d, m256d, FN_M256D)																		\
			VE_SIMD_BINARY_CASE(Simd_m256i, m256i, FN_M256I)																		\
			VE_SIMD_BINARY_CASE(Simd_m512, m512, FN_M512)																			\
			VE_SIMD_BINARY_CASE(Simd_m512d, m512d, FN_M512D)																		\
			VE_SIMD_BINARY_CASE(Simd_m512i, m512i, FN_M512I)																		\
			VE_SIMD_BINARY_CASE(Simd_v128, v128, FN_V128)																			\
			VE_SIMD_BINARY_CASE(Simd_int8x8, int8x8, FN_I8X8)																		\
			VE_SIMD_BINARY_CASE(Simd_int16x4, int16x4, FN_I16X4)																	\
			VE_SIMD_BINARY_CASE(Simd_int32x2, int32x2, FN_I32X2)																	\
			VE_SIMD_BINARY_CASE(Simd_int64x1, int64x1, FN_I64X1)																	\
			VE_SIMD_BINARY_CASE(Simd_uint8x8, uint8x8, FN_U8X8)																		\
			VE_SIMD_BINARY_CASE(Simd_uint16x4, uint16x4, FN_U16X4)																	\
			VE_SIMD_BINARY_CASE(Simd_uint32x2, uint32x2, FN_U32X2)																	\
			VE_SIMD_BINARY_CASE(Simd_uint64x1, uint64x1, FN_U64X1)																	\
			VE_SIMD_BINARY_CASE(Simd_float32x2, float32x2, FN_F32X2)																\
			VE_SIMD_BINARY_CASE(Simd_float64x1, float64x1, FN_F64X1)																\
			VE_SIMD_BINARY_CASE(Simd_int8x16, int8x16, FN_I8X16)																	\
			VE_SIMD_BINARY_CASE(Simd_int16x8, int16x8, FN_I16X8)																	\
			VE_SIMD_BINARY_CASE(Simd_int32x4, int32x4, FN_I32X4)																	\
			VE_SIMD_BINARY_CASE(Simd_int64x2, int64x2, FN_I64X2)																	\
			VE_SIMD_BINARY_CASE(Simd_uint8x16, uint8x16, FN_U8X16)																	\
			VE_SIMD_BINARY_CASE(Simd_uint16x8, uint16x8, FN_U16X8)																	\
			VE_SIMD_BINARY_CASE(Simd_uint32x4, uint32x4, FN_U32X4)																	\
			VE_SIMD_BINARY_CASE(Simd_uint64x2, uint64x2, FN_U64X2)																	\
			VE_SIMD_BINARY_CASE(Simd_float32x4, float32x4, FN_F32X4)																\
			VE_SIMD_BINARY_CASE(Simd_float64x2, float64x2, FN_F64X2)																\
			default : {																												\
				context->deallocateObject(outObj);																					\
				return Result{};																									\
			}																														\
		}																															\
		return outObj->createResult();																								\
	}

	VE_SIMD_BINARY_OP(operator+,
		simde_mm_add_pi32, simde_mm_add_ps, simde_mm_add_pd, simde_mm_add_epi32,
		simde_mm256_add_ps, simde_mm256_add_pd, simde_mm256_add_epi32,
		simde_mm512_add_ps, simde_mm512_add_pd, simde_mm512_add_epi32,
		simde_wasm_i32x4_add,
		simde_vadd_s8, simde_vadd_s16, simde_vadd_s32, simde_vadd_s64,
		simde_vadd_u8, simde_vadd_u16, simde_vadd_u32, simde_vadd_u64,
		simde_vadd_f32, veUnsupported,
		simde_vaddq_s8, simde_vaddq_s16, simde_vaddq_s32, simde_vaddq_s64,
		simde_vaddq_u8, simde_vaddq_u16, simde_vaddq_u32, simde_vaddq_u64,
		simde_vaddq_f32, simde_vaddq_f64
	)

	VE_SIMD_BINARY_OP(operator-,
		simde_mm_sub_pi32, simde_mm_sub_ps, simde_mm_sub_pd, simde_mm_sub_epi32,
		simde_mm256_sub_ps, simde_mm256_sub_pd, simde_mm256_sub_epi32,
		simde_mm512_sub_ps, simde_mm512_sub_pd, simde_mm512_sub_epi32,
		simde_wasm_i32x4_sub,
		simde_vsub_s8, simde_vsub_s16, simde_vsub_s32, simde_vsub_s64,
		simde_vsub_u8, simde_vsub_u16, simde_vsub_u32, simde_vsub_u64,
		simde_vsub_f32, veUnsupported,
		simde_vsubq_s8, simde_vsubq_s16, simde_vsubq_s32, simde_vsubq_s64,
		simde_vsubq_u8, simde_vsubq_u16, simde_vsubq_u32, simde_vsubq_u64,
		simde_vsubq_f32, simde_vsubq_f64
	)

	VE_SIMD_BINARY_OP(operator*,
		veUnsupported, simde_mm_mul_ps, simde_mm_mul_pd, simde_mm_mullo_epi32,
		simde_mm256_mul_ps, simde_mm256_mul_pd, simde_mm256_mullo_epi32,
		simde_mm512_mul_ps, simde_mm512_mul_pd, simde_mm512_mullo_epi32,
		simde_wasm_i32x4_mul,
		simde_vmul_s8, simde_vmul_s16, simde_vmul_s32, veUnsupported,
		simde_vmul_u8, simde_vmul_u16, simde_vmul_u32, veUnsupported,
		simde_vmul_f32, veUnsupported,
		simde_vmulq_s8, simde_vmulq_s16, simde_vmulq_s32, veUnsupported,
		simde_vmulq_u8, simde_vmulq_u16, simde_vmulq_u32, veUnsupported,
		simde_vmulq_f32, simde_vmulq_f64
	)

	VE_SIMD_BINARY_OP(operator/,
		veUnsupported, simde_mm_div_ps, simde_mm_div_pd, veUnsupported,
		simde_mm256_div_ps, simde_mm256_div_pd, veUnsupported,
		simde_mm512_div_ps, simde_mm512_div_pd, veUnsupported,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

	VE_SIMD_BINARY_OP(operator%,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

	VE_SIMD_BINARY_OP(operator&,
		simde_mm_and_si64, simde_mm_and_ps, simde_mm_and_pd, simde_mm_and_si128,
		simde_mm256_and_ps, simde_mm256_and_pd, simde_mm256_and_si256,
		simde_mm512_and_ps, simde_mm512_and_pd, simde_mm512_and_si512,
		simde_wasm_v128_and,
		simde_vand_s8, simde_vand_s16, simde_vand_s32, simde_vand_s64,
		simde_vand_u8, simde_vand_u16, simde_vand_u32, simde_vand_u64,
		veUnsupported, veUnsupported,
		simde_vandq_s8, simde_vandq_s16, simde_vandq_s32, simde_vandq_s64,
		simde_vandq_u8, simde_vandq_u16, simde_vandq_u32, simde_vandq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_BINARY_OP(operator|,
		simde_mm_or_si64, simde_mm_or_ps, simde_mm_or_pd, simde_mm_or_si128,
		simde_mm256_or_ps, simde_mm256_or_pd, simde_mm256_or_si256,
		simde_mm512_or_ps, simde_mm512_or_pd, simde_mm512_or_si512,
		simde_wasm_v128_or,
		simde_vorr_s8, simde_vorr_s16, simde_vorr_s32, simde_vorr_s64,
		simde_vorr_u8, simde_vorr_u16, simde_vorr_u32, simde_vorr_u64,
		veUnsupported, veUnsupported,
		simde_vorrq_s8, simde_vorrq_s16, simde_vorrq_s32, simde_vorrq_s64,
		simde_vorrq_u8, simde_vorrq_u16, simde_vorrq_u32, simde_vorrq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_BINARY_OP(operator^,
		simde_mm_xor_si64, simde_mm_xor_ps, simde_mm_xor_pd, simde_mm_xor_si128,
		simde_mm256_xor_ps, simde_mm256_xor_pd, simde_mm256_xor_si256,
		simde_mm512_xor_ps, simde_mm512_xor_pd, simde_mm512_xor_si512,
		simde_wasm_v128_xor,
		simde_veor_s8, simde_veor_s16, simde_veor_s32, simde_veor_s64,
		simde_veor_u8, simde_veor_u16, simde_veor_u32, simde_veor_u64,
		veUnsupported, veUnsupported,
		simde_veorq_s8, simde_veorq_s16, simde_veorq_s32, simde_veorq_s64,
		simde_veorq_u8, simde_veorq_u16, simde_veorq_u32, simde_veorq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_BINARY_OP(operator<<,
		veUnsupported, veUnsupported, veUnsupported, simde_mm_sllv_epi32,
		veUnsupported, veUnsupported, simde_mm256_sllv_epi32,
		veUnsupported, veUnsupported, simde_mm512_sllv_epi32,
		veUnsupported,
		simde_vshl_s8, simde_vshl_s16, simde_vshl_s32, simde_vshl_s64,
		ve_vshl_u8, ve_vshl_u16, ve_vshl_u32, ve_vshl_u64,
		veUnsupported, veUnsupported,
		simde_vshlq_s8, simde_vshlq_s16, simde_vshlq_s32, simde_vshlq_s64,
		ve_vshlq_u8, ve_vshlq_u16, ve_vshlq_u32, ve_vshlq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_BINARY_OP(operator>>,
		veUnsupported, veUnsupported, veUnsupported, simde_mm_srlv_epi32,
		veUnsupported, veUnsupported, simde_mm256_srlv_epi32,
		veUnsupported, veUnsupported, simde_mm512_srlv_epi32,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

#undef VE_SIMD_BINARY_OP
#undef VE_SIMD_BINARY_CASE


#define VE_SIMD_COMPOUND_ASSIGN_CASE(REG_ENUM, REG_MEM, FUNC)																		\
		case REG_ENUM : {																											\
			reg.REG_MEM = FUNC(reg.REG_MEM, rhsSimd->reg.REG_MEM);																	\
			break;																													\
		}

#define VE_SIMD_COMPOUND_ASSIGN_OP(OP_NAME,																							\
		FN_M64, FN_M128, FN_M128D, FN_M128I,																						\
		FN_M256, FN_M256D, FN_M256I,																								\
		FN_M512, FN_M512D, FN_M512I,																								\
		FN_V128,																													\
		FN_I8X8, FN_I16X4, FN_I32X2, FN_I64X1,																						\
		FN_U8X8, FN_U16X4, FN_U32X2, FN_U64X1,																						\
		FN_F32X2, FN_F64X1,																											\
		FN_I8X16, FN_I16X8, FN_I32X4, FN_I64X2,																						\
		FN_U8X16, FN_U16X8, FN_U32X4, FN_U64X2,																						\
		FN_F32X4, FN_F64X2)																											\
	Result SimdObject::OP_NAME(const Result& rhs) {																					\
		if (rhs.type != NumericConstant::Object || !rhs.value.objectVal || !(rhs.value.objectVal->type() & BuiltInType_Simd)) {		\
			return Result{};																										\
		}																															\
		const SimdObject* rhsSimd = static_cast<const SimdObject*>(rhs.value.objectVal);											\
		if (regType != rhsSimd->regType) { return Result{}; }																		\
		switch (regType) {																											\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m64, m64, FN_M64)																		\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m128, m128, FN_M128)																	\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m128d, m128d, FN_M128D)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m128i, m128i, FN_M128I)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m256, m256, FN_M256)																	\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m256d, m256d, FN_M256D)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m256i, m256i, FN_M256I)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m512, m512, FN_M512)																	\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m512d, m512d, FN_M512D)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_m512i, m512i, FN_M512I)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_v128, v128, FN_V128)																	\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int8x8, int8x8, FN_I8X8)																\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int16x4, int16x4, FN_I16X4)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int32x2, int32x2, FN_I32X2)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int64x1, int64x1, FN_I64X1)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint8x8, uint8x8, FN_U8X8)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint16x4, uint16x4, FN_U16X4)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint32x2, uint32x2, FN_U32X2)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint64x1, uint64x1, FN_U64X1)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_float32x2, float32x2, FN_F32X2)														\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_float64x1, float64x1, FN_F64X1)														\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int8x16, int8x16, FN_I8X16)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int16x8, int16x8, FN_I16X8)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int32x4, int32x4, FN_I32X4)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_int64x2, int64x2, FN_I64X2)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint8x16, uint8x16, FN_U8X16)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint16x8, uint16x8, FN_U16X8)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint32x4, uint32x4, FN_U32X4)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_uint64x2, uint64x2, FN_U64X2)															\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_float32x4, float32x4, FN_F32X4)														\
			VE_SIMD_COMPOUND_ASSIGN_CASE(Simd_float64x2, float64x2, FN_F64X2)														\
			default : {																												\
				return Result{};																									\
			}																														\
		}																															\
		return this->createResult();																								\
	}

	VE_SIMD_COMPOUND_ASSIGN_OP(operator+=,
		simde_mm_add_pi32, simde_mm_add_ps, simde_mm_add_pd, simde_mm_add_epi32,
		simde_mm256_add_ps, simde_mm256_add_pd, simde_mm256_add_epi32,
		simde_mm512_add_ps, simde_mm512_add_pd, simde_mm512_add_epi32,
		simde_wasm_i32x4_add,
		simde_vadd_s8, simde_vadd_s16, simde_vadd_s32, simde_vadd_s64,
		simde_vadd_u8, simde_vadd_u16, simde_vadd_u32, simde_vadd_u64,
		simde_vadd_f32, veUnsupported,
		simde_vaddq_s8, simde_vaddq_s16, simde_vaddq_s32, simde_vaddq_s64,
		simde_vaddq_u8, simde_vaddq_u16, simde_vaddq_u32, simde_vaddq_u64,
		simde_vaddq_f32, simde_vaddq_f64
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator-=,
		simde_mm_sub_pi32, simde_mm_sub_ps, simde_mm_sub_pd, simde_mm_sub_epi32,
		simde_mm256_sub_ps, simde_mm256_sub_pd, simde_mm256_sub_epi32,
		simde_mm512_sub_ps, simde_mm512_sub_pd, simde_mm512_sub_epi32,
		simde_wasm_i32x4_sub,
		simde_vsub_s8, simde_vsub_s16, simde_vsub_s32, simde_vsub_s64,
		simde_vsub_u8, simde_vsub_u16, simde_vsub_u32, simde_vsub_u64,
		simde_vsub_f32, veUnsupported,
		simde_vsubq_s8, simde_vsubq_s16, simde_vsubq_s32, simde_vsubq_s64,
		simde_vsubq_u8, simde_vsubq_u16, simde_vsubq_u32, simde_vsubq_u64,
		simde_vsubq_f32, simde_vsubq_f64
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator*=,
		veUnsupported, simde_mm_mul_ps, simde_mm_mul_pd, simde_mm_mullo_epi32,
		simde_mm256_mul_ps, simde_mm256_mul_pd, simde_mm256_mullo_epi32,
		simde_mm512_mul_ps, simde_mm512_mul_pd, simde_mm512_mullo_epi32,
		simde_wasm_i32x4_mul,
		simde_vmul_s8, simde_vmul_s16, simde_vmul_s32, veUnsupported,
		simde_vmul_u8, simde_vmul_u16, simde_vmul_u32, veUnsupported,
		simde_vmul_f32, veUnsupported,
		simde_vmulq_s8, simde_vmulq_s16, simde_vmulq_s32, veUnsupported,
		simde_vmulq_u8, simde_vmulq_u16, simde_vmulq_u32, veUnsupported,
		simde_vmulq_f32, simde_vmulq_f64
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator/=,
		veUnsupported, simde_mm_div_ps, simde_mm_div_pd, veUnsupported,
		simde_mm256_div_ps, simde_mm256_div_pd, veUnsupported,
		simde_mm512_div_ps, simde_mm512_div_pd, veUnsupported,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator%=,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator&=,
		simde_mm_and_si64, simde_mm_and_ps, simde_mm_and_pd, simde_mm_and_si128,
		simde_mm256_and_ps, simde_mm256_and_pd, simde_mm256_and_si256,
		simde_mm512_and_ps, simde_mm512_and_pd, simde_mm512_and_si512,
		simde_wasm_v128_and,
		simde_vand_s8, simde_vand_s16, simde_vand_s32, simde_vand_s64,
		simde_vand_u8, simde_vand_u16, simde_vand_u32, simde_vand_u64,
		veUnsupported, veUnsupported,
		simde_vandq_s8, simde_vandq_s16, simde_vandq_s32, simde_vandq_s64,
		simde_vandq_u8, simde_vandq_u16, simde_vandq_u32, simde_vandq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator|=,
		simde_mm_or_si64, simde_mm_or_ps, simde_mm_or_pd, simde_mm_or_si128,
		simde_mm256_or_ps, simde_mm256_or_pd, simde_mm256_or_si256,
		simde_mm512_or_ps, simde_mm512_or_pd, simde_mm512_or_si512,
		simde_wasm_v128_or,
		simde_vorr_s8, simde_vorr_s16, simde_vorr_s32, simde_vorr_s64,
		simde_vorr_u8, simde_vorr_u16, simde_vorr_u32, simde_vorr_u64,
		veUnsupported, veUnsupported,
		simde_vorrq_s8, simde_vorrq_s16, simde_vorrq_s32, simde_vorrq_s64,
		simde_vorrq_u8, simde_vorrq_u16, simde_vorrq_u32, simde_vorrq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator^=,
		simde_mm_xor_si64, simde_mm_xor_ps, simde_mm_xor_pd, simde_mm_xor_si128,
		simde_mm256_xor_ps, simde_mm256_xor_pd, simde_mm256_xor_si256,
		simde_mm512_xor_ps, simde_mm512_xor_pd, simde_mm512_xor_si512,
		simde_wasm_v128_xor,
		simde_veor_s8, simde_veor_s16, simde_veor_s32, simde_veor_s64,
		simde_veor_u8, simde_veor_u16, simde_veor_u32, simde_veor_u64,
		veUnsupported, veUnsupported,
		simde_veorq_s8, simde_veorq_s16, simde_veorq_s32, simde_veorq_s64,
		simde_veorq_u8, simde_veorq_u16, simde_veorq_u32, simde_veorq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator<<=,
		veUnsupported, veUnsupported, veUnsupported, simde_mm_sllv_epi32,
		veUnsupported, veUnsupported, simde_mm256_sllv_epi32,
		veUnsupported, veUnsupported, simde_mm512_sllv_epi32,
		veUnsupported,
		simde_vshl_s8, simde_vshl_s16, simde_vshl_s32, simde_vshl_s64,
		ve_vshl_u8, ve_vshl_u16, ve_vshl_u32, ve_vshl_u64,
		veUnsupported, veUnsupported,
		simde_vshlq_s8, simde_vshlq_s16, simde_vshlq_s32, simde_vshlq_s64,
		ve_vshlq_u8, ve_vshlq_u16, ve_vshlq_u32, ve_vshlq_u64,
		veUnsupported, veUnsupported
	)

	VE_SIMD_COMPOUND_ASSIGN_OP(operator>>=,
		veUnsupported, veUnsupported, veUnsupported, simde_mm_srlv_epi32,
		veUnsupported, veUnsupported, simde_mm256_srlv_epi32,
		veUnsupported, veUnsupported, simde_mm512_srlv_epi32,
		veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported, veUnsupported, veUnsupported,
		veUnsupported, veUnsupported
	)

}	// namespace ve
