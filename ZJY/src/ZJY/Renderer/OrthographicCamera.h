#pragma once
#include"glm/glm.hpp"

namespace ZJY
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Positon; }
		void SetPosition(const glm::vec3& positon) { m_Positon = positon; RecalulateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalulateViewMatrix();}

		const glm::mat4& GetViewMatrix() const{return  m_ViewMatrix;}
		const glm::mat4& GetProjectionMatrix() const {return  m_ProjectionMatrix;}
		const glm::mat4& GetViewPorjectionMatrix() const {return  m_ViewPorjectionMatrix;}

	private:
		void RecalulateViewMatrix();

	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewPorjectionMatrix;

		glm::vec3 m_Positon = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0.0f;
	};

}
