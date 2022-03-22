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

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override {return m_VertexBuffers;}
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;}

		virtual void AddVertexBuffer(Ref<VertexBuffer>&) override;
		virtual void SetIndexBuffer(Ref<IndexBuffer>&) override;
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
	};
}