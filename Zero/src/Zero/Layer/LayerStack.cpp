#include "LayerStack.h"

Zero::LayerStack::~LayerStack() {
  for (Layer* layer : m_Layers) {
    layer->OnDetach();
    delete layer;
  }
}

void Zero::LayerStack::PushLayer(Layer* layer) {
  m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
  m_LayerInsertIndex++;
}

void Zero::LayerStack::PushOverlay(Layer* overlay) {
  m_Layers.emplace_back(overlay);
}

void Zero::LayerStack::PopLayer(Layer* layer) {
  Array<Layer*>::iterator layerIterator{ std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer) };
  if (layerIterator != m_Layers.end() + m_LayerInsertIndex) {
    layer->OnDetach();
    m_Layers.erase(layerIterator);
    m_LayerInsertIndex--;
  }
}

void Zero::LayerStack::PopOverlay(Layer* overlay) {
  Array<Layer*>::iterator layerIterator{ std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay) };
  if (layerIterator != m_Layers.end()) {
    overlay->OnDetach();
    m_Layers.erase(layerIterator);
  }
}

Zero::Array<Zero::Layer*>::iterator Zero::LayerStack::begin() {
  return m_Layers.begin();
}

Zero::Array<Zero::Layer*>::iterator Zero::LayerStack::end() {
  return m_Layers.end();
}

Zero::Array<Zero::Layer*>::reverse_iterator Zero::LayerStack::rbegin() {
  return m_Layers.rbegin();
}

Zero::Array<Zero::Layer*>::reverse_iterator Zero::LayerStack::rend() {
  return m_Layers.rend();
}
