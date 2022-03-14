
#include"Hazel.h"
#include "glm/glm.hpp"

#include <glm/gtc/type_ptr.hpp>


class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Example") 
	{
		glm::mat4 trans(1.0f);
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 1, 0));
		//0  0  1  0
		//0  1  0  0
		//-1 0  0  0
		//0  0  0  1
		float* p = glm::value_ptr(trans);
		std::cout << typeid(p).name() << std::endl;
		for (int i = 0; i < 16; i++) {
			std::cout << *p << ' ';
			p++;
		}
		std::cout << std::endl;
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
		PushOverlay(new Hazel::ImGuiLayer());
	};
	~SandBox() {};


};


Hazel::Application* Hazel::CreateApplication() {
	return new SandBox();
}
