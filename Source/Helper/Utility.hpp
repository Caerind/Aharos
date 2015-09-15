#ifndef LP_UTILITY_HPP_INCLUDED
#define LP_UTILITY_HPP_INCLUDED

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include "Math.hpp"

namespace lp
{

sf::FloatRect getViewRect(sf::View const& v);

template<typename T>
void centerOrigin(T& t);

template<typename T>
sf::Vector2<T> getRectCenter(const sf::Rect<T>& r);

template<typename T>
sf::Vector2<T> getRectPosition(const sf::Rect<T>& r);

template<typename T>
sf::Vector2<T> getRectSize(const sf::Rect<T>& r);

float distanceRectPoint(sf::FloatRect const& rect, sf::Vector2f const& point);

template<typename T>
std::array<sf::Vector2<T>,4> getPoint(const sf::Rect<T>& r);

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////

template<typename T>
void centerOrigin(T& t)
{
    t.setOrigin(t.getGlobalBounds().width/2,t.getGlobalBounds().height/2);
}

template<typename T>
sf::Vector2<T> getRectCenter(const sf::Rect<T>& r)
{
    return sf::Vector2<T>(r.left + r.width /2, r.top + r.height /2);
}

template<typename T>
sf::Vector2<T> getRectPosition(const sf::Rect<T>& r)
{
    return sf::Vector2<T>(r.left, r.top);
}

template<typename T>
sf::Vector2<T> getRectSize(const sf::Rect<T>& r)
{
    return sf::Vector2<T>(r.width, r.height);
}

template<typename T>
std::array<sf::Vector2<T>,4> getPoint(const sf::Rect<T>& r)
{
    std::array<sf::Vector2<T>,4> array;
    array[0] = sf::Vector2f(r.left,r.top);
    array[1] = sf::Vector2f(r.left+r.width,r.top);
    array[2] = sf::Vector2f(r.left+r.width,r.top+r.height);
    array[3] = sf::Vector2f(r.left,r.top+r.height);
    return array;
}

} // namespace lp

#endif // LP_UTILITY_HPP_INCLUDED
