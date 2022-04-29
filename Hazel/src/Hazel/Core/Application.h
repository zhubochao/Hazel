#pragma once
#include"Core.h"
#include"Window.h"	
#include "Hazel/Core/LayerStack.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/ImGui/ImGuiLayer.h"



namespace Hazel{
	class HAZEL_API Application
	{
	public:
		Application(const std::string& name="Hazel App");
		virtual ~Application();

		void OnEvent(Event& e);
		
		void Run();
		void Close();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		ImGuiLayer* Get_ImGuiLayer() { return m_ImGuiLayer; }

		static inline Application& Get() { return *m_Instance;}
		inline Window& GetWindow() {return *m_Window;}
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* m_Instance;
		Application();

		float m_LastFrameTime = 0.0f;

	};


	//To be defined in CLIENT
	Application* CreateApplication();
}

