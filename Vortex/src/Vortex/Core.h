#pragma once

#ifdef VTX_WINDOWS_PLATFORM
			
#endif // VRT_WINDOWS_PLATFORM

#ifdef VTX_ENABLE_ASSERT
	#define VTX_ASSERT(x, ...) { if(!(x)) { VTX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define VTX_CORE_ASSERT(x, ...) { if(!(x)) { VTX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#endif // VRT_ENABLE_ASSERT

#define BIT(x) ( 1 << x )