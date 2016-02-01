#ifndef SES_ENTITY_HPP
#define SES_ENTITY_HPP

#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <Box2D/Dynamics/b2Body.h>

#include "../Helper/TypeToString.hpp"
#include "../Helper/pugixml.hpp"
#include "../Helper/PhysicConverter.hpp"

#include "Component.hpp"
#include "ComponentFilter.hpp"

namespace ses
{

class World;

class Entity
{
    public:
        Entity(std::string const& id);
        ~Entity();

        typedef std::shared_ptr<Entity> Ptr;

        const std::string& getId() const;

        void setPosition(sf::Vector2f const& position);
        sf::Vector2f getPosition() const;

        void setRotation(float rotation);
        float getRotation() const;

        void setPositionZ(float z);
        float getPositionZ() const;

        template<typename T, typename ... Args>
        T& addComponent(Args&& ... args);

        template<typename T>
        bool hasComponent();
        bool hasComponent(std::string const& componentId);
        bool hasComponents(ComponentFilter const& filter);

        template<typename T>
        T& getComponent();

        template<typename T>
        void removeComponent();
        void removeComponent(std::string const& componentId);
        void removeComponents();

        std::size_t getComponentsCount() const;

        void remove();
        bool isMarkedForRemoval() const;

        void update();

        b2Body* getBody();
        void addFixture(b2FixtureDef fDef);
        bool hasFixture(std::string fName);
        void removeFixture(std::string fName);
        void removeAllFixtures();

        void load(pugi::xml_node& entity);
        void save(pugi::xml_node& entity);

        friend World;

        template<typename T>
        static bool registerComponent();

    protected:
        static std::map<std::string,std::function<Component::Ptr()>> mComponentFactories;

    protected:
        const std::string mId;
        b2Body* mBody;
        World* mWorld;
        float mZ;
        bool mMarkedForRemoval;
        std::map<std::string,Component::Ptr> mComponents;
};

template<typename T, typename ... Args>
T& Entity::addComponent(Args&& ... args)
{
    mComponents[lp::type<T>()] = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    mComponents[lp::type<T>()]->mEntity = this;
    update();
    return getComponent<T>();
}

template<typename T>
bool Entity::hasComponent()
{
    return hasComponent(lp::type<T>());
}

template<typename T>
T& Entity::getComponent()
{
    assert(hasComponent<T>());
    return static_cast<T&>(*mComponents.at(lp::type<T>()));
}

template<typename T>
void Entity::removeComponent()
{
    removeComponent(lp::type<T>());
}

template<typename T>
bool Entity::registerComponent()
{
    std::string t = lp::type<T>();
	mComponentFactories[t] = [] ()
	{
		return Component::Ptr(new T());
	};
	return true;
}

typedef std::vector<Entity::Ptr> EntityVector;

} // namespace ses

#endif // SES_ENTITY_HPP
