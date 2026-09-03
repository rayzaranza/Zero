#pragma once

#include "Event/Event.h"
#include "Layer/Layer.h"

namespace Zero
{
    class ZERO_API UILayer : public Layer
    {
      public:
        UILayer();
        ~UILayer();

      public:
        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

      private:
        float m_Time { 0.0f };
    };
}
