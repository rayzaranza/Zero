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
