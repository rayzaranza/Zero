#include "Layer.h"

namespace Zero
{
    Layer::Layer(const std::string& name) : m_Name { name }
    {}

    Layer::~Layer()
    {}

    void Layer::OnAttach()
    {}

    void Layer::OnDetach()
    {}

    void Layer::OnUpdate()
    {}

    void Layer::OnEvent(Event& event)
    {}

    const std::string& Layer::GetName() const
    {
        return m_Name;
    }
}
