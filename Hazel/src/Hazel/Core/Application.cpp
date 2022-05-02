#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/Event.h"
#include "Input.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Core/Timestep.h"

#include <glad/glad.h>
#include "glfw/glfw3.h"

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::m_Instance = nullptr;
	Application::Application(const std::string& name)
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = Scope<Window>(Window::Create(WindowProps(name)));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		HZ_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	void Application::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));


		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend();++it)
		{
			if (e.m_Handled)
			{
				break;
			}

			(*it)->OnEvent(e);
		}
	}

	void Application::Run() 
	{
		HZ_PROFILE_FUNCTION();

		while (m_Running)
		{
			HZ_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			if (!m_Minimized)
			{
				{
					HZ_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}
				
				{
					HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");
					m_ImGuiLayer->Begin();

					for (Layer* layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}

					m_ImGuiLayer->End();
				}
			}
			m_Window->OnUpdate();
			
		}
	}



	void Application::Close()
	{
		m_Running = false;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

}
