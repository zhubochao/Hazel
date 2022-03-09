#pragma once

#include"Event.h"

#include<sstream>

namespace Hazel
{
	class HAZEL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int w, unsigned int h) : m_Width(w), m_Height(h) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << "," << m_Height;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication )
			EVENT_CLASS_TYPE(WindowResize)
	private:
		unsigned m_Width, m_Height;
	};


	class HAZEL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent: ";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowClose)

	};


	class HAZEL_API WindowFocusEvent : public Event
	{
		WindowFocusEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent: ";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowFocus)
	};

	class HAZEL_API WindowLostFocusEvent : public Event
	{
		WindowLostFocusEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent: ";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(WindowLostFocus)
	};



	class HAZEL_API AppRenderEvent : public Event
	{
		AppRenderEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppRender)
	};

	class HAZEL_API AppTickEvent : public Event
	{
		AppTickEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppTick)
	};

	class HAZEL_API AppUpdateEvent : public Event
	{
		AppUpdateEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		EVENT_CLASS_TYPE(AppUpdate)
	};

}