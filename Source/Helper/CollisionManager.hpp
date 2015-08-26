#ifndef LP_COLLISIONMANAGER_HPP
#define LP_COLLISIONMANAGER_HPP

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "CollisionShape.hpp"

namespace lp
{

class CollisionManager : public sf::Drawable
{
    public:
        CollisionManager();

        void add(CollisionShape::Ptr shape);
        void remove(CollisionShape::Ptr shape);

        bool intersect(CollisionShape::Ptr shape);
        bool intersect(CollisionShape& shape);
        bool contains(sf::Vector2f point);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        std::vector<CollisionShape::Ptr> mCollisions;
};

} // namespace lp

#endif // LP_COLLISIONMANAGER_HPP
