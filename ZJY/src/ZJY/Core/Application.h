#pragma once

#include"ZJY/Core.h"
#include"ZJY/Events/Event.h"
#include"ZJY/Window.h"
#include"ZJY/Events/ApplicationEvent.h"

#include"ZJY/Core/LayerStack.h"

#include"ZJY/ImGui/ImGuiLayer.h"

#include"ZJY/Renderer/Shader.h"

namespace ZJY {
	class ZJY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		ImGuiLayer* m_ImGuiLayer;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	Application* CreatApplication();
}

