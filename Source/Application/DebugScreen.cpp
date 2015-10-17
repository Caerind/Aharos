#include "DebugScreen.hpp"

namespace ah
{

DebugScreen::DebugScreen() : mFont(nullptr), mColor(sf::Color::White), mCharsize(20), mShowDebugScreen(true), mValues()
{
}

void DebugScreen::setDebugInfo(std::string const& id, std::string const& value)
{
    auto itr = mValues.find(id);
    mValues[id].setString(id + " : " + value);
    if (itr == mValues.end())
    {
        update();
    }
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

void DebugScreen::setColor(sf::Color color)
{
    mColor = color;
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
            itr->second.setColor(mColor);
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
        sf::View view = target.getView();
        target.setView(target.getDefaultView());
        for (auto itr = mValues.begin(); itr != mValues.end(); itr++)
        {
            target.draw(itr->second);
        }
        target.setView(view);
    }
}

}
