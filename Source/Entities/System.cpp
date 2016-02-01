#include "System.hpp"
#include "World.hpp"

namespace ses
{

System::System()
: mWorld(nullptr)
{
}

System::~System()
{
    mWorld = nullptr;
}

void System::handleMessage(sf::Packet& packet)
{
}

void System::onEntityUpdate(Entity::Ptr entity)
{
    mEntities.update(entity);
}

void System::removeEntity(Entity::Ptr entity)
{
    mEntities.remove(entity);
}

} // namespace ses
