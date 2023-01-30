#pragma once
#include"ZJY/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace ZJY
{
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		 void Init() override;
		 void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};

}