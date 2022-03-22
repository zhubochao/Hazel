#pragma once

#include <memory>
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& ) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>&) = 0;


		static VertexArray* Create();
	};
}