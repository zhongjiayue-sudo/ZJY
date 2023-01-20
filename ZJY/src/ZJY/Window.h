#pragma once

#include "hzpch.h"
#include "ZJY/Core.h"
#include "ZJY/Events/Event.h"

namespace ZJY {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "ZJY Engine", 
			unsigned int width = 1280, 
			unsigned height = 720) 
			:Title(title), Width(width), Height(height) 
		{

		}
	};

	class ZJY_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallBack(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}