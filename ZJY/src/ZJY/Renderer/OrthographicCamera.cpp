#include"hzpch.h"

#include"OrthographicCamera.h"
#include"glm/gtc/matrix_transform.hpp"

namespace ZJY
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left,right,bottom,top,-1.0f,1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewPorjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;//��ʼ��

	}
	/// <summary>
	/// ���¼��������ÿ���ƶ�����ת֮��
	/// </summary>
	void OrthographicCamera::RecalulateViewMatrix()
	{
		//tranform=position*rotation
		glm::mat4 tranform = glm::translate(glm::mat4(1.0f), m_Positon)
			* glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		//�ƶ��ľ���Ҫ����ת��,inverse �෴��
		m_ViewMatrix = glm::inverse(tranform);
		m_ViewPorjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}