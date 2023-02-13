#pragma once

#include"ZJY/Renderer/OrthographicCamera.h"
#include"ZJY/Core/Timestep.h"

#include"ZJY/Events/ApplicationEvent.h"//����resize
#include"ZJY/Events/MouseEvent.h"//����¼�


namespace ZJY
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);//aspectRatio��߱�

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_rotation;

		glm::vec3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

}