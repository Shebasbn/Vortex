#pragma once
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"
#include <spdlog/fmt/fmt.h>

#define VORTEX_FMT_EVENT_DERIVED(DerivedType)        \
static_assert(std::is_base_of<Vortex::Event, Vortex::DerivedType>::value, #DerivedType " must derive from Vortex::Event");\
template <>                                          \
struct fmt::formatter<Vortex::DerivedType>           \
    : fmt::formatter<Vortex::Event> {                \
    template <typename FormatContext>                \
    auto format(const Vortex::DerivedType& e, FormatContext& ctx) const { \
        return fmt::formatter<Vortex::Event>::format(e, ctx);             \
    }                                                                  \
};

template <>
struct fmt::formatter<Vortex::Event> {
    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin(); // No format specifiers
    }

    template <typename FormatContext>
    auto format(const Vortex::Event& e, FormatContext& ctx) const {
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
            e.GetTimestamp().time_since_epoch()).count();
        return format_to(ctx.out(), "[{} | ID: {} | Time: {}] {}",
            e.GetName(), e.GetID(), time, e.ToString());
    }
};

// Key Events
VORTEX_FMT_EVENT_DERIVED(KeyPressedEvent)
VORTEX_FMT_EVENT_DERIVED(KeyReleasedEvent)
VORTEX_FMT_EVENT_DERIVED(KeyTypedEvent)

// Mouse Events
VORTEX_FMT_EVENT_DERIVED(MouseMovedEvent)
VORTEX_FMT_EVENT_DERIVED(MouseScrolledEvent)
VORTEX_FMT_EVENT_DERIVED(MouseButtonPressedEvent)
VORTEX_FMT_EVENT_DERIVED(MouseButtonReleasedEvent)

// Application Events
VORTEX_FMT_EVENT_DERIVED(WindowResizeEvent)
VORTEX_FMT_EVENT_DERIVED(WindowCloseEvent)
VORTEX_FMT_EVENT_DERIVED(AppTickEvent)
VORTEX_FMT_EVENT_DERIVED(AppUpdateEvent)
VORTEX_FMT_EVENT_DERIVED(AppRenderEvent)

