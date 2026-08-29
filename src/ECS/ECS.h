#pragma once

#include <bitset>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace ZY
{
    constexpr unsigned int MAX_COMPONENTS { 64 };
    using Signature = std::bitset<MAX_COMPONENTS>;

    class Entity
    {
    public:
        unsigned int id;
        class Registry* registry;

    public:
        Entity(unsigned int id);
        Entity(const Entity& entity) = default;

    public:
        Entity& operator = (const Entity& other) = default;
        bool operator == (const Entity& other) const;
        bool operator != (const Entity& other) const;
        bool operator > (const Entity& other) const;
        bool operator < (const Entity& other) const;
        template <typename T, typename ...TArgs> void addComponent(TArgs&& ...args);
        template <typename T> void removeComponent();
        template <typename T> T& getComponent() const;
        template <typename T> bool hasComponent() const;
    };



    struct BaseComponent
    {
    protected:
        static unsigned int nextId;
    };



    template <typename T>
    class Component : BaseComponent
    {
    public:
        static unsigned int getId();
    };



    class System
    {
    public:
        Signature signature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

    public:
        void addEntity(Entity entity);
        void removeEntity(Entity entity);
        template <typename T> void requireComponent();
    };



    class BasePool
    {
    public:
        virtual ~BasePool()
        {}
    };



    template <typename T>
    class Pool : public BasePool
    {
    private:
        std::vector<T> data;

    public:
        Pool(unsigned int size = 128);
        virtual ~Pool() = default;

    public:
        void add(T object);
        T& get(unsigned int index);
        void set(unsigned int index, T object);
        T& operator [](unsigned int index) const;
    };



    class Registry
    {
    public:
        unsigned int entityCount;
        std::vector<std::shared_ptr<BasePool>> componentPools;
        std::vector<Signature> entityComponentSignatures;
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        std::set<Entity> createEntityQueue;
        std::set<Entity> destroyEntityQueue;

    public:
        Registry();

    public:
        Entity createEntity();
        void addEntityToMatchingSystems(Entity entity);
        void update();

        template <typename T, typename ...TArgs> void addComponent(Entity entity, TArgs&& ...args);
        template <typename T> void removeComponent(Entity entity);
        template <typename T> T& getComponent(Entity entity) const;
        template <typename T> bool hasComponent(Entity entity) const;

        template <typename T, typename ...TArgs> void addSystem(TArgs&& ...args);
        template <typename T> void removeSystem();
        template <typename T> bool hasSystem() const;
        template <typename T> T& getSystem();
    };

}





template <typename T>
void ZY::System::requireComponent()
{
    unsigned int componentId { ZY::Component<T>::getId() };
    signature.set(componentId);
}

template <typename T>
unsigned int ZY::Component<T>::getId()
{
    static unsigned int id { nextId++ };
    return id;
}

template <typename T, typename ...TArgs>
void ZY::Registry::addComponent(ZY::Entity entity, TArgs&& ...args)
{
    const unsigned int componentId { ZY::Component<T>::getId() };
    if (componentId >= componentPools.size())
    {
        componentPools.resize(componentId + 1, nullptr);
    }

    if (!componentPools[componentId])
    {
        componentPools[componentId] = std::make_shared<ZY::Pool<T>>();
    }

    std::shared_ptr<ZY::Pool<T>> componentPool { std::static_pointer_cast<ZY::Pool<T>>(componentPools[componentId]) };
    T component { std::forward<TArgs>(args)... };
    componentPool->set(entity.id, component);
    entityComponentSignatures[entity.id].set(componentId);

    LOG("Component #{} added to Entity #{}.", componentId, entity.id);
}

template <typename T>
void ZY::Registry::removeComponent(ZY::Entity entity)
{
    const unsigned int componentId { ZY::Component<T>::getId() };
    entityComponentSignatures[entity.id].set(componentId, false);
}

template <typename T>
T& ZY::Registry::getComponent(ZY::Entity entity) const
{
    const unsigned int componentId { ZY::Component<T>::getId() };
    std::shared_ptr<ZY::Pool<T>> componentPool { std::static_pointer_cast<ZY::Pool<T>>(componentPools[componentId]) };
    return componentPool->get(entity.id);
}

template <typename T>
bool ZY::Registry::hasComponent(ZY::Entity entity) const
{
    const unsigned int componentId { ZY::Component<T>::getId() };
    return entityComponentSignatures[entity.id].test(componentId);
}

template <typename T, typename ...TArgs>
void ZY::Registry::addSystem(TArgs && ...args)
{
    std::shared_ptr<T> system { std::make_shared<T>(std::forward<TArgs>(args)...) };
    systems.insert(std::make_pair(std::type_index(typeid(T)), system));
}

template <typename T>
void ZY::Registry::removeSystem()
{
    systems.erase(systems.find(typeid(T)));
}

template <typename T>
bool ZY::Registry::hasSystem() const
{
    return systems.contains(typeid(T));
}

template <typename T>
T& ZY::Registry::getSystem()
{
    auto system { systems.find(std::type_index(typeid(T))) };
    return *(std::static_pointer_cast<T>(system->second));
}

template <typename T>
ZY::Pool<T>::Pool(unsigned int size)
{
    data.resize(size);
}

template <typename T>
void ZY::Pool<T>::add(T object)
{
    data.push_back(object);
}

template <typename T>
T& ZY::Pool<T>::get(unsigned int index)
{
    return static_cast<T&>(data[index]);
}

template <typename T>
void ZY::Pool<T>::set(unsigned int index, T object)
{
    data[index] = object;
}

template <typename T>
T& ZY::Pool<T>::operator [](unsigned int index) const
{
    return data[index];
}

template <typename T, typename ...TArgs>
void ZY::Entity::addComponent(TArgs && ...args)
{
    registry->addComponent<T>(*this, std::forward<TArgs>(args)...);
}

template <typename T>
void ZY::Entity::removeComponent()
{
    registry->removeComponent<T>(*this);
}

template <typename T>
T& ZY::Entity::getComponent() const
{
    return registry->getComponent<T>(*this);
}

template <typename T>
bool ZY::Entity::hasComponent() const
{
    return registry->hasComponent<T>(*this);
}
