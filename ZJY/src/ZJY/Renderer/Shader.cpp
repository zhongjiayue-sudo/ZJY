#include"hzpch.h"
#include"Shader.h"

#include"Renderer.h"
#include"Platform/OpenGL/OpenGLShader.h"

namespace ZJY
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
