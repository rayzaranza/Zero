#include "Zero/Layer/Layer.h"


Zero::Layer::Layer(const std::string& name) : m_Name{ name }
{
}


const std::string& Zero::Layer::GetName() const
{
    return m_Name;
}


void Zero::Layer::OnAttach()
{
}


void Zero::Layer::OnDetach()
{
}


void Zero::Layer::OnUpdate(const DeltaTime deltaTime)
{
}


void Zero::Layer::OnRender()
{
}


void Zero::Layer::OnUIRender()
{
}


void Zero::Layer::OnEvent(Event& event)
{
}
