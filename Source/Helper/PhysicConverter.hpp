#ifndef LP_PHYSICCONVERTER_HPP
#define LP_PHYSICCONVERTER_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <Box2D/Box2D.h>

namespace Physic
{
    // Pixels / Meters
    constexpr double PIXELS_PER_METERS = 32.0;
    template<typename T>
    constexpr T pixelsToMeters(const T& x)
    {
        return x/PIXELS_PER_METERS;
    }
    template<typename T>
    constexpr T metersToPixels(const T& x)
    {
        return x*PIXELS_PER_METERS;
    }

    // Degrees / Radians
    constexpr double PI = 3.14159265358979323846;
    template<typename T>
    constexpr T degToRad(const T& x)
    {
        return PI*x/180.0;
    }
    template<typename T>
    constexpr T radToDeg(const T& x)
    {
        return 180.0*x/PI;
    }

    sf::Vector2f toSfml(b2Vec2 const& vec);
    sf::Color toSfml(b2Color const& color);
    sf::FloatRect toSfml(b2AABB const& aabb);

    b2Vec2 toBox2D(sf::Vector2f const& vec);
    b2Color toBox2D(sf::Color const& color);
    b2AABB toBox2D(sf::FloatRect const& rect);

} // namespace Physic

#endif // LP_PHYSICCONVERTER_HPP
