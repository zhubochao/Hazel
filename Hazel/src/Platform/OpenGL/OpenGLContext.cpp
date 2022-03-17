#include "hzpch.h"

#include "OpenGLContext.h"
#include "Glad/glad.h"
#include <GLFW/glfw3.h>


namespace Hazel
{
	Hazel::OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window)
	{
		HZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!")
	}

	Hazel::OpenGLContext::~OpenGLContext()
	{

	}

	void Hazel::OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "FAIL TO INITIALIZE Glad!");

		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HZ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HZ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void Hazel::OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}


