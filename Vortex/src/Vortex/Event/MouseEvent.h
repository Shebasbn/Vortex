#pragma once

#include "Event.h"

namespace Vortex
{
	class MouseButton : public Event
	{
	public:
		uint32_t GetMouseButton() const { return m_MouseButton; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
	protected:
		MouseButton(uint32_t button)
			: m_MouseButton(button){}
		uint32_t m_MouseButton;
	};
}