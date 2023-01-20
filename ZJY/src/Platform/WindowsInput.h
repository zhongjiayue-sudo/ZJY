#pragma once

#include"ZJY/Core/Input.h"

namespace ZJY {
	class WindowsInput:public Input
	{
	public:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePositionImpl() override;

	private:

	};
}
