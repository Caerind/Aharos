#include "DebugScreen.hpp"

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
    }
    mValues[id].setString(id + " : " + value);
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

void DebugScreen::showDebugScreen()
{
    mShowDebugScreen = true;
}

void DebugScreen::hideDebugScreen()
{
    mShowDebugScreen = false;
}

bool DebugScreen::isDebugScreenVisible()
{
    return mShowDebugScreen;
}

void DebugScreen::update()
{
    if (mFont != nullptr)
    {
        float pos = 5.f;
        for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
        {
            itr->second.setFont(*mFont);
            itr->second.setCharacterSize(mCharSize);
            itr->second.setPosition(sf::Vector2f(5.f,pos));
            pos += itr->second.getGlobalBounds().height + 5.f;
        }
    }
}

void DebugScreen::render(sf::RenderTarget& target) const
{
    if (mFont != nullptr && mShowDebugScreen)
    {
        target.setView(target.getDefaultView());
        for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
        {
            target.draw(itr->second);
        }
    }
}