#ifndef LP_COLLISIONSHAPE_HPP
#define LP_COLLISIONSHAPE_HPP

#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace lp
{

class CollisionShape : public sf::Drawable
{
    public:
        typedef std::shared_ptr<CollisionShape> Ptr;

        CollisionShape();
        CollisionShape(sf::FloatRect const& rect);
		CollisionShape(sf::ConvexShape const& shape);

        void setPointCount(unsigned int count);
        unsigned int getPointCount() const;

        void setPoint(unsigned int id, sf::Vector2f pos);
        sf::Vector2f getPoint(unsigned int id) const;

        bool intersects(CollisionShape::Ptr shape);
        bool intersects(CollisionShape shape);
        bool contains(sf::Vector2f point);

        void move(sf::Vector2f const& movement);
        void cancelLastMovement();

        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::Vector2f mPosition;
        std::vector<sf::Vector2f> mPoints;

        sf::Vector2f mLastMovement;
};

} // namespace lp

#endif // LP_COLLISIONSHAPE_HPP
