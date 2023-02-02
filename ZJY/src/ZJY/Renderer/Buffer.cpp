#include"hzpch.h"
#include"Buffer.h"

#include"Renderer.h"
#include"Platform/OpenGL/OpenGLBuffer.h"

//利用其他图形库
//#include"Platform/Direct3D/Direct3DBuffer.h"

namespace ZJY
{
	VertexBuffer* VertexBuffer::Creat(float* vertices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
				Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Creat(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetRendererAPI())
		{
		case RendererAPI::API::None:
			Z_CORE_ASSERT(false, "RendererAPI::None is currently no supported!"; return nullptr);
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, size);

		}
		Z_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}