#include "../Logger/Logger.h"
#include "ECS.h"

unsigned int ZY::BaseComponent::nextId { 0 };

ZY::Entity::Entity(unsigned int id) :
    id { id },
    registry { nullptr }
{}

bool ZY::Entity::operator == (const ZY::Entity& other) const
{
    return id == other.id;
}

bool ZY::Entity::operator != (const ZY::Entity& other) const
{
    return id != other.id;
}

bool ZY::Entity::operator > (const ZY::Entity& other) const
{
    return id > other.id;
}

bool ZY::Entity::operator < (const ZY::Entity& other) const
{
    return id < other.id;
}

void ZY::System::addEntity(ZY::Entity entity)
{
    entities.push_back(entity);
}

void ZY::System::removeEntity(ZY::Entity entity)
{
    std::erase(entities, entity);
}

ZY::Registry::Registry()
    : entityCount { 0 }
{
    componentPools.reserve(100);
    entityComponentSignatures.reserve(400);
    systems.reserve(100);
}

ZY::Entity ZY::Registry::createEntity()
{
    const unsigned int entityId { entityCount++ };
    ZY::Entity entity { entityId };
    entity.registry = this;

    createEntityQueue.insert(entity);
    if (entity.id >= entityComponentSignatures.size())
    {
        entityComponentSignatures.resize(static_cast<std::vector<ZY::Signature, std::allocator<ZY::Signature>>::size_type>(entity.id) + 1);
    }

    LOG("Entity #{} created", entityId);
    return entity;
}

void ZY::Registry::addEntityToMatchingSystems(ZY::Entity entity)
{
    const ZY::Signature& entityComponentSignature { entityComponentSignatures[entity.id] };

    for (auto& system : systems)
    {
        const ZY::Signature& systemComponentSignature { system.second->signature };

        bool isSignatureMatching { (entityComponentSignature & systemComponentSignature) == systemComponentSignature };
        if (isSignatureMatching)
        {
            system.second->addEntity(entity);
        }
    }
}

void ZY::Registry::update()
{
    for (ZY::Entity entity : createEntityQueue)
    {
        addEntityToMatchingSystems(entity);
    }

    createEntityQueue.clear();
}
