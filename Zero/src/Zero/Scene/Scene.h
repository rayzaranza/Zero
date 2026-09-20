#pragma once
#include <entt/entt.hpp>

namespace Zero {

class Scene {
public:
  Scene();
  ~Scene();
private:
  entt::registry m_Registry;
};

}
