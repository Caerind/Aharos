#include "SpriteSystem.hpp"

namespace ses
{

SpriteSystem::SpriteSystem()
{
    mEntities.requiresOne({lp::type<SpriteComponent>(),lp::type<TileLayerComponent>()});
}

void SpriteSystem::render(sf::RenderTarget& target)
{
    mEntities.sort([](Entity::Ptr a, Entity::Ptr b) -> bool
    {
        if (a->getPositionZ() != b->getPositionZ())
        {
            return (a->getPositionZ() > b->getPositionZ());
        }
        else
        {
            return (a->getPosition().y < b->getPosition().y);
        }
    });

    for (std::size_t i = 0; i < mEntities.size(); i++)
    {
        ses::Entity::Ptr e = mEntities.at(i);
        if (e != nullptr)
        {
            sf::Transform t;
            t.translate(e->getPosition());
            t.rotate(e->getRotation());
            sf::RenderStates states;
            states.transform = t;
            if (e->hasComponent<SpriteComponent>())
            {
                target.draw(e->getComponent<SpriteComponent>(),states);
            }
            if (e->hasComponent<TileLayerComponent>())
            {
                target.draw(e->getComponent<TileLayerComponent>(),states);
            }
        }
    }
}

} // namespace ses
