#include "Math.hpp"

namespace lp
{

std::mt19937 RandomEngine(static_cast<unsigned long>(std::time(nullptr)));

float toRadian(float deg)
{
    return PI * deg / 180.f;
}

float toDegree(float rad)
{
    return 180.f * rad / PI;
}

int random(int min, int max)
{
    assert(min <= max);
	std::uniform_int_distribution<int> d(min, max);
	return d(RandomEngine);
}

unsigned int random(unsigned int min, unsigned int max)
{
    assert(min <= max);
	std::uniform_int_distribution<unsigned int> d(min, max);
	return d(RandomEngine);
}

float random(float min, float max)
{
    assert(min <= max);
	std::uniform_real_distribution<float> d(min, max);
	return d(RandomEngine);
}

float length(sf::Vector2f const& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float distance(sf::Vector2f const& p1, sf::Vector2f const& p2)
{
    return length(p1-p2);
}

void setLength(sf::Vector2f& vector, float newLength)
{
    assert(vector != sf::Vector2f());
	vector *= newLength / length(vector);
}

sf::Vector2f unitVector(sf::Vector2f const& vector)
{
    assert(vector != sf::Vector2f());
	return vector / length(vector);
}

} // namespace lp
