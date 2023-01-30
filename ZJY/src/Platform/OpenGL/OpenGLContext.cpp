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



		const GLubyte* name = glGetString(GL_VENDOR); //���ظ���ǰOpenGLʵ�ֳ��̵�����
		const GLubyte* biaoshifu = glGetString(GL_RENDERER); //����һ����Ⱦ����ʶ����ͨ���Ǹ�Ӳ��ƽ̨
		const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //���ص�ǰOpenGLʵ�ֵİ汾��

		printf("OpenGLʵ�ֳ��̵����֣�%s\n", name);
		printf("��Ⱦ����ʶ����%s\n", biaoshifu);
		printf("OpenGLʵ�ֵİ汾�ţ�%s\n", OpenGLVersion);

	}
	void OpenGLContext::SwapBuffers()
	{

		glfwSwapBuffers(m_windowHandle);
	}
}