add_executable(Sandbox
    "src/Sandbox.h"
	"src/Sandbox.cpp"

    "src/Layers/ExampleLayer.h"
    "src/Layers/ExampleLayer.cpp"

    "src/Layers/ExampleLayer2D.h"
    "src/Layers/ExampleLayer2D.cpp"
)

target_link_libraries(Sandbox
    PRIVATE
        Zero
)
