#pragma once
#include <spdlog/spdlog.h>
#include "Event/EventFormatter.h"

namespace Vortex
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#ifndef DEBUG_BUILD
// Core Log Macros
	#define VTX_CORE_DEBUG(...) 
	#define VTX_CORE_TRACE(...) 
	#define VTX_CORE_INFO(...)  
	#define VTX_CORE_WARN(...)  
	#define VTX_CORE_ERROR(...) 
	#define VTX_CORE_FATAL(...) 

	// Client Log Macros
	#define VTX_DEBUG(...) 
	#define VTX_TRACE(...) 
	#define VTX_INFO(...)  
	#define VTX_WARN(...)  
	#define VTX_ERROR(...) 
	#define VTX_FATAL(...) 
#else
	// Core Log Macros
	#define VTX_CORE_DEBUG(...) :: Vortex::Log::GetCoreLogger()->debug(__VA_ARGS__)
	#define VTX_CORE_TRACE(...) ::Vortex::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define VTX_CORE_INFO(...)  ::Vortex::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define VTX_CORE_WARN(...)  ::Vortex::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define VTX_CORE_ERROR(...) ::Vortex::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define VTX_CORE_FATAL(...) ::Vortex::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client Log Macros
	#define VTX_DEBUG(...) ::Vortex::Log::GetCoreLogger()->debug(__VA_ARGS__)
	#define VTX_TRACE(...) ::Vortex::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define VTX_INFO(...)  ::Vortex::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define VTX_WARN(...)  ::Vortex::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define VTX_ERROR(...) ::Vortex::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define VTX_FATAL(...) ::Vortex::Log::GetCoreLogger()->critical(__VA_ARGS__)
#endif // DEBUG_BUILD