#include "Utility.hpp"

namespace lp
{

sf::FloatRect getViewRect(sf::View const& v)
{
    return sf::FloatRect(v.getCenter() - 0.5f * v.getSize(),v.getSize());
}

float distanceRectPoint(sf::FloatRect const& rect, sf::Vector2f const& point)
{
	float d = 1000000.f;
	for (float i = 0.f; i < rect.width; i++)
	{
		d = std::min(d,lp::distance(point, sf::Vector2f(rect.left + i, rect.top)));
		d = std::min(d,lp::distance(point, sf::Vector2f(rect.left + i, rect.top + rect.height)));
	}
	for (float i = 0.f; i < rect.height; i++)
	{
		d = std::min(d,lp::distance(point, sf::Vector2f(rect.left, rect.top + i)));
		d = std::min(d,lp::distance(point, sf::Vector2f(rect.left + rect.width, rect.top + i)));
	}
	return d;
}

}
