add_executable(Sandbox
  "src/Sandbox.h"
	"src/Sandbox.cpp"
  "src/Sandbox2D.h"
  "src/Sandbox2D.cpp"
)

target_link_libraries(Sandbox PRIVATE Zero)
