#pragma once

#include "Hazel/Renderer/VertexArray.h"
#include "glad/glad.h"

namespace Hazel
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray() override;
		OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers;}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;}

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) override;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>&) override;
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};
}