#include "CollisionShape.hpp"

namespace lp
{

CollisionShape::CollisionShape()
{
}

CollisionShape::CollisionShape(sf::FloatRect const& rect)
{
    mPoints.resize(4);
    mPoints[0] = sf::Vector2f(-rect.width * 0.5f, -rect.height * 0.5f);
    mPoints[1] = sf::Vector2f(rect.width * 0.5f, -rect.height * 0.5f);
    mPoints[2] = sf::Vector2f(rect.width * 0.5f, rect.height * 0.5f);
    mPoints[3] = sf::Vector2f(-rect.width * 0.5f, rect.height * 0.5f);
}

CollisionShape::CollisionShape(sf::ConvexShape const& shape)
{
	mPoints.resize(shape.getPointCount());
	for (unsigned int i = 0; i < shape.getPointCount(); i++)
	{
		mPoints[i] = shape.getPoint(i);
	}
}

void CollisionShape::setPointCount(unsigned int count)
{
    mPoints.resize(count);
}

unsigned int CollisionShape::getPointCount() const
{
    return mPoints.size();
}

void CollisionShape::setPoint(unsigned int id, sf::Vector2f pos)
{
    if (id >= 0 && id < getPointCount())
    {
        mPoints[id] = pos;
    }
}

sf::Vector2f CollisionShape::getPoint(unsigned int id) const
{
    if (id >= 0 && id < getPointCount())
    {
        return mPoints[id];
    }
    return sf::Vector2f(0,0);
}

bool CollisionShape::intersects(CollisionShape::Ptr shape)
{
    if (shape == nullptr)
        return false;
    for (unsigned int i = 0; i < getPointCount(); i++)
        if (shape->contains(getPoint(i) + getPosition()))
            return true;
    for (unsigned int i = 0; i < shape->getPointCount(); i++)
        if (contains(shape->getPoint(i) + shape->getPosition()))
            return true;
    return false;
}

bool CollisionShape::intersects(CollisionShape shape)
{
    for (unsigned int i = 0; i < getPointCount(); i++)
        if (shape.contains(getPoint(i) + getPosition()))
            return true;
    for (unsigned int i = 0; i < shape.getPointCount(); i++)
        if (contains(shape.getPoint(i) + shape.getPosition()))
            return true;
    return false;
}

bool CollisionShape::contains(sf::Vector2f point)
{
    point -= getPosition();
    for (unsigned int i = 0; i < getPointCount(); i++)
    {
        sf::Vector2f a = getPoint(i), b;
        if (i == getPointCount() - 1)
            b = getPoint(0) - a;
        else
            b = getPoint(i + 1) - a;
        if (b.x * (point.y - a.y) - b.y * (point.x - a.x) < 0)
            return false;
    }
    return true;
}

void CollisionShape::move(sf::Vector2f const& movement)
{
    mPosition += movement;
    mLastMovement = movement;
}

void CollisionShape::cancelLastMovement()
{
    mPosition -= mLastMovement;
    mLastMovement = sf::Vector2f();
}

void CollisionShape::setPosition(sf::Vector2f position)
{
    mPosition = position;
}

sf::Vector2f CollisionShape::getPosition() const
{
    return mPosition;
}

void CollisionShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::ConvexShape shape;
    shape.setPointCount(getPointCount());
    shape.setPosition(getPosition());
    for (unsigned int i = 0; i < getPointCount(); i++)
    {
        shape.setPoint(i,getPoint(i));
    }
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);
    target.draw(shape);
    sf::CircleShape c;
    c.setPosition(getPosition());
    c.setRadius(1);
    c.setFillColor(sf::Color::Green);
    target.draw(c);
}

} // namespace lp
