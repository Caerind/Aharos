#include "Utility.hpp"

namespace lp
{

sf::FloatRect getViewRect(sf::View const& v)
{
    return sf::FloatRect(v.getCenter() - 0.5f * v.getSize(),v.getSize());
}

}
