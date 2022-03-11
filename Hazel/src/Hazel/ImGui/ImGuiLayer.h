#pragma once

#include "Hazel/Layer.h"

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