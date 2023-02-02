#pragma once

namespace ZJY
{
	class Timestep
	{
	public:
		Timestep(float time=0.0f)
			:m_Time(time)
		{

		}

		operator float() const { return m_Time; }//��Timestep���͵�����ʱ֮��ʹ�õ�ʱm_Time;

		float GetSecond()const { return m_Time; }
		float GetMilliseSecond()const { return m_Time * 1000.0f; }
	private:
		float m_Time ;
	};

}
