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
		//m_Window->SetVSync(false);//不限制60fps

		//创建渲染器
		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);//新加窗口，放入栈中
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		//Z_CORE_INFO("{0}", e);//记录窗口时间的输出

		EventDispatcher dispatcher(e);//如果这个事件发生就会触发什么类型的方法,检测type
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
			//设置delta time
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastframeTime;
			m_LastframeTime = time;

			//图层更新
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