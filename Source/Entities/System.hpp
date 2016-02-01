#ifndef SES_SYSTEM_HPP
#define SES_SYSTEM_HPP

#include <memory>
#include <vector>

#include "EntityContainer.hpp"

#include "../Helper/Packet.hpp"
#include "../Helper/TypeToString.hpp"

namespace ses
{

class World;

class System
{
    public:
        System();
        virtual ~System();

        typedef std::shared_ptr<System> Ptr;

        virtual void handleMessage(sf::Packet& packet);
        virtual void onEntityUpdate(Entity::Ptr entity);
        virtual void removeEntity(Entity::Ptr entity);

        friend World;

    protected:
        World* mWorld;
        EntityContainer mEntities;
};

} // namespace ses

#endif // SES_SYSTEM_HPP
