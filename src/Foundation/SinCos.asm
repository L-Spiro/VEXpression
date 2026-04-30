.code

PUBLIC sinCos
; void sinCos(double radians, double* outSin, double* outCos);

angleOnStack$ = 8

sinCos PROC

	movsd QWORD PTR angleOnStack$[rsp], xmm0	; Argument angle is in xmm0, move it to the stack.
	fld QWORD PTR angleOnStack$[rsp]			; Push angle onto the FPU stack where we can do FLOPs.
	fsincos
	fstp QWORD PTR [r8]							; Store/pop cosine output argument.
	fstp QWORD PTR [rdx]						; Store/pop sine output argument.
	ret 0

sinCos ENDP

PUBLIC sinCosF
; void sinCosF(float angle, float* outSin, float* outCos);

stackAngle$ = 4

sinCosF PROC

	movss DWORD PTR stackAngle$[rsp], xmm0		; Argument angle is in xmm0, move it to the stack.
	fld DWORD PTR stackAngle$[rsp]				; Push angle onto the FPU stack where we can do FLOPs.
	fsincos
	fstp DWORD PTR [r8]							; Store/pop cosine output argument.
	fstp DWORD PTR [rdx]						; Store/pop sine output argument.
	ret 0

sinCosF ENDP

END
