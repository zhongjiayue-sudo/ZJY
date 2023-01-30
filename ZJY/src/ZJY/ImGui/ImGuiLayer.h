#pragma once

#include"ZJY/Core/Layer.h"
#include"ZJY/Events/KeyEvent.h"
#include"ZJY/Events/MouseEvent.h"
#include"ZJY/Events/ApplicationEvent.h"

namespace ZJY
{
	class ZJY_API ImGuiLayer:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		/// <summary>
		/// ÖØÐ´Ðéº¯Êý
		/// </summary>

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	//	void OnEvent(Event& event);
	//private:
	//	//ImGui Event
	//	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	//	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	//	bool OnMouseMovedEvent(MouseMovedEvent& e);
	//	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	//	bool OnKeyPressedEvent(KeyPressedEvent& e);
	//	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	//	bool OnKeyTypedEvent(KeyTypedEvent& e);
	//	bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}