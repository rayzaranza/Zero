#pragma once

#include "Zero/Core.h"
#include "Zero/Event/Event.h"
#include "Zero/Time/DeltaTime.h"

namespace Zero
{
    class Layer
    {
      public:
        Layer(const String& name = "Layer") : m_Name{ name } {}

      public:
        inline virtual void OnAttach() {}
        inline virtual void OnDetach() {}
        inline virtual void OnUpdate(DeltaTime deltaTime) {}
        inline virtual void OnUIRender() {}
        inline virtual void OnEvent(Event& event) {}

      public:
        inline const String& GetName() const { return m_Name; }

      private:
        String m_Name{};
    };
}
