#include "hzpch.h"
#include "Application.h"
#include "Events/Event.h"
#include "Input.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Hazel/Renderer/Renderer.h"

#include <glad/glad.h>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::m_Instance = nullptr;
	Application::Application()
	{
		HZ_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<VertexBuffer> VBTraingle(VertexBuffer::Create(vertices, sizeof(vertices)));

		//m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		VBTraingle->SetLayout(layout);
		//m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(VBTraingle);

		uint32_t indices[3] = { 0, 1, 2 }; 
		std::shared_ptr<IndexBuffer> IBTraingle(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		//m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		
		m_VertexArray->SetIndexBuffer(IBTraingle);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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

		m_ShaderTraingle.reset(new Shader(vertexSrc, fragmentSrc));


		m_VARect.reset(VertexArray::Create());
		
		float verticesRect[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> VBRect(VertexBuffer::Create(verticesRect, sizeof(verticesRect)));

		//m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layoutRect =
		{
			{ ShaderDataType::Float3, "a_Position" }
		};
		VBRect->SetLayout(layoutRect);
		//m_VertexBuffer->SetLayout(layout);

		m_VARect->AddVertexBuffer(VBRect);

		uint32_t indicesRect[6] = { 0, 1, 2,
									2, 3, 0 };
		std::shared_ptr<IndexBuffer> IBRect(IndexBuffer::Create(indicesRect, sizeof(indicesRect) / sizeof(uint32_t)));
		//m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VARect->SetIndexBuffer(IBRect);

		std::string vertexRectSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentRectSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;

			void main()
			{
				color = vec4(0.1f, 0.1f, 0.8f,1.0f);
			}
		)";

		m_ShaderRect.reset(new Shader(vertexRectSrc, fragmentRectSrc));

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.DisPatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//HZ_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}
	}

	void Application::Run() {
		while (m_Running)
		{	
			RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
			RenderCommand::Clear();

			Renderer::BeginScene();
			m_ShaderRect->Bind();
			m_VARect->Bind();
			RenderCommand::DrawIndexed(m_VARect);
			//glDrawElements(GL_TRIANGLES, m_VARect->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_ShaderTraingle->Bind();
			m_VertexArray->Bind();
			RenderCommand::DrawIndexed(m_VertexArray);
			//glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();
			auto [x,y] = Input::GetMousePosition();
			//HZ_CORE_TRACE("{0}, {1}", x, y);
			m_Window->OnUpdate();
			
		}
	}



	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
