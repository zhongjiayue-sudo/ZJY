#include"hzpch.h"
#include"OpenGLContext.h"

#include<GLFW/glfw3.h>
#include<Glad/glad.h>

namespace ZJY
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle)
	{
		Z_CORE_ASSERT(windowHandle, "window Handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		Z_CORE_ASSERT(status, "Failed to initialize Glad!");



		const GLubyte* name = glGetString(GL_VENDOR); //返回负责当前OpenGL实现厂商的名字
		const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
		const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本号

		printf("OpenGL实现厂商的名字：%s\n", name);
		printf("渲染器标识符：%s\n", biaoshifu);
		printf("OpenGL实现的版本号：%s\n", OpenGLVersion);

	}
	void OpenGLContext::SwapBuffers()
	{

		glfwSwapBuffers(m_windowHandle);
	}
}