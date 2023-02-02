#include"hzpch.h"
#include"OpenGLBuffer.h"

#include"glad/glad.h"

namespace ZJY
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) //�����size����ͨ���ֽڴ���
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/// <summary>
	/// IndexBuffer
	/// </summary>
	/// <param name="indices"></param>
	/// <param name="size"></param>

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)//�����count����ͨ��Ԫ�ش��䣬��Ҫ���Դ�С-��count * sizeof(uint32_t)
		:m_count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}