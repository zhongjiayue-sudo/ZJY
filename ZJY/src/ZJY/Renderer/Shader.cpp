#include"hzpch.h"
#include"Shader.h"

#include"Renderer.h"
#include"Platform/OpenGL/OpenGLShader.h"

namespace ZJY
{
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(path);
		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name,vertexSrc, fragmentSrc);
		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		Z_CORE_ASSERT(!Exsits(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		Z_CORE_ASSERT(Exsits(name), "Shader not found!");
		return m_Shaders[name];
	}
	/// <summary>
	/// 代表找到最后一个都没有找到，所以shader不存在
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool ShaderLibrary::Exsits(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}
