#include"hzpch.h"
#include"VertexArray.h"
#include"Renderer.h"
#include"Platform/OpenGL/OpenGLVertexArray.h"

namespace ZJY
{
	VertexArray* VertexArray::Creat()
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}
