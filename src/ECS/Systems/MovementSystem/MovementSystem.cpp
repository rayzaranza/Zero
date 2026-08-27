#include "MovementSystem.h"

#include "../../../Logger/Logger.h"
#include "../../Components/RigidBodyComponent.h"
#include "../../Components/TransformComponent.h"

ZY::Movement::Movement()
{
	requireComponent<ZY::TransformComponent>();
	requireComponent<ZY::RigidBodyComponent>();
}

void ZY::Movement::update() const
{
	for (ZY::Entity entity : entities)
	{
		ZY::TransformComponent& transform{ entity.getComponent<ZY::TransformComponent>() };
		const ZY::RigidBodyComponent& rigidBody{ entity.getComponent<ZY::RigidBodyComponent>() };

		transform.position += rigidBody.velocity;

		LOG("Transform position is x: {}, y: {}.", transform.position.x, transform.position.y);
	}
}
