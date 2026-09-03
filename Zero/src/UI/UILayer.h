#pragma once

#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
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
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
        bool OnMouseScrolledEvent(MouseScrolledEvent& event);
        bool OnMouseMovedEvent(MouseMovedEvent& event);
        bool OnKeyPressedEvent(KeyPressedEvent& event);
        bool OnKeyReleasedEvent(KeyReleasedEvent& event);
        bool OnKeyTypedEvent(KeyTypedEvent& event);
        bool OnWindowResizedEvent(WindowResizedEvent& event);

      private:
        float m_Time { 0.0f };
    };
}
