#pragma once
#include <array>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Zero {
  template <typename T> using Array = std::vector<T>;
  template <typename T, size_t S> using FixedArray = std::array<T, S>;
  template <typename K, typename V> using Map = std::unordered_map<K, V>;
  template <typename A, typename B> using Pair = std::pair<A, B>;
  template <typename T> using Function = std::function<T>;

  template <typename T> using Scope = std::unique_ptr<T>;
  template <typename T> using Ref = std::shared_ptr<T>;
  template <typename T> using WeakRef = std::weak_ptr<T>;

  template <typename T, typename... TArgs>
  constexpr Ref<T> CreateRef(TArgs&&... args) {
    return std::make_shared<T>(std::forward<TArgs>(args)...);
  }

  template <typename T, typename... TArgs>
  constexpr Scope<T> CreateScope(TArgs&&... args) {
    return std::make_unique<T>(std::forward<TArgs>(args)...);
  };
}
