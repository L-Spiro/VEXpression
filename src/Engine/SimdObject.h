#pragma once

#include "../Engine/ExecutionContext.h"
#include "../Engine/Result.h"
#include "../Engine/SimdIncludes.h"
#include "Object.h"

#include <string>

namespace ve {

	// == Enumerations.
	/**
	 * Identifies the instruction set architecture associated with a SIMD register type.
	 **/
	enum class InstructionSet : uint8_t {
		MMX,
		SSE,
		AVX,
		AVX512,
		WASM,
		NEON
	};

	/**
	 * Enumeration of all SIMD register types supported by the scripting engine.
	 **/
	enum SimdRegisterType : uint32_t {
		Simd_m64,
		Simd_m128,
		Simd_m128d,
		Simd_m128i,
		Simd_m256,
		Simd_m256d,
		Simd_m256i,
		Simd_m512,
		Simd_m512d,
		Simd_m512i,
		Simd_v128,
		Simd_int8x8,
		Simd_int16x4,
		Simd_int32x2,
		Simd_int64x1,
		Simd_uint8x8,
		Simd_uint16x4,
		Simd_uint32x2,
		Simd_uint64x1,
		Simd_float32x2,
		Simd_float64x1,
		Simd_int8x16,
		Simd_int16x8,
		Simd_int32x4,
		Simd_int64x2,
		Simd_uint8x16,
		Simd_uint16x8,
		Simd_uint32x4,
		Simd_uint64x2,
		Simd_float32x4,
		Simd_float64x2
	};

	/**
	 * Union encapsulating the underlying SIMDe register types.
	 **/
	union SimdRegister {
		simde__m64							m64;
		simde__m128							m128;
		simde__m128d						m128d;
		simde__m128i						m128i;
		simde__m256							m256;
		simde__m256d						m256d;
		simde__m256i						m256i;
		simde__m512							m512;
		simde__m512d						m512d;
		simde__m512i						m512i;
		simde_v128_t						v128;
		simde_int8x8_t						int8x8;
		simde_int16x4_t						int16x4;
		simde_int32x2_t						int32x2;
		simde_int64x1_t						int64x1;
		simde_uint8x8_t						uint8x8;
		simde_uint16x4_t					uint16x4;
		simde_uint32x2_t					uint32x2;
		simde_uint64x1_t					uint64x1;
		simde_float32x2_t					float32x2;
		simde_float64x1_t					float64x1;
		simde_int8x16_t						int8x16;
		simde_int16x8_t						int16x8;
		simde_int32x4_t						int32x4;
		simde_int64x2_t						int64x2;
		simde_uint8x16_t					uint8x16;
		simde_uint16x8_t					uint16x8;
		simde_uint32x4_t					uint32x4;
		simde_uint64x2_t					uint64x2;
		simde_float32x4_t					float32x4;
		simde_float64x2_t					float64x2;
	};

	/**
	 * Contains detailed hardware and structural properties of a SIMD register.
	 **/
	struct SimdRegisterInfo {
		/**
		 * The string representation or identifier of the SIMD register (e.g., "__m128").
		 **/
		const char*							name;
		
		/**
		 * The data type of individual components or lanes in the register.
		 **/
		DataType							componentType;
		
		/**
		 * The total number of components or lanes in the register.
		 **/
		size_t								componentCount;
		
		/**
		 * The total size of the register in bytes.
		 **/
		size_t								registerSize;
		
		/**
		 * The memory alignment requirement for the register in bytes.
		 **/
		size_t								alignment;
		
		/**
		 * The SIMD instruction set architecture this register is primarily associated with.
		 **/
		InstructionSet						instructionSet;
	};

	/**
	 * Represents a dynamically typed SIMD register object in the script environment.
	 **/
	class SimdObject : public Object {
	public :
		SimdObject(ExecutionContext* ctx) : Object(ctx), regType(Simd_m128) {}
		virtual ~SimdObject() = default;


		// == Functions.
		/**
		 * Gets the runtime type identifier of this object.
		 *
		 * \return			Returns the object type identifier.
		 **/
		virtual uint32_t					type() const override {
			return Object::type() | BuiltInType_Simd;
		}

		/**
		 * Serializes the object into a string representation.
		 *
		 * \param returnString	The output parameter where the string representation will be appended.
		 * \param depth			The current recursion depth (used for indenting or catching circular references).
		 * \param flags			Formatting flags dictating how the string should be generated.
		 * \return				Returns true if the object was successfully converted to a string.
		 **/
		virtual bool						toString(std::string& returnString, uint32_t depth, uint32_t flags) const override;

		/**
		 * Converts the object to a fundamental numeric constant type if possible.
		 *
		 * \param targetType	The target numeric type to convert to.
		 * \return				Returns a Result containing the converted value, or an error state if invalid.
		 **/
		virtual Result						convertTo(NumericConstant targetType) const override;

		/**
		 * Initializes the internal state of the object using a raw Result value.
		 *
		 * \param val			The Result value to initialize from.
		 * \return				Returns true if initialization was successful, false otherwise.
		 **/
		virtual bool						initializeFrom(const Result& val) override;

		/**
		 * Accesses an element within the object using a single index.
		 *
		 * \param idx			The zero-based index of the element to access.
		 * \return				Returns a Result containing the accessed element.
		 **/
		virtual Result						arrayAccess(int64_t idx) override;

		/**
		 * Accesses an element or sub-range within the object using complex indexing or slicing.
		 *
		 * \param idx0			The primary index or slice start.
		 * \param idx1			The secondary index or slice end.
		 * \param mask			A bitmask defining the specific access behavior.
		 * \return				Returns a Result containing the accessed element or range.
		 **/
		virtual Result						arrayAccessEx(int64_t idx0, int64_t idx1, uint32_t mask) override;

		/**
		 * Assigns a value directly to a specified index within the SIMD register.
		 *
		 * \param index			The zero-based or negative offset index.
		 * \param rhs			The result to insert or overwrite with.
		 * \return				Returns the assigned value on success, or Invalid on failure.
		 **/
		virtual Result						arrayAssign(int64_t index, const Result& rhs) override;

		/**
		 * Retrieves the total number of elements contained in the object.
		 *
		 * \return				Returns the element count as a size_t.
		 **/
		virtual size_t						arrayLength() const override;

		/**
		 * Evaluates equality between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if equal, 0 if not.
		 **/
		virtual Result						operator==(const Result& rhs) const override;

		/**
		 * Evaluates inequality between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if not equal, 0 if equal.
		 **/
		virtual Result						operator!=(const Result& rhs) const override;

		/**
		 * Evaluates strictly-less-than comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less, 0 otherwise.
		 **/
		virtual Result						operator<(const Result& rhs) const override;

		/**
		 * Evaluates strictly-greater-than comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater, 0 otherwise.
		 **/
		virtual Result						operator>(const Result& rhs) const override;

		/**
		 * Evaluates less-than-or-equal comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if less or equal, 0 otherwise.
		 **/
		virtual Result						operator<=(const Result& rhs) const override;

		/**
		 * Evaluates greater-than-or-equal comparison between this object and a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing 1 if greater or equal, 0 otherwise.
		 **/
		virtual Result						operator>=(const Result& rhs) const override;

		/**
		 * Evaluates the addition operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed sum.
		 **/
		virtual Result						operator+(const Result& rhs) const override;

		/**
		 * Evaluates the subtraction operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed difference.
		 **/
		virtual Result						operator-(const Result& rhs) const override;

		/**
		 * Evaluates the multiplication operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed product.
		 **/
		virtual Result						operator*(const Result& rhs) const override;

		/**
		 * Evaluates the division operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed quotient.
		 **/
		virtual Result						operator/(const Result& rhs) const override;

		/**
		 * Evaluates the modulo operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed remainder.
		 **/
		virtual Result						operator%(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise left-shift operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns a Result containing the shifted value.
		 **/
		virtual Result						operator<<(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise right-shift operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand indicating the shift amount.
		 * \return				Returns a Result containing the shifted value.
		 **/
		virtual Result						operator>>(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise AND operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise AND.
		 **/
		virtual Result						operator&(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise OR operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise OR.
		 **/
		virtual Result						operator|(const Result& rhs) const override;

		/**
		 * Evaluates the bitwise XOR operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the computed bitwise XOR.
		 **/
		virtual Result						operator^(const Result& rhs) const override;

		/**
		 * Evaluates the compound addition assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator+=(const Result& rhs) override;

		/**
		 * Evaluates the compound subtraction assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator-=(const Result& rhs) override;

		/**
		 * Evaluates the compound multiplication assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator*=(const Result& rhs) override;

		/**
		 * Evaluates the compound division assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator/=(const Result& rhs) override;

		/**
		 * Evaluates the compound modulo assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator%=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise AND assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator&=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise OR assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator|=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise XOR assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator^=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise shift left assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator<<=(const Result& rhs) override;

		/**
		 * Evaluates the compound bitwise shift right assignment operation against a right-hand operand.
		 *
		 * \param rhs			The right-hand side operand.
		 * \return				Returns a Result containing the modified Object.
		 **/
		virtual Result						operator>>=(const Result& rhs) override;


		// == Functions.
		/**
		 * A placeholder function to bypass compilation errors on architectures 
		 * that lack native hardware support for a specific register size/operation.
		 **/
		template <typename T>
		static inline T						veUnsupported(T a, T b) { return a; }

		// NEON shift intrinsics for unsigned types expect signed integers for the shift amount.
		// We wrap them here to explicitly bitcast the unsigned vectors to signed vectors.
		static inline simde_uint8x8_t		ve_vshl_u8(simde_uint8x8_t a, simde_uint8x8_t b) {
			simde_int8x8_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshl_u8(a, sb);
		}
		static inline simde_uint16x4_t		ve_vshl_u16(simde_uint16x4_t a, simde_uint16x4_t b) {
			simde_int16x4_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshl_u16(a, sb);
		}
		static inline simde_uint32x2_t		ve_vshl_u32(simde_uint32x2_t a, simde_uint32x2_t b) {
			simde_int32x2_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshl_u32(a, sb);
		}
		static inline simde_uint64x1_t		ve_vshl_u64(simde_uint64x1_t a, simde_uint64x1_t b) {
			simde_int64x1_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshl_u64(a, sb);
		}
		static inline simde_uint8x16_t		ve_vshlq_u8(simde_uint8x16_t a, simde_uint8x16_t b) {
			simde_int8x16_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshlq_u8(a, sb);
		}
		static inline simde_uint16x8_t		ve_vshlq_u16(simde_uint16x8_t a, simde_uint16x8_t b) {
			simde_int16x8_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshlq_u16(a, sb);
		}
		static inline simde_uint32x4_t		ve_vshlq_u32(simde_uint32x4_t a, simde_uint32x4_t b) {
			simde_int32x4_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshlq_u32(a, sb);
		}
		static inline simde_uint64x2_t		ve_vshlq_u64(simde_uint64x2_t a, simde_uint64x2_t b) {
			simde_int64x2_t sb; std::memcpy(&sb, &b, sizeof(sb)); return simde_vshlq_u64(a, sb);
		}

		// AVX unified comparison wrappers. AVX uses a single intrinsic with an immediate 
		// predicate rather than distinct functions for each comparison type.
		static inline simde__m256			ve_mm256_cmpeq_ps(simde__m256 a, simde__m256 b)     { return simde_mm256_cmp_ps(a, b, SIMDE_CMP_EQ_OQ); }
		static inline simde__m256d			ve_mm256_cmpeq_pd(simde__m256d a, simde__m256d b)   { return simde_mm256_cmp_pd(a, b, SIMDE_CMP_EQ_OQ); }

		static inline simde__m256			ve_mm256_cmpneq_ps(simde__m256 a, simde__m256 b)    { return simde_mm256_cmp_ps(a, b, SIMDE_CMP_NEQ_OQ); }
		static inline simde__m256d			ve_mm256_cmpneq_pd(simde__m256d a, simde__m256d b)  { return simde_mm256_cmp_pd(a, b, SIMDE_CMP_NEQ_OQ); }

		static inline simde__m256			ve_mm256_cmplt_ps(simde__m256 a, simde__m256 b)     { return simde_mm256_cmp_ps(a, b, SIMDE_CMP_LT_OQ); }
		static inline simde__m256d			ve_mm256_cmplt_pd(simde__m256d a, simde__m256d b)   { return simde_mm256_cmp_pd(a, b, SIMDE_CMP_LT_OQ); }

		static inline simde__m256			ve_mm256_cmple_ps(simde__m256 a, simde__m256 b)     { return simde_mm256_cmp_ps(a, b, SIMDE_CMP_LE_OQ); }
		static inline simde__m256d			ve_mm256_cmple_pd(simde__m256d a, simde__m256d b)   { return simde_mm256_cmp_pd(a, b, SIMDE_CMP_LE_OQ); }

		static inline simde__m256			ve_mm256_cmpgt_ps(simde__m256 a, simde__m256 b)     { return simde_mm256_cmp_ps(a, b, SIMDE_CMP_GT_OQ); }
		static inline simde__m256d			ve_mm256_cmpgt_pd(simde__m256d a, simde__m256d b)   { return simde_mm256_cmp_pd(a, b, SIMDE_CMP_GT_OQ); }

		static inline simde__m256			ve_mm256_cmpge_ps(simde__m256 a, simde__m256 b)     { return simde_mm256_cmp_ps(a, b, SIMDE_CMP_GE_OQ); }
		static inline simde__m256d			ve_mm256_cmpge_pd(simde__m256d a, simde__m256d b)   { return simde_mm256_cmp_pd(a, b, SIMDE_CMP_GE_OQ); }

	public :
		SimdRegisterType					regType;
		SimdRegister						reg;
		static const SimdRegisterInfo		simdRegisterProperties[];
	};

}	// namespace ve
