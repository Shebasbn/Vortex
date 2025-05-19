#include "Log.h"
#include "Vortex/Event/Event.h"
#include "Vortex/Event/KeyEvent.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Vortex
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("VORTEX");
        s_CoreLogger->set_level(spdlog::level::trace);
        VTX_CORE_DEBUG("Core logger initialized");

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
        VTX_DEBUG("Core logger initialized");

        
    }
}