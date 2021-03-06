#include "hzpch.h"
#include "LayerStack.h"


namespace Hazel
{
	void Hazel::LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin()+ m_LayerInsertIndex, layer);
		//layer->OnAttach();
		m_LayerInsertIndex++;
	}

	void Hazel::LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		//overlay->OnAttach();
	}

	void Hazel::LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.end())
		{
			//layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void Hazel::LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, overlay);
		if (it != begin() + m_LayerInsertIndex)
		{
			//overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	}

}

