#include"hzpch.h"
#include"Texture.h"

#include"Renderer.h"
#include"Platform/OpenGL/OpenGLTexture.h"

namespace ZJY
{
	/// <summary>
	/// 
	/// </summary>
	/// <param name="path"></param>
	/// <returns>Ref:shared_ptr</returns>
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}