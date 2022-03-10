#pragma once

#include"Event.h"


namespace Hazel
{
	class HAZEL_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button) : m_Button(button) {};
		int m_Button;
	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};


	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};


	class HAZEL_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX;}
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)
	private:
		float m_MouseX, m_MouseY;
	};


	class HAZEL_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) : m_OffsetX(x), m_OffsetY(y) {}

		inline float GetXOffset() const { return m_OffsetX; }
		inline float GetYOffset() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_OffsetX << "," << m_OffsetY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
			EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float m_OffsetX, m_OffsetY;
	};

}