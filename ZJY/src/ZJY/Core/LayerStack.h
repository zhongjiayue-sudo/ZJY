#pragma once

#include"ZJY/Core.h"
#include"Layer.h"

#include<vector>

namespace ZJY {
	class ZJY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() {
			return m_Layers.begin();
		}//µü´úÆ÷

		std::vector<Layer*>::iterator end() {
			return m_Layers.end();
		}

	private:
		std::vector<Layer*> m_Layers;//ÆÕÍ¨Ö¸Õë
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}