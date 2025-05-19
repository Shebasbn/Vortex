#pragma once
#include "Event.h"
#include "KeyEvent.h"
#include <spdlog/fmt/fmt.h>


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

// Optional: format derived types explicitly if needed
template <>
struct fmt::formatter<Vortex::KeyPressedEvent> : fmt::formatter<Vortex::Event> {
    template <typename FormatContext>
    auto format(const Vortex::KeyPressedEvent& e, FormatContext& ctx) const {
        return fmt::formatter<Vortex::Event>::format(e, ctx);
    }
};