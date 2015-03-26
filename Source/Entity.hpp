#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <string>

#include "Component.hpp"
#include "EntityManager.hpp"

class Entity
{
    public:
        friend class EntityManager;

        Entity(EntityManager* manager, std::string const& name = "");

        typedef std::shared_ptr<Entity> Ptr;

        template<typename T>
        T& addComponent(T* component);

        template<typename T>
        bool hasComponent();
        bool hasComponent(std::string const& type);
        bool hasComponents(ComponentFilter const& filter);

        template<typename T>
        void removeComponent();
        void removeAllComponents();

        template<typename T>
        T& getComponent();

        std::size_t getId() const;
        std::string getName() const;
        std::string getType() const;
        std::string getTag() const;

        void setType(std::string const& type);
        void setTag(std::string const& tag);

    private:
        static std::size_t gIdCounter;

        EntityManager* mManager;

        std::size_t mId; // Id of the entity : unique and precise
        std::string mName; // Name of the entity : for unique entity (example : player character...)
        std::string mType; // Type of the entity : for entities made by strict function "prefab entities"
        std::string mTag; // Tag of the entity : for group of "what you want" (example : you have few type of entities : Sorcerer & Magician which don't have the same components, you can get them both with the tag)

        ComponentArray mComponents;
};

template<typename T>
T& Entity::addComponent(T* component)
{
    mComponents[T::getType()] = component;
    if (mManager != nullptr)
    {
        mManager->update(mId);
    }
    return *component;
}

template<typename T>
bool Entity::hasComponent()
{
    return mComponents.find(T::getType()) != mComponents.end();
}

template<typename T>
void Entity::removeComponent()
{
    if (hasComponent<T>())
    {
        mComponents.erase(mComponents.find(T::getType()));
        if (mManager != nullptr)
        {
            mManager->update(mId);
        }
    }
}

template<typename T>
T& Entity::getComponent()
{
    assert(hasComponent<T>());

    return static_cast<T&>(*mComponents[T::getType()]);
}

#endif // ENTITY_HPP
