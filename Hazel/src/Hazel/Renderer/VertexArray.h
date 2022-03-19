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

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& ) = 0;
		virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer>&) = 0;


		static VertexArray* Create();
	};
}