#include"hzpch.h"
#include"OpenGLRenderderAPI.h"

#include<glad/glad.h>

namespace ZJY
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc();�C���OpenGL���Դ��ɫ��Ŀ����ɫ����ȡ����������һ��ϵ����Դ��ɫ���Ե�ϵ����Ϊ��Դ���ӡ�
		//��Ŀ����ɫ���Ե�ϵ����Ϊ��Ŀ�����ӡ�����Ȼ����ӣ������͵õ����µ���ɫ��
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

