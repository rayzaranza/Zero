#pragma once
#include "Entity.h"

namespace Zero {

class ScriptableEntity {
public:
  virtual ~ScriptableEntity() = default;
  template <typename T> T& GetComponent();
protected:
  virtual void OnCreate();
  virtual void OnDestroy();
  virtual void OnUpdate(const DeltaTime deltaTime);
private:
  Entity m_Entity{};
  friend class Scene;
};

}

template <typename T>
T& Zero::ScriptableEntity::GetComponent() {
  return m_Entity.GetComponent<T>();
}
