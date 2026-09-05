#pragma once

#include "Zero/Event/ApplicationEvent.h"
#include "Zero/Event/KeyEvent.h"
#include "Zero/Event/MouseEvent.h"
#include "Zero/Layer/Layer.h"

namespace Zero
{
    class UILayer : public Layer
    {
      public:
        UILayer();
        ~UILayer();

      public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUIRender() override;

      public:
        void Begin();
        void End();

      private:
        float m_Time { 0.0f };
    };
}
