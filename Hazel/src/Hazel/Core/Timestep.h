#pragma once

namespace Hazel
{
	class Timestep
	{
	public:
		Timestep(float time = 0) : m_Time(time)
		{

		}

		operator float() {return m_Time;}

		const float GetTime() const { return m_Time;}
		const float GetMillisecondTime() {return m_Time * 1000;}
	private:
		float m_Time;
	};
}
