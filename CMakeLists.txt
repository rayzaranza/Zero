cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ZY")

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable (ZY 
	"src/Main.cpp"
	"src/Window/Window.h"
	"src/Window/Window.cpp"
	"src/Renderer/Renderer.h"
	"src/Renderer/Renderer.cpp"
	"src/Buffer/VertexBuffer.h"
	"src/Buffer/VertexBuffer.cpp"
	"src/Buffer/IndexBuffer.cpp"
	"src/Buffer/IndexBuffer.cpp"
	"src/Buffer/VertexArray.h"
	"src/Buffer/VertexArray.cpp"
	"src/Shader/Shader.h"
	"src/Shader/Shader.cpp"
	"src/Asset/Asset.h"
	"src/Asset/Asset.cpp"
	"src/Camera/Camera.h"
	"src/Camera/Camera.cpp"
	"src/Logger/Logger.h"
	"src/Logger/Logger.cpp"
	"src/ECS/ECS.h"
	"src/ECS/ECS.cpp"
	"src/ECS/Components/RigidBodyComponent.h"
	"src/ECS/Components/TransformComponent.h"
	"src/ECS/Components/SpriteComponent.h"
	"src/ECS/Systems/MovementSystem/MovementSystem.h"
	"src/ECS/Systems/MovementSystem/MovementSystem.cpp"
 )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ZY PROPERTY CXX_STANDARD 23)
endif()

target_link_libraries(ZY PRIVATE 
	glm::glm 
	glad::glad 
	glfw
	spdlog::spdlog
)