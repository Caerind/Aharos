#include "PhysicConverter.hpp"

namespace Physic
{

sf::Vector2f toSfml(b2Vec2 const& vec)
{
    return sf::Vector2f(metersToPixels(vec.x),metersToPixels(vec.y));
}

sf::Color toSfml(b2Color const& color)
{
    return sf::Color(color.r * 256.f,color.g * 256.f,color.b * 256.f);
}

sf::FloatRect toSfml(b2AABB const& aabb)
{
    return sf::FloatRect(Physic::toSfml(aabb.GetCenter() - aabb.GetExtents()),Physic::toSfml(2 * aabb.GetExtents()));
}

b2Vec2 toBox2D(sf::Vector2f const& vec)
{
    return b2Vec2(pixelsToMeters(vec.x),pixelsToMeters(vec.y));
}

b2Color toBox2D(sf::Color const& color)
{
    return b2Color(color.r / 256.f, color.g / 256.f, color.b / 256.f);
}

b2AABB toBox2D(sf::FloatRect const& rect)
{
    b2AABB aabb;
    aabb.upperBound.x = Physic::pixelsToMeters(rect.left);
    aabb.upperBound.y = Physic::pixelsToMeters(rect.top);
    aabb.lowerBound.x = Physic::pixelsToMeters(rect.left + rect.width);
    aabb.lowerBound.y = Physic::pixelsToMeters(rect.top + rect.height);
    return aabb;
}

} // namespace Physic
