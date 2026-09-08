#pragma once

#include "Zero/Core.h"
#include "Zero/Event/Event.h"

namespace Zero
{
    class Layer
    {
      public:
        Layer(const std::string& name = "Layer") : m_Name { name } {}

      public:
        inline virtual void OnAttach() {}
        inline virtual void OnDetach() {}
        inline virtual void OnUpdate() {}
        inline virtual void OnUIRender() {}
        inline virtual void OnEvent(Event& event) {}

      public:
        inline const std::string& GetName() const { return m_Name; }

      private:
        std::string m_Name {};
    };
}
