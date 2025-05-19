#pragma once

#include "Event.h"
#include <sstream>

namespace Vortex
{
	class KeyEvent : public Event
	{
	public:
		uint32_t GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(uint32_t keyCode)
			: m_KeyCode(keyCode) {}
		uint32_t m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(uint32_t keyCode, uint32_t repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		uint32_t GetRepeatCount() const { return m_RepeatCount; }
		virtual std::string ToString() const override
		{ 
			std::stringstream ss;
			ss << "(KeyCode): " << m_KeyCode << " (" << m_RepeatCount << " times).";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		uint32_t m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(uint32_t keyCode)
			: KeyEvent(keyCode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "(KeyCode): " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(uint32_t keyCode)
			: KeyEvent(keyCode) {
		}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "(KeyCode): " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}