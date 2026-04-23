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

#ifdef IN
#undef IN
#endif

#ifdef OUT
#undef OUT
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