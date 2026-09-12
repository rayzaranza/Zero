#pragma once

#include "Zero/Types/Color.h"
#include "Zero/Types/Math.h"

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Zero
{
    //===========================================================================================
    //  Primitives
    //===========================================================================================
    using F32 = float;
    using F64 = double;

    using U8 = uint8_t;
    using U16 = uint16_t;
    using U32 = uint32_t;
    using U64 = uint64_t;

    using I8 = int8_t;
    using I16 = int16_t;
    using I32 = int32_t;
    using I64 = int64_t;

    using String = std::string;
    using Boolean = bool;
    using Length = size_t;

    using Degrees = F32;
    using Seconds = F32;
    using Milliseconds = F32;

    using RendererID = U32;

    //===========================================================================================
    //  Containers
    //===========================================================================================
    template <typename T> using Array = std::vector<T>;
    template <typename T, Length S> using FixedArray = std::array<T, S>;
    template <typename K, typename V> using Map = std::unordered_map<K, V>;
    template <typename A, typename B> using Pair = std::pair<A, B>;

    //===========================================================================================
    //  Pointers
    //===========================================================================================
    template <typename T> using Scope = std::unique_ptr<T>;
    template <typename T> using Ref = std::shared_ptr<T>;
    template <typename T> using WeakRef = std::weak_ptr<T>;

    //===========================================================================================
    //  Functions
    //===========================================================================================
    template <typename T> using Function = std::function<T>;

    template <typename T, typename... TArgs>
    constexpr Ref<T> CreateRef(TArgs&&... args)
    {
        return std::make_shared<T>(std::forward<TArgs>(args)...);
    }
}
