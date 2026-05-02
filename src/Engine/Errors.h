#pragma once

namespace ve {

	// == Enumerations.
	/**
	 * Standardized error codes.
	 **/
	enum class ErrorCode {
		Success,

		// == Internal Errors.
		Out_Of_Memory,
		Fail_To_Allocate_Node_For_Ast,

		// == Compilation Errors.
		Invalid_LValue,
		Unknown_Operator,
		Invalid_Function_Target,
		Unknown_Function,
		Invalid_Argument_Count,
		Syntax_Error,

		// == Runtime Errors.
		Unknown_Numeric_Type,
		Object_Initialization_Failed,
		Object_Deletion_Failed,
		String_Remove_Failed,
		String_Reverse_Failed,
	};

}	// namespace ve
