#include"hzpch.h"
#include "Application.h"

#include<Glad/glad.h>
#include"ZJY/Renderer/Renderer.h"

#include"ZJY/Core/Input.h"

#include"GLFW/glfw3.h"


namespace ZJY {

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		Z_CORE_ASSERT(!s_Instance);
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));
		//m_Window->SetVSync(false);//������60fps

		//������Ⱦ��
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);//�¼Ӵ��ڣ�����ջ��
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
		while (m_Running) 
		{
			//����delta time
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastframeTime;
			m_LastframeTime = time;

			//ͼ�����
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			//main kind of game loop
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