#pragma once

#include "Hazel/Layer.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"


namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() ;
		void OnDetach() ;
		void OnUpdate() ;
		void OnEvent(Event& event);

		bool OnKeyPressedEvent(KeyPressedEvent& );
		bool OnKeyReleasedEvent(KeyReleasedEvent&);
		bool OnKeyTypedEvent(KeyTypedEvent&);
		bool OnMouseScrolledEvent(MouseScrolledEvent&);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& );
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent&);
		bool OnMouseMovedEvent(MouseMovedEvent&);
		bool OnWindowResizeEvent(WindowResizeEvent&);

	private:
		float m_Time = 0.0f;
	};

}