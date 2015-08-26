#include "Box.hpp"

namespace sg
{

Box::Box() : Widget()
{
    mTextureRects.resize(3);
    mFillColors.resize(3);
    mCallbacks.resize(2);
    mAlign = TextAlign::Center;
    mPadding = 10.f;
    mUsingSprite = false;
}

Box::Box(Widget* parent) : Widget(parent)
{
    mTextureRects.resize(3);
    mFillColors.resize(3);
    mCallbacks.resize(2);
    mAlign = TextAlign::Center;
    mPadding = 10.f;
    mUsingSprite = false;
}

void Box::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mEnabled && mVisible)
    {
        if (getGlobalBounds().contains(mousePosition) && !mActive)
        {
            setActive(true);
            if (mCallbacks.size() >= 2)
                if (mCallbacks[1])
                    mCallbacks[1]();
        }
        if (!getGlobalBounds().contains(mousePosition) && mActive)
        {
            setActive(false);
            if (mCallbacks.size() >= 2)
                if (mCallbacks[1])
                    mCallbacks[1]();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mActive)
        {
            if (mCallbacks.size() >= 1)
                if (mCallbacks[0])
                    mCallbacks[0]();
        }
    }
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mShape,states);
    target.draw(mText,states);
}

void Box::setEnabled(bool enabled)
{
    mEnabled = enabled;
    updateShape();
}

void Box::setActive(bool active)
{
    mActive = active;
    updateShape();
}

void Box::setTexture(sf::Texture& texture)
{
    mShape.setTexture(&texture);
    mUsingSprite = true;
}

void Box::setTextureRect(sf::IntRect rect, std::size_t id)
{
    mUsingSprite = true;
    if (id >= 0 && id < mTextureRects.size())
    {
        mTextureRects[id] = rect;
        if (id == 0 && mTextureRects.size() >= 3)
        {
            if (mTextureRects[1] == sf::IntRect(0,0,0,0))
            {
                mTextureRects[1] = rect;
            }
            if (mTextureRects[2] == sf::IntRect(0,0,0,0))
            {
                mTextureRects[2] = rect;
            }
        }
        updateShape();
    }
}

void Box::setOutlineThickness(float thickness)
{
    mShape.setOutlineThickness(thickness);
}

void Box::setOutlineColor(sf::Color color)
{
    mShape.setOutlineColor(color);
}

void Box::setFillColor(sf::Color color, std::size_t id)
{
    mUsingSprite = false;
    if (id >= 0 && id < mFillColors.size())
    {
        mFillColors[id] = color;
        if (id == 0 && mFillColors.size() >= 3)
        {
            if (mFillColors[1] == sf::Color(0,0,0))
            {
                mFillColors[1] = color;
            }
            if (mFillColors[2] == sf::Color(0,0,0))
            {
                mFillColors[2] = color;
            }
        }
        updateShape();
    }
}

void Box::setSize(sf::Vector2f size)
{
    mShape.setSize(size);
    mSize = size;
    updateText();
}

void Box::setFont(sf::Font& font)
{
    mText.setFont(font);
    updateText();
}

void Box::setString(std::string const& string)
{
    mText.setString(string);
    updateText();
}

void Box::setCharacterSize(std::size_t charsize)
{
    mText.setCharacterSize(charsize);
    updateText();
}

void Box::setTextColor(sf::Color color)
{
    mText.setColor(color);
}

void Box::setTextAlign(TextAlign align)
{
    mAlign = align;
    updateText();
}

void Box::setPadding(float padding)
{
    mPadding = padding;
    updateText();
}

void Box::setCallback(std::function<void()> callback, std::size_t id)
{
    if (id >= 0 && id < mCallbacks.size())
    {
        mCallbacks[id] = std::move(callback);
    }
}

sf::RectangleShape& Box::getShape()
{
    return mShape;
}

sf::Text& Box::getText()
{
    return mText;
}

void Box::updateShape()
{
    if (mUsingSprite)
    {
        if (!mEnabled && mTextureRects.size() >= 3) // 2
        {
            mShape.setTextureRect(mTextureRects[2]);
        }
        else if (mEnabled && mActive && mTextureRects.size() >= 2) // 1
        {
            mShape.setTextureRect(mTextureRects[1]);
        }
        else if (mTextureRects.size() >= 1) // 0
        {
            mShape.setTextureRect(mTextureRects[0]);
        }
    }
    else
    {
        if (!mEnabled && mTextureRects.size() >= 3) // 2
        {
            mShape.setFillColor(mFillColors[2]);
        }
        else if (mEnabled && mActive && mTextureRects.size() >= 2) // 1
        {
            mShape.setFillColor(mFillColors[1]);
        }
        else if (mTextureRects.size() >= 1) // 0
        {
            mShape.setFillColor(mFillColors[0]);
        }
    }
}

void Box::updateText()
{
    sf::Vector2f position;
    switch (mAlign)
    {
        case TextAlign::Left: position.x = mPadding; break;
        case TextAlign::Center: position.x = getGlobalBounds().width/2 - mText.getGlobalBounds().width/2; break;
        default: position.x = getGlobalBounds().width - mPadding;
    }
    position.y = getGlobalBounds().height/2 - mText.getGlobalBounds().height/2;
    mText.setPosition(position);
}

}
