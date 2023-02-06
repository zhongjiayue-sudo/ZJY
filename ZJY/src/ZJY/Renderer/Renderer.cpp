#include"hzpch.h"
#include"Renderer.h"

#include"RenderCommand.h"

#include"Platform/OpenGL/OpenGLShader.h"

namespace ZJY
{
	Renderer::SceneData* Renderer::m_sceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_sceneData->ViewPorjectionMatrix = camera.GetViewPorjectionMatrix();
	}
	void Renderer::EndScene()
	{

	}
	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		//dynamic_pointer_cast��dynamic_cast�÷����ƣ���ָ��������ָ��ʱ������ת������dynamic_Cast ����벻��ͨ������ʱ��Ҫʹ��dynamic_pointer_cast
		//��Ҫ��;���������ָ������ð�ȫ��ת�����������ָ������ã������������ָ������õ��÷��麯����
		//����ǻ���ָ������õ��õ����麯������ת������������ʱ������������麯����
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjuection", m_sceneData->ViewPorjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}