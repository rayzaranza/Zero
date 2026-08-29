#include "RenderSystem.h"

#include "../../../Logger/Logger.h"
#include "../../../Renderer/Renderer.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/TransformComponent.h"

ZY::RenderSystem::RenderSystem()
{
	requireComponent<ZY::TransformComponent>();
	requireComponent<ZY::SpriteComponent>();
	LOG("Renderer system created.");
}

void ZY::RenderSystem::draw(const ZY::VertexArray& vertexArray, const ZY::Shader& shader) const
{
	for (ZY::Entity entity : entities)
	{
		const ZY::TransformComponent& transform{ entity.getComponent<ZY::TransformComponent>() };
		const ZY::SpriteComponent& sprite{ entity.getComponent<ZY::SpriteComponent>() };

		VertexBuffer vertexBuffer{ { transform.position.x, transform.position.y } };
		IndexBuffer indexBuffer{ { } };

		ZY::Renderer::draw(vertexArray, shader);
	}
}

