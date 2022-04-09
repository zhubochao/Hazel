#pragma once

#include "Hazel.h"

#include "Level.h"
#include <imgui/imgui.h>

class GameLayer : public Hazel::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnDetach() override;
	virtual void OnAttach() override;

	virtual void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& e) override;
	bool OnMouseButtonPressed(Hazel::MouseButtonEvent& e);
	bool OnWindowResize(Hazel::WindowResizeEvent& e);

private:
	void CreateCamera(uint32_t width, uint32_t height);

private:
	Hazel::Ref<Hazel::OrthographicCamera> m_Camera;
	Level m_Level;
	ImFont* m_Font;
	float m_Time;
	bool m_Blink;

	enum class GameState
	{
		Play = 0, MainMenu = 1, GameOver = 2
	};
	GameState m_State = GameState::MainMenu;
};