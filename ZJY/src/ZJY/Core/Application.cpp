#include"hzpch.h"
#include "Application.h"

#include<Glad/glad.h>

#include"ZJY/Core/Input.h"

namespace ZJY {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

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

	Application::Application()
	{
		Z_CORE_ASSERT(!s_Instance);
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);//�¼Ӵ��ڣ�����ջ��

		glGenVertexArrays(1, &m_VertexArray);//����һ��VAO���κ����Ķ������Ե��õĶ���洢�����VAO��
		glBindVertexArray(m_VertexArray);

		float vertives[3 * 7] = {
			-0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f , 1.0f,
			 0.5f , -0.5f , 0.0f , 0.0f , 0.0f , 1.0f , 1.0f,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f , 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Creat(vertives, sizeof(vertives)));
		{
			BufferLayout layout = {
				{ShaderDataType::Float3,"a_Position"},
				{ShaderDataType::Float4,"a_Color"}
			};

			m_VertexBuffer->SetLayeout(layout);
		}
		
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)//Ҫ�е������ſ��Ա���
		{
			//����������Щ�������浽����������
			glEnableVertexAttribArray(index);
			//��������ʵ���ϴ洢�ڶ��������У������Ƕ��㻺����
			glVertexAttribPointer(index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGlBaseType(element.Type), 
				element.Normalized ? GL_FALSE : GL_FALSE, 
				layout.GetStride(),
				(const void*)element.Offset);//0�±꣬����������,�ֽڳ��ȣ������ƫ����
			index++;
		}

		//glEnableVertexAttribArray(1);
		////��������ʵ���ϴ洢�ڶ��������У������Ƕ��㻺����
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)12);//4�±꣬4��������,������3����������4����������ӣ�ƫ�ƴ�0�����ĵط���ʼ

		//����������Ҳ����Ԫ�ػ�����,�������ǵ������˳���
		unsigned int indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Creat(indices, sizeof(indices) / sizeof(uint32_t)));//sizeof(indices) / sizeof(uint32_t)=3

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0 );
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5,1.0);
				color = v_Color;
			}

		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));//����ָ��Ͳ�������Ψһ���൱��m_Shader=new std::unique_ptr<Shader>()
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		//Z_CORE_INFO("{0}", e);//��¼����ʱ������

		EventDispatcher dispatcher(e);//�������¼������ͻᴥ��ʲô���͵ķ���,���type
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//Z_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}