#include "CollisionManager.hpp"

namespace lp
{

CollisionManager::CollisionManager()
{
}

void CollisionManager::add(CollisionShape::Ptr shape)
{
    mCollisions.push_back(shape);
}

void CollisionManager::remove(CollisionShape::Ptr shape)
{
    for (auto itr = mCollisions.begin(); itr != mCollisions.end(); itr++)
    {
        if ((*itr) == shape)
        {
            mCollisions.erase(itr);
        }
    }
}

bool CollisionManager::intersect(CollisionShape::Ptr shape)
{
    if (shape == nullptr)
        return false;
    for (unsigned int i = 0; i < mCollisions.size(); i++)
        if (mCollisions[i] != nullptr)
            if (mCollisions[i]->intersects(shape))
                return true;
    return false;
}

bool CollisionManager::intersect(CollisionShape& shape)
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
        if (shape.intersects(mCollisions[i]))
            return true;
    return false;
}

bool CollisionManager::contains(sf::Vector2f point)
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
    {
        if (mCollisions[i] != nullptr)
        {
            if (mCollisions[i]->contains(point))
            {
                return true;
            }
        }
    }
    return false;
}

void CollisionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mCollisions.size(); i++)
    {
        target.draw(*mCollisions[i]);
    }
}

} // namespace lp
