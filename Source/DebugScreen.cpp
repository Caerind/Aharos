#include "DebugScreen.hpp"

namespace ah
{

DebugScreen::DebugScreen() : mFont(nullptr), mCharsize(20), mShowDebugScreen(false), mValues()
{
}

void DebugScreen::setDebugInfo(std::string const& id, std::string const& value)
{
    if (mValues.find(id) == mValues.end())
    {
        sf::Text t;
        t.setColor(sf::Color::White);
        mValues[id] = t;
        mValues[id].setString(id + " : " + value);
        update();
    }
    mValues[id].setString(id + " : " + value);
}

void DebugScreen::showDebugScreen(bool show)
{
    mShowDebugScreen = show;
}

bool DebugScreen::isDebugScreenVisible()
{
    return mShowDebugScreen;
}

void DebugScreen::setFont(sf::Font& font)
{
    mFont = std::make_shared<sf::Font>(font);
    update();
}

void DebugScreen::setCharsize(std::size_t charsize)
{
    mCharsize = charsize;
    update();
}

void DebugScreen::update()
{
    if (mFont != nullptr)
    {
        float pos = 5.f;
        for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
        {
            itr->second.setFont(*mFont);
            itr->second.setCharacterSize(mCharsize);
            itr->second.setPosition(sf::Vector2f(5.f,pos));
            pos += itr->second.getGlobalBounds().height + 5.f;
        }
    }
}

void DebugScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mShowDebugScreen)
    {
        target.setView(target.getDefaultView());
        for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
        {
            target.draw(itr->second);
        }
    }
}

}
