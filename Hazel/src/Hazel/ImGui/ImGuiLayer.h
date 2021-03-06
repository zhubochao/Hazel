#pragma once

#include "Hazel/Core/Layer.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"


namespace Hazel
{
	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e)override;
		//virtual void OnImGuiRender() override;

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = false;
	};

}