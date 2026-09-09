#pragma once

#include "Zero/Layer/Layer.h"

namespace Zero
{
    class UILayer : public Layer
    {
      public:
        UILayer() : Layer{"UILayer"}, m_Time{0.0f} {}
        ~UILayer() = default;

      public:
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUIRender() override;

      public:
        void Begin();
        void End();

      private:
        float m_Time;
    };
}
