cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(zero LANGUAGES CXX C)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(zero
        src/Main.cpp
        src/Application/Application.cpp
        src/Application/Application.h
        src/Window/Window.cpp
        src/Window/Window.h
        src/Window/Window.cpp
        src/Window/Window.h
        src/Core/Types.h
        src/Logger/Logger.cpp
        src/Logger/Logger.h
)

target_link_libraries(zero
        PRIVATE
        glm::glm
        glad::glad
        glfw
        spdlog::spdlog
)

target_compile_definitions(zero
        PUBLIC
        GLFW_INCLUDE_NONE
        GLM_ENABLE_EXPERIMENTAL
)
