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
		}//迭代器

		std::vector<Layer*>::iterator end() {
			return m_Layers.end();
		}

	private:
		std::vector<Layer*> m_Layers;//普通指针
		unsigned int m_LayerInsertIndex = 0;//索引
	};
}