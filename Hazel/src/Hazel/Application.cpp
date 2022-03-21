#include "hzpch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Input.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Core/Timestep.h"

#include <glad/glad.h>
#include "glfw/glfw3.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::m_Instance = nullptr;
	Application::Application()
	{
		HZ_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.DisPatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	void Application::Run() {
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}
			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();
			auto [x,y] = Input::GetMousePosition();
			//HZ_CORE_TRACE("{0}, {1}", x, y);
			m_Window->OnUpdate();
			
		}
	}



	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
