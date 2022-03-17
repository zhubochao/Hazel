#pragma once



namespace Hazel
{
	class Context
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;

	private:

	};

}