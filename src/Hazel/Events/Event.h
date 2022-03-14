#pragma once

#include "Hazel/Core.h"

namespace Hazel
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
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

	#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
									virtual EventType GetEventType() const override{ return GetStaticType(); }\
									virtual const char* GetName() const override {  return #type;};

	#define EVENT_CLASS_CATEGORY(category) virtual int GetCategroyFlags() const { return category;}

	class HAZEL_API Event
	{
	friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategroyFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		virtual bool Handled() const {return m_Handled;}
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategroyFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};


	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		// a function which takes T& returns bool
	public:
		EventDispatcher(Event& event) : m_Event(event) {}
		
		template<typename T>
		bool DisPatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}