#pragma once

#include <array>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "Zero/Core/Types.h"
#include "Zero/Logger/Logger.h"
#include "Zero/Profiler/Profiler.h"

#ifdef ZR_PLATFORM_WINDOWS
# define NOMINMAX
# include <Windows.h>
#endif
