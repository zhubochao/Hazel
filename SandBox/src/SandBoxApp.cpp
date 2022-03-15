
#include"Hazel.h"
#include "glm/glm.hpp"

#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Example") 
	{
		
	}

	void OnUpdate() override 
	{
		//HZ_INFO("ExampleLayer::Update"); 
		if(Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab is pressed(poll)");

	}

	void OnEvent(Hazel::Event& event) override 
	{ 
		Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			HZ_TRACE("{0}", (char)e.GetKeyCode());
			if (e.GetKeyCode() == HZ_KEY_TAB)
				HZ_TRACE("Tab is pressed!(event)");
		}
	}
	
};


class SandBox : public Hazel::Application
{
public:
	SandBox() 
	{ 
		PushLayer(new ExampleLayer());
	};
	~SandBox() {};


};


Hazel::Application* Hazel::CreateApplication() {
	return new SandBox();
}
