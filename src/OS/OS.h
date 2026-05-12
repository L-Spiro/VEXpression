#pragma once

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>

#ifdef ERROR
#undef ERROR
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#elif defined(__APPLE__)

//#include <iconv.h>
#include <cerrno>

#elif defined(__linux__) || defined(__unix__) || defined(_POSIX_VERSION)

//#include <iconv.h>
#include <cerrno>

#endif

#if defined(_MSC_VER)
	#include <intrin.h> // Required for cross-platform MSVC intrinsics (x64/ARM64)
#endif

#if defined(_MSC_VER)
	#define veFastcall										__fastcall
	#define veCdecl											__cdecl
	#define veExpect(cond, val)								(cond)

	// MSVC Prefetching: Handle ARM64 (Windows on ARM) vs x86/x64.
	#if defined(_M_ARM64) || defined(_M_ARM)
		#define vePrefetchLine(addr)						__prefetch(reinterpret_cast<const void*>(addr))
		#define vePrefetchLineWrite(addr)					__prefetchw(reinterpret_cast<const void*>(addr))
	#else
		#define vePrefetchLine(addr)						_mm_prefetch(reinterpret_cast<const char*>(addr), _MM_HINT_T0)
		#define vePrefetchLineWrite(addr)					_m_prefetchw(reinterpret_cast<volatile const void*>(addr))
	#endif

	#define veAlign(n)										__declspec(align(n))
	#define veFallthrough									[[fallthrough]]
	#define veLikely(x)										(x) [[likely]]
	#define veUnlikely(x)									(x) [[unlikely]]

#elif defined(__GNUC__) || defined(__clang__)
	#define veFastcall

	// cdecl and fastcall are x86 specific. ARM (macOS/iOS/Linux) ignores these.
	#if defined(__i386__) || defined(__x86_64__) || defined(__amd64__)
		#define veCdecl										__attribute__((cdecl))
	#else
		#define veCdecl
	#endif

	#define veExpect(cond, val)								__builtin_expect(!!(cond), (val))
	#define vePrefetchLine(addr)							__builtin_prefetch(reinterpret_cast<const void*>(addr), 0, 3)
	#define vePrefetchLineWrite(addr)						__builtin_prefetch(reinterpret_cast<const void*>(addr), 1, 3)

	// GNU Compiler Collection (GCC) or Clang (macOS, iOS, Linux).
	#define veAlign(n)										__attribute__((aligned(n)))
	
	// Handle fallthrough for modern Clang/GCC.
	#if defined(__has_cpp_attribute) && __has_cpp_attribute(fallthrough)
		#define veFallthrough								[[fallthrough]]
	#else
		#define veFallthrough								__attribute__((fallthrough))
	#endif

	#define veLikely(x)										(__builtin_expect(!!(x), 1))
	#define veUnlikely(x)									(__builtin_expect(!!(x), 0))	
#else
	#error "Unsupported compiler"
#endif	// #if defined(_MSC_VER)
