#include"hzpch.h"
#include"OpenGLVertexArray.h"
#include"glad/glad.h"
namespace ZJY
{
	static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ZJY::ShaderDataType::Float:    return GL_FLOAT;
			case ZJY::ShaderDataType::Float2:	return GL_FLOAT;
			case ZJY::ShaderDataType::Float3:	return GL_FLOAT;
			case ZJY::ShaderDataType::Float4:	return GL_FLOAT;
			case ZJY::ShaderDataType::Mat3:		return GL_FLOAT;
			case ZJY::ShaderDataType::Mat4:		return GL_FLOAT;
			case ZJY::ShaderDataType::Int:		return GL_INT;
			case ZJY::ShaderDataType::Int2:		return GL_INT;
			case ZJY::ShaderDataType::Int3:		return GL_INT;
			case ZJY::ShaderDataType::Int4:		return GL_INT;
			case ZJY::ShaderDataType::Bool:		return GL_BOOL;
		}

		Z_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);//创建一个VAO，任何随后的顶点属性调用的都会存储在这个VAO中
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		Z_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)//要有迭代器才可以遍历
		{
			//这两步把这些东西保存到顶点数组中
			glEnableVertexAttribArray(index);
			//顶点属性实际上存储在顶点数组中，而不是顶点缓冲区
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGlBaseType(element.Type),
				element.Normalized ? GL_FALSE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);//0下标，三个浮点数,字节长度，最后是偏移量
			index++;
		}
		m_vertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_indexBuffer = indexBuffer;
	}
}