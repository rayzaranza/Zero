add_executable(Sandbox
    "src/Sandbox.h"
	"src/Sandbox.cpp"
)

target_link_libraries(Sandbox
    PRIVATE
        Zero
)
