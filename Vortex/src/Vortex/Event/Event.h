#pragma once

#include "Vortex/Core.h"

namespace Vortex
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	#define EVENT_CLASS_TYPE(type)\
		static EventType GetStaticType() { return EventType::type; }\
		virtual EventType GetEventType() const override { return GetStaticType(); }\
		virtual const char* GetName() const override { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
		friend class EventDispatcher;
	public:
		Event() : m_TimeStamp(std::chrono::steady_clock::now()) {}
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(const EventCategory category) const { return GetCategoryFlags() & category; }
		bool IsHandled() const { return m_Handled; }
		void SetHandled(bool handled = true) { m_Handled = handled; }
		uint64_t GetID() const { return m_EventID; }
		const std::chrono::steady_clock::time_point& GetTimestamp() const { return m_TimeStamp; }
	private:
		static inline std::atomic<uint64_t> s_EventCounter = 0;
		uint64_t m_EventID = ++s_EventCounter;
		std::chrono::steady_clock::time_point m_TimeStamp;
		bool m_Handled = false;
	};
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) 
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				T& casted = static_cast<T&>(m_Event);
				m_Event.SetHandled(func(casted));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	inline std::ostream& operator<<(std::ostream& os, const Vortex::Event& e) {
		return os << e.ToString();
	}
}

#include <spdlog/fmt/ostr.h>

//namespace fmt {
//	template <>
//	struct formatter<Vortex::Event> : formatter<std::string>
//	{
//		// Inherit parse() from formatter<std::string>
//		template <typename FormatContext>
//		auto format(const Vortex::Event& e, FormatContext& ctx)
//		{
//			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(
//				e.GetTimestamp().time_since_epoch()
//			).count();
//
//			return fmt::format_to(ctx.out(), "[{} | ID: {} | Time: {}] {}",
//				e.GetName(), e.GetID(), time, e.ToString());
//		}
//	};
//}