#pragma once
#include"Core.h"
#include"Window.h"	
#include "Hazel/LayerStack.h"

namespace Hazel{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);
		
		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *m_Instance;}
		inline Window& GetWindow() {return *m_Window;}
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* m_Instance;
	};


	//To be defined in CLIENT
	Application* CreateApplication();
}

