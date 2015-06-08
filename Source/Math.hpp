#ifndef AH_MATH_HPP
#define AH_MATH_HPP

#include <random>
#include <ctime>
#include <cassert>

#include <SFML/System/Vector2.hpp>

namespace ah
{

constexpr float PI = 3.14159265359;

float toRadian(float deg);
float toDegree(float rad);

int random(int min, int max);
unsigned int random(unsigned int min, unsigned int max);
float random(float min, float max);

float length(sf::Vector2f const& vector);
void setLength(sf::Vector2f& vector, float newLength);
sf::Vector2f unitVector(sf::Vector2f const& vector);

} // namespace ah

#endif // AH_MATH_HPP
