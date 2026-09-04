#pragma once

#include "Event/Event.h"
#include "Zero/Core.h"

namespace Zero
{
    class ZERO_API Layer
    {
      public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

      public:
        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnUpdate();
        virtual void OnEvent(Event& event);
        virtual void OnUIRender();

      public:
        const std::string& GetName() const;

      private:
        std::string m_Name {};
    };
}
