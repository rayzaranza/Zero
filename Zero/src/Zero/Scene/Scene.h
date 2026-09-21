#pragma once
#include "Zero/Time/DeltaTime.h"
#include <entt/entt.hpp>

namespace Zero {

class Scene {
public:
  Scene();
  ~Scene();
  void OnUpdate(const DeltaTime deltaTime);
  void OnRender();
  entt::entity CreateEntity();
  entt::registry& GetRegistry();
private:
  entt::registry m_Registry;
};

}
