#include "Layer.h"

Zero::Layer::Layer(const std::string& name) : m_Name{ name } {
}

void Zero::Layer::OnAttach() {
}

void Zero::Layer::OnDetach() {
}

void Zero::Layer::OnRender() {
}

void Zero::Layer::OnUIRender() {
}

void Zero::Layer::OnEvent(Event& event) {
}

const std::string& Zero::Layer::GetName() const {
  return m_Name;
}
