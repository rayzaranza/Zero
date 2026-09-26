#pragma once
#include "Entity.h"

namespace Zero {

class ScriptableEntity {
public:
  template <typename T> T& GetComponent();
private:
  Entity m_Entity{};
  friend class Scene;
};

}

template <typename T>
T& Zero::ScriptableEntity::GetComponent() {
  return m_Entity.GetComponent<T>();
}
