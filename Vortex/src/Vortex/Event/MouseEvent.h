#pragma once

#include "Event.h"

namespace Vortex
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float posX, float posY)
			:m_MousePosX(posX), m_MousePosY(posY) {}
		
		float GetXPos() const { return m_MousePosX; }
		float GetYPos() const { return m_MousePosY; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "(MouseMoved): (X: " << m_MousePosX << ", Y: " << m_MousePosX << ").";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_MousePosX, m_MousePosY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "(MouseScrolled): (X-Offset: "<< m_XOffset << ", Y-Offset: " << m_YOffset << ").";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		uint32_t GetMouseButton() const { return m_MouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(uint32_t button)
			: m_MouseButton(button){}
		uint32_t m_MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(uint32_t button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "(MouseButton): " << m_MouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(uint32_t button)
			: MouseButtonEvent(button) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "(MouseButton): " << m_MouseButton;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}