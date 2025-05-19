#pragma once

#ifdef VTX_WINDOWS_PLATFORM
	#define VTX_DEBUGBREAK() __debugbreak()
#elif defined(VTX_UNIX_PLATFORM)|| defined(VTX_APPLE_PLATFORM)
	#include <signal.h>
	#define VTX_DEBUGBREAK() raise(SIGTRAP)
#else
	#define VTX_DEBUGBREAK() ((void)0)
#endif

#ifdef VTX_ENABLE_ASSERT
	#define VTX_ASSERT(x, ...) do { if(!(x)) { VTX_ERROR("Assertion Failed: {0}", __VA_ARGS__); VTX_DEBUGBREAK(); }} while(0)
	#define VTX_CORE_ASSERT(x, ...) do { if(!(x)) { VTX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); VTX_DEBUGBREAK(); }} while(0)
#else
	#define VTX_ASSERT(x, ...)
	#define VTX_CORE_ASSERT(x, ...)
#endif // VRT_ENABLE_ASSERT
#define VTX_STATIC_ASSERT(cond, msg) static_assert(cond, "Vortex StaticAssert Failed: " msg)

#define BIT(x) ( 1 << (x) )

#define VTX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)