#include "hzpch.h"
#include "Application.h"
#include "Events/Event.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Hazel {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {}

	void Application::Run() {
		while (true)
		{
			m_Window->OnUpdate();
		}
	}

}
