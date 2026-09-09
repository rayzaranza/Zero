#include "Zero/Renderer/RenderCommand.h"

#include "Zero/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Zero
{
    RendererAPI* RenderCommand::s_RendererAPI{new OpenGLRendererAPI()};

}
