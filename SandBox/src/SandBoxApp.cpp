
#include"Hazel.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "glm/glm.hpp"
#include "imgui/imgui.h"


#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Example") ,  m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Hazel::VertexBuffer> VBTraingle(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

		Hazel::BufferLayout layout =
		{
			{ Hazel::ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float4, "a_Color" }
		};
		VBTraingle->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(VBTraingle);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Hazel::IndexBuffer> IBTraingle(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(IBTraingle);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_ShaderTraingle.reset(Hazel::Shader::Create(vertexSrc, fragmentSrc));

		m_VARect.reset(Hazel::VertexArray::Create());

		float verticesRect[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Hazel::VertexBuffer> VBRect(Hazel::VertexBuffer::Create(verticesRect, sizeof(verticesRect)));

		//m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		Hazel::BufferLayout layoutRect =
		{
			{ Hazel::ShaderDataType::Float3, "a_Position" }
		};
		VBRect->SetLayout(layoutRect);
		//m_VertexBuffer->SetLayout(layout);

		m_VARect->AddVertexBuffer(VBRect);

		uint32_t indicesRect[6] = { 0, 1, 2,
									2, 3, 0 };
		std::shared_ptr<Hazel::IndexBuffer> IBRect(Hazel::IndexBuffer::Create(indicesRect, sizeof(indicesRect) / sizeof(uint32_t)));
		//m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VARect->SetIndexBuffer(IBRect);

		std::string vertexRectSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentRectSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color,1.0f);
			}
		)";

		m_ShaderRect.reset(Hazel::Shader::Create(vertexRectSrc, fragmentRectSrc));
	}

		virtual void OnImGuiRender() override
		{

		}

		void OnUpdate(Hazel::Timestep ts) override
		{
			//HZ_TRACE("Frame Time {0}s, fps: {1}", ts.GetTime(), 1000.0/ts.GetMillisecondTime());
			if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
				m_CameraPosition.x -= m_CameraMoveSpeed * ts;
			else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
				m_CameraPosition.x += m_CameraMoveSpeed * ts;

			if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
				m_CameraPosition.y += m_CameraMoveSpeed * ts;
			else if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
				m_CameraPosition.y -= m_CameraMoveSpeed * ts;

			if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			
			Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Hazel::RenderCommand::Clear();

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);

			Hazel::Renderer::BeginScene(m_Camera);

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_ShaderRect)->Bind();
			std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_ShaderRect)->UploadUniformFloat3("u_Color", m_SquareColor);

			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Hazel::Renderer::Submit(m_ShaderRect, m_VARect, transform);
				}
			}

			
			Hazel::Renderer::Submit(m_ShaderTraingle, m_VertexArray);
			Hazel::Renderer::EndScene();
		}

		void OnEvent(Hazel::Event& event) override
		{

		}
	private:
		std::shared_ptr<Hazel::Shader> m_ShaderTraingle, m_ShaderRect;

		std::shared_ptr <Hazel::VertexArray> m_VertexArray, m_VARect;

		Hazel::OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition;

		float m_CameraMoveSpeed = 5.0f;

		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;
		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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
