#pragma once

#include "Hazel/Renderer/GraphicsContext.h"
#include "Hazel/Core/Window.h"

struct GLFWwindow;

namespace Hazel
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow*);
		~OpenGLContext();

		void Init();
		void SwapBuffer();

	private:
		GLFWwindow* m_WindowHandle;
	};

}