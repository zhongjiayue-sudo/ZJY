#include"hzpch.h"
#include"RenderCommand.h"

#include"Platform/OpenGL/OpenGLRenderderAPI.h"
namespace ZJY
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}