#include"hzpch.h"
#include"OpenGLRenderderAPI.h"

#include<glad/glad.h>

namespace ZJY
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc();–混合OpenGL会把源颜色和目标颜色各自取出，并乘以一个系数（源颜色乘以的系数称为“源因子”
		//，目标颜色乘以的系数称为“目标因子”），然后相加，这样就得到了新的颜色。
	}
	void ZJY::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void ZJY::OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void ZJY::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

	}
}

