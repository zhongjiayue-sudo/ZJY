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
		//dynamic_pointer_cast与dynamic_cast用法类似，当指针是智能指针时候，向下转换，用dynamic_Cast 则编译不能通过，此时需要使用dynamic_pointer_cast
		//主要用途：将基类的指针或引用安全地转换成派生类的指针或引用，并用派生类的指针或引用调用非虚函数。
		//如果是基类指针或引用调用的是虚函数无需转换就能在运行时调用派生类的虚函数。
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjuection", m_sceneData->ViewPorjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}