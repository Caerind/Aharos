#include "Statistics.hpp"

Statistics Statistics::gInstance;
bool Statistics::gInitialised;

Statistics* Statistics::instance()
{
    return gInitialised ? &gInstance : nullptr;
}

void Statistics::add(std::string const& field, std::string const& defaultValue)
{
    if (instance() != nullptr)
    {
        sf::Text t;
        t.setString(field + " : " + defaultValue);
        t.setColor(sf::Color::White);
        instance()->mStats[field] = t;
        instance()->update();
    }
}

void Statistics::setValue(std::string const& field, std::string const& value)
{
    if (instance() != nullptr)
    {
        if (instance()->mStats.find(field) != instance()->mStats.end())
        {
            instance()->mStats.find(field)->second.setString(instance()->mStats.find(field)->first + " : " + value);
        }
    }
}

void Statistics::setFont(std::string const& filename)
{
    if (instance() != nullptr)
    {
        auto f = ResourceHolder::get<sf::Font>(filename);
        if (f != nullptr)
        {
            instance()->mFont = f;
        }
        instance()->update();
    }
}

void Statistics::setCharSize(unsigned int charSize)
{
    if (instance() != nullptr)
    {
        instance()->mCharSize = charSize;
        instance()->update();
    }
}

void Statistics::render()
{
    if (instance() != nullptr)
    {
        if (instance()->mFont != nullptr)
        {
            Window::setDefaultView();
            for (auto itr = instance()->mStats.begin(); itr != instance()->mStats.end(); itr++)
            {
                Window::draw(itr->second);
            }
        }
    }
}

void Statistics::update()
{
    if (mFont != nullptr)
    {
        float pos = 5.f;
        for (auto itr = mStats.begin(); itr != mStats.end(); itr++)
        {
            itr->second.setFont(*mFont);
            itr->second.setCharacterSize(mCharSize);
            itr->second.setPosition(sf::Vector2f(pos,5.f));
            pos += itr->second.getGlobalBounds().height + 5;
        }
    }
}

Statistics::Statistics()
{
    gInitialised = true;
    mFont = nullptr;
    mCharSize = 30;
}

Statistics::~Statistics()
{
    gInitialised = false;
}
