#pragma once

#include "Text.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <format>
#include <fstream>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

#ifdef _WIN32
	#include "../OS/OS.h"
	#include <processthreadsapi.h>
	#include <shlobj.h>
#elif defined( __APPLE__ )
	#include <CoreFoundation/CoreFoundation.h>
	#include <IOKit/ps/IOPowerSources.h>
	#include <IOKit/ps/IOPSKeys.h>
	#include <IOKit/pwr_mgt/IOPMLib.h>
	#include <mach-o/dyld.h>
	#include <mach/host_info.h>
	#include <mach/mach.h>
	#include <mach/mach_host.h>
	#include <mach/mach_time.h>
	#include <mach/thread_act.h>
	#include <mach/thread_policy.h>
	#include <pthread.h>
	#include <pwd.h>
	#include <sys/sysctl.h>
	#include <sys/types.h>
	#include <unistd.h>
#else
	#include <limits.h>
	#include <pthread.h>
	#include <pwd.h>
	#include <sys/syscall.h>
	#include <sys/types.h>
	#include <sys/utsname.h>
	#include <time.h>
	#include <unistd.h>
#endif


namespace ve {

	/**
	 * Provides system-level utilities such as high-resolution timing.
	 **/
	class System {
	public :
		// == Functions.
		// ===============================
		// Timing & Performance
		// ===============================
		/**
		 * Gets the current high-resolution hardware tick count.
		 *
		 * \return			Returns the current performance counter value.
		 **/
		static inline uint64_t		getPerformanceCounter() {
#if defined( _WIN32 )
			LARGE_INTEGER li;
			::QueryPerformanceCounter(&li);
			return static_cast<uint64_t>(li.QuadPart);
#elif defined( __APPLE__ )
			return ::mach_absolute_time();
#else
			struct timespec ts;
			::clock_gettime(CLOCK_MONOTONIC, &ts);
			return static_cast<uint64_t>(ts.tv_sec) * 1000000000ULL + static_cast<uint64_t>(ts.tv_nsec);
#endif
		}

		/**
		 * Gets the number of ticks per second for the high-resolution counter.
		 *
		 * \return			Returns the performance counter frequency in Hz.
		 **/
		static inline uint64_t		getPerformanceFrequency() {
#if defined( _WIN32 )
			LARGE_INTEGER li;
			::QueryPerformanceFrequency(&li);
			return static_cast<uint64_t>(li.QuadPart);
#elif defined( __APPLE__ )
			mach_timebase_info_data_t timebase;
			::mach_timebase_info(&timebase);
			// mach_absolute_time returns ticks. 
			// 1 tick = (numer / denom) nanoseconds.
			// Frequency (ticks per second) = 1,000,000,000 * denom / numer
			return (1000000000ULL * static_cast<uint64_t>(timebase.denom)) / static_cast<uint64_t>(timebase.numer);
#else
			// clock_gettime with CLOCK_MONOTONIC returns nanosecond resolution.
			return 1000000000ULL;
#endif
		}

		/**
		 * Suspends the current thread for the specified number of milliseconds.
		 *
		 * \param milliseconds	The duration to sleep in milliseconds.
		 **/
		static inline void			sleep(uint32_t milliseconds) {
#if defined( _WIN32 )
			::Sleep(static_cast<DWORD>(milliseconds));
#else
			struct timespec ts;
			ts.tv_sec = milliseconds / 1000;
			ts.tv_nsec = (milliseconds % 1000) * 1000000;
			::nanosleep(&ts, nullptr);
#endif
		}

		/**
		 * Suspends the current thread for the specified number of microseconds.
		 * Note: Exact precision depends on the OS scheduler and hardware timer resolution.
		 *
		 * \param microseconds	The duration to sleep in microseconds.
		 **/
		static inline void			sleepMicroseconds(uint64_t microseconds) {
#if defined( _WIN32 )
			// Windows waitable timers use 100-nanosecond intervals.
			// Negative values indicate relative time.
			LARGE_INTEGER timerInterval;
			timerInterval.QuadPart = -static_cast<LONGLONG>(microseconds * 10ULL);

			// CREATE_WAITABLE_TIMER_HIGH_RESOLUTION is supported on Windows 10, version 1803 and newer.
#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 2
#endif

			HANDLE timer = ::CreateWaitableTimerExW(nullptr, nullptr, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
			if (timer == nullptr) {
				// Fallback for older Windows versions.
				timer = ::CreateWaitableTimerW(nullptr, TRUE, nullptr);
			}

			if (timer != nullptr) {
				::SetWaitableTimer(timer, &timerInterval, 0, nullptr, nullptr, FALSE);
				::WaitForSingleObject(timer, INFINITE);
				::CloseHandle(timer);
			}
			else {
				// Absolute fallback (loss of microsecond precision).
				::Sleep(static_cast<DWORD>(microseconds / 1000ULL));
			}
#else
			struct timespec ts;
			ts.tv_sec = static_cast<time_t>(microseconds / 1000000ULL);
			ts.tv_nsec = static_cast<long>((microseconds % 1000000ULL) * 1000ULL);
			::nanosleep(&ts, nullptr);
#endif
		}


		// =========================================================================
		// Filesystem & Paths
		// =========================================================================
		/**
		 * Helper function to safely retrieve the current user's home directory on POSIX systems.
		 * Must be called within a try/catch block.
		 *
		 * \return			Returns the UTF-8 path to the home directory.
		 **/
		static inline std::string	getPosixHomeDirectory() {
#if !defined( _WIN32 )
			const char* homeEnv = std::getenv("HOME");
			if (homeEnv != nullptr) {
				return std::string(homeEnv);
			}
			// Fallback if HOME is not set.
			struct passwd* pw = ::getpwuid(getuid());
			if (pw != nullptr && pw->pw_dir != nullptr) {
				return std::string(pw->pw_dir);
			}
#endif
			return std::string();
		}

		/**
		 * Retrieves the full, absolute path to the currently running executable.
		 * Must be called within a try/catch block.
		 *
		 * \return			Returns the UTF-8 path to the executable.
		 **/
		static inline std::string	getExecutablePath() {
#if defined( _WIN32 )
			std::wstring buffer;
			// 32768 (0x8000) is the maximum extended path length in Windows (\\?\ prefix).
			buffer.resize(0x8000);
			DWORD len = ::GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
			if (len > 0) {
				buffer.resize(len);
				return Text::wStringToUtf8(buffer);
			}
			return std::string();
#elif defined( __APPLE__ )
			char buffer[1024];
			uint32_t size = sizeof(buffer);
			if (_NSGetExecutablePath(buffer, &size) == 0) {
				return std::string(buffer);
			}

			std::string result;
			result.resize(size);
			if (_NSGetExecutablePath(result.data(), &size) == 0) {
				// Remove the null terminator that _NSGetExecutablePath includes in the size.
				if (!result.empty() && result.back() == '\0') {
					result.pop_back();
				}
				return result;
			}
			return std::string();
#else
			char buffer[PATH_MAX];
			ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer));
			if (len > 0 && len < PATH_MAX) {
				return std::string(buffer, static_cast<size_t>(len));
			}
			return std::string();
#endif
		}

		/**
		 * Retrieves the absolute directory containing the currently running executable.
		 * Must be called within a try/catch block.
		 *
		 * \return			Returns the UTF-8 path to the directory (without a trailing slash).
		 **/
		static inline std::string	getExecutableDirectory() {
			std::string exePath = getExecutablePath();
			size_t slashPos = exePath.find_last_of("/\\");
			if (slashPos != std::string::npos) {
				return exePath.substr(0, slashPos);
			}
			return exePath;
		}

		/**
		 * Retrieves the path to the current user's local application data folder.
		 * Windows: %LOCALAPPDATA% (e.g., C:\Users\Name\AppData\Local)
		 * macOS: ~/Library/Application Support
		 * Linux: ~/.local/share (XDG Base Directory standard)
		 * Must be called within a try/catch block.
		 *
		 * \return			Returns the UTF-8 path to the application data directory.
		 **/
		static inline std::string	getAppDataDirectory() {
#if defined( _WIN32 )
			PWSTR path = nullptr;
			std::string result;
			if (SUCCEEDED(::SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path))) {
				result = Text::wStringToUtf8(std::wstring(path));
				::CoTaskMemFree(path);
			}
			return result;
#elif defined( __APPLE__ )
			std::string home = getPosixHomeDirectory();
			if (!home.empty()) {
				return home + "/Library/Application Support";
			}
			return std::string();
#else
			const char* xdgData = std::getenv("XDG_DATA_HOME");
			if (xdgData != nullptr && xdgData[0] != '\0') {
				return std::string(xdgData);
			}
			std::string home = getPosixHomeDirectory();
			if (!home.empty()) {
				return home + "/.local/share";
			}
			return std::string();
#endif
		}

		/**
		 * Retrieves the path to the current user's standard documents folder.
		 * Must be called within a try/catch block.
		 *
		 * \return			Returns the UTF-8 path to the user's Documents directory.
		 **/
		static inline std::string	getUserDocumentsDirectory() {
#if defined( _WIN32 )
			PWSTR path = nullptr;
			std::string result;
			if (SUCCEEDED(::SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &path))) {
				result = Text::wStringToUtf8(std::wstring(path));
				::CoTaskMemFree(path);
			}
			return result;
#else
			// macOS and Linux largely share the standard ~/Documents paradigm.
			// On Linux, XDG_DOCUMENTS_DIR is technically correct, but manually parsing user-dirs.dirs 
			// is overkill for a lightweight system header. The fallback to ~/Documents is nearly universal.
			std::string home = getPosixHomeDirectory();
			if (!home.empty()) {
				return home + "/Documents";
			}
			return std::string();
#endif
		}


		// ===============================
		// System Information
		// ===============================
		/**
		 * Gets the number of logical CPU cores available.
		 *
		 * \return			Returns the logical core count, with a minimum guaranteed value of 1.
		 **/
		static inline uint32_t		getLogicalCoreCount() {
			uint32_t count = std::thread::hardware_concurrency();
			return count > 0 ? count : 1;
		}

		/**
		 * Gets the number of physical CPU cores available.
		 * Note: Falls back to logical core count if the physical query fails.
		 *
		 * \return			Returns the physical core count.
		 **/
		static inline uint32_t		getPhysicalCoreCount() {
#if defined( _WIN32 )
			DWORD len = 0;
			::GetLogicalProcessorInformation(nullptr, &len);
			if ( len == 0 ) { return getLogicalCoreCount(); }

			std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));
			if ( !::GetLogicalProcessorInformation(buffer.data(), &len) ) { return getLogicalCoreCount(); }

			uint32_t cores = 0;
			for ( const auto& info : buffer ) {
				if ( info.Relationship == RelationProcessorCore ) {
					++cores;
				}
			}
			return cores > 0 ? cores : getLogicalCoreCount();
#elif defined( __APPLE__ )
			uint32_t cores = 0;
			size_t len = sizeof(cores);
			::sysctlbyname("hw.physicalcpu", &cores, &len, nullptr, 0);
			return cores > 0 ? cores : getLogicalCoreCount();
#else
			// Linux: Parse /proc/cpuinfo and count unique core IDs per physical ID.
			// TODO: Implement a simplififed fallback.
			long cores = ::sysconf(_SC_NPROCESSORS_ONLN);
			return cores > 0 ? static_cast<uint32_t>(cores) : getLogicalCoreCount();
#endif
		}

		/**
		 * Gets the total system memory installed on the machine.
		 *
		 * \return			Returns the total memory in bytes.
		 **/
		static inline uint64_t		getTotalSystemMemory() {
#if defined( _WIN32 )
			MEMORYSTATUSEX status;
			status.dwLength = sizeof(status);
			::GlobalMemoryStatusEx(&status);
			return status.ullTotalPhys;
#elif defined( __APPLE__ )
			uint64_t mem = 0;
			size_t len = sizeof(mem);
			::sysctlbyname("hw.memsize", &mem, &len, nullptr, 0);
			return mem;
#else
			uint64_t pages = static_cast<uint64_t>(::sysconf(_SC_PHYS_PAGES));
			uint64_t pageSize = static_cast<uint64_t>(::sysconf(_SC_PAGE_SIZE));
			return pages * pageSize;
#endif
		}

		/**
		 * Gets the currently available system memory.
		 *
		 * \return			Returns the available memory in bytes.
		 **/
		static inline uint64_t		getAvailableSystemMemory() {
#if defined( _WIN32 )
			MEMORYSTATUSEX status;
			status.dwLength = sizeof(status);
			::GlobalMemoryStatusEx(&status);
			return status.ullAvailPhys;
#elif defined( __APPLE__ )
			mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
			vm_statistics64_data_t vmStats;
			if ( ::host_statistics64(::mach_host_self(), HOST_VM_INFO64, reinterpret_cast<host_info64_t*>(&vmStats), &count) == KERN_SUCCESS ) {
				return static_cast<uint64_t>(vmStats.free_count + vmStats.inactive_count) * static_cast<uint64_t>(::sysconf(_SC_PAGE_SIZE));
			}
			return 0;
#else
			uint64_t pages = static_cast<uint64_t>(::sysconf(_SC_AVPHYS_PAGES));
			uint64_t pageSize = static_cast<uint64_t>(::sysconf(_SC_PAGE_SIZE));
			return pages * pageSize;
#endif
		}

		/**
		 * Gets a string representing the operating system.
		 *
		 * \return			Returns the OS name (and release version on POSIX systems).
		 **/
		static inline std::string	getOsName() {
#if defined( _WIN32 )
			// Extracting the exact Windows version (e.g., 10 vs 11) at runtime is heavy 
			// and requires registry reads or RtlGetVersion. Compile-time literal is safest.
			return "Windows";
#elif defined( __APPLE__ )
			return "macOS";
#else
			struct utsname buffer;
			if ( ::uname(&buffer) == 0 ) {
				return std::string(buffer.sysname) + " " + buffer.release;
			}
			return "Linux";
#endif
		}

		/**
		 * Determines the byte order of the host system.
		 *
		 * \return			Returns true if the system is little-endian.
		 **/
		static inline bool			isLittleEndian() {
			// This runtime check should be optimized by all modern compilers 
			// into a compile-time constant `return true;` or `return false;`.
			const uint16_t number = 0x1;
			const char* ptr = reinterpret_cast<const char*>(&number);
			return (ptr[0] == 1);
		}


		// ===============================
		// Threading & Processes
		// ===============================
		/**
		 * Pins the current thread to specific CPU cores.
		 *
		 * \param coreMask	A bitmask representing the physical/logical cores the thread is allowed to run on.
		 **/
		static inline void			setThreadAffinity(uint64_t coreMask) {
#if defined( _WIN32 )
			::SetThreadAffinityMask(::GetCurrentThread(), static_cast<DWORD_PTR>(coreMask));
#elif defined( __APPLE__ )
			// macOS does not support strict core pinning. Use the thread affinity API as a best-effort grouping mechanism.
			thread_affinity_policy_data_t policy;
			policy.affinity_tag = static_cast<integer_t>(coreMask);
			::thread_policy_set(::pthread_mach_thread_np(pthread_self()), THREAD_AFFINITY_POLICY, 
							  reinterpret_cast<thread_policy_t>(&policy), THREAD_AFFINITY_POLICY_COUNT);
#else
			cpu_set_t cpuset;
			CPU_ZERO(&cpuset);
			for (int i = 0; i < 64; ++i) {
				if ((coreMask & (1ULL << i)) != 0) {
					CPU_SET(i, &cpuset);
				}
			}
			pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
#endif
		}

		/**
		 * Gets the OS-assigned ID of the running process.
		 *
		 * \return			Returns the current process ID.
		 **/
		static inline uint32_t		getCurrentProcessId() {
#if defined( _WIN32 )
			return static_cast<uint32_t>(::GetCurrentProcessId());
#else
			return static_cast<uint32_t>(getpid());
#endif
		}

		/**
		 * Gets the OS-assigned ID of the calling thread.
		 *
		 * \return			Returns the current thread ID.
		 **/
		static inline uint64_t		getCurrentThreadId() {
#if defined( _WIN32 )
			return static_cast<uint64_t>(::GetCurrentThreadId());
#elif defined( __APPLE__ )
			uint64_t tid;
			::pthread_threadid_np(nullptr, &tid);
			return tid;
#else
			return static_cast<uint64_t>(syscall(SYS_gettid));
#endif
		}


		// ===============================
		// Power & Display Management
		// ===============================
		/**
		 * Tells the OS whether it should prevent the display from sleeping or the system from entering standby.
		 * Useful during continuous tasks like emulation or video playback.
		 *
		 * \param prevent	Set to true to prevent sleep, false to restore normal sleep behavior.
		 **/
		static inline void			preventDisplaySleep(bool prevent) {
#if defined( _WIN32 )
			if (prevent) {
				::SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);
			}
			else {
				::SetThreadExecutionState(ES_CONTINUOUS);
			}
#elif defined( __APPLE__ )
			static IOPMAssertionID assertionId = 0;
			
			if (prevent) {
				if (assertionId == 0) {
					CFStringRef reasonForActivity = CFSTR("Application preventing sleep");
					IOPMAssertionCreateWithName(kIOPMAssertionTypeNoDisplaySleep, 
												kIOPMAssertionLevelOn, reasonForActivity, &assertionId);
				}
			}
			else {
				if (assertionId != 0) {
					IOPMAssertionRelease(assertionId);
					assertionId = 0;
				}
			}
#else
			// Linux display sleep prevention is heavily dependent on the display server (X11/Wayland)
			// and active desktop environment (GNOME, KDE, etc.). 
			// Without pulling in heavy DBUS/XCB libraries, using 'xset' via system() is the most robust terminal fallback.
			if (prevent) {
				int ret = std::system("xset s off -dpms 2>/dev/null");
				(void)ret; // Suppress unused result warning
			}
			else {
				int ret = std::system("xset s on +dpms 2>/dev/null");
				(void)ret;
			}
#endif
		}

		/**
		 * Retrieves the current battery level of the system.
		 *
		 * \return			Returns the battery percentage (0 to 100), or -1 if the system has no battery (desktop) or an error occurred.
		 **/
		static inline int32_t		getBatteryPercentage() {
#if defined( _WIN32 )
			SYSTEM_POWER_STATUS status;
			if (::GetSystemPowerStatus(&status)) {
				// 255 indicates that the status is unknown (often means no battery).
				if (status.BatteryLifePercent != 255) {
					return static_cast<int32_t>(status.BatteryLifePercent);
				}
			}
			return -1;
#elif defined( __APPLE__ )
			CFTypeRef blob = IOPSCopyPowerSourcesInfo();
			CFArrayRef sources = IOPSCopyPowerSourcesList(blob);
			int32_t percent = -1;
			
			if (CFArrayGetCount(sources) > 0) {
				CFDictionaryRef pSource = static_cast<CFDictionaryRef>(IOPSGetPowerSourceDescription(blob, CFArrayGetValueAtIndex(sources, 0)));
				if (pSource) {
					CFNumberRef capacityNum = static_cast<CFNumberRef>(CFDictionaryGetValue(pSource, CFSTR(kIOPSCurrentCapacityKey)));
					CFNumberRef maxCapacityNum = static_cast<CFNumberRef>(CFDictionaryGetValue(pSource, CFSTR(kIOPSMaxCapacityKey)));
					
					if (capacityNum && maxCapacityNum) {
						int cap = 0;
						int maxCap = 0;
						CFNumberGetValue(capacityNum, kCFNumberIntType, &cap);
						CFNumberGetValue(maxCapacityNum, kCFNumberIntType, &maxCap);
						
						if (maxCap > 0) {
							percent = static_cast<int32_t>((cap * 100) / maxCap);
						}
					}
				}
			}
			
			CFRelease(sources);
			CFRelease(blob);
			return percent;
#else
			// Linux exposes battery information generically via the sysfs filesystem.
			// BAT0 is the standard primary battery, falling back to BAT1 for dual-battery laptops.
			int32_t capacity = -1;
			std::ifstream file("/sys/class/power_supply/BAT0/capacity");
			if (file >> capacity) {
				return capacity;
			}
			
			std::ifstream file1("/sys/class/power_supply/BAT1/capacity");
			if (file1 >> capacity) {
				return capacity;
			}
			
			return -1;
#endif
		}
	protected :

	private :
	};

}	// namespace ve
