#pragma once
#include <memory>
#include <expected>


namespace Zero {


template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using Scope = std::unique_ptr<T>;

template <typename T, typename K>
using Result = std::expected<T, K>;

template <typename T, typename... TArgs>
constexpr Ref<T> CreateRef(TArgs&&... args);

template <typename T, typename... TArgs>
constexpr Scope<T> CreateScope(TArgs&&... args);


} // Zero


template <typename T, typename... TArgs>
constexpr Zero::Ref<T> Zero::CreateRef(TArgs&&... args)
{
    return std::make_shared<T>(std::forward<TArgs>(args)...);
}

template <typename T, typename... TArgs>
constexpr Zero::Scope<T> Zero::CreateScope(TArgs&&... args)
{
    return std::make_unique<T>(std::forward<TArgs>(args)...);
}
