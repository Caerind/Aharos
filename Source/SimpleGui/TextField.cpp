#include "TextField.hpp"

namespace sg
{

TextField::TextField() : Box()
{
    mFocused = false;
    mCallbacks.resize(1);
    mMaxSize = 999;
}

TextField::TextField(Widget* parent) : Box(parent)
{
    mFocused = false;
    mCallbacks.resize(1);
}

void TextField::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mEnabled && mVisible)
    {
        if (event.type == sf::Event::MouseMoved && getGlobalBounds().contains(mousePosition) && !mActive)
        {
            setActive(true);
            if (mCallbacks.size() >= 1)
                if (mCallbacks[0])
                    mCallbacks[0]();
        }
        if (event.type == sf::Event::MouseMoved && !getGlobalBounds().contains(mousePosition) && mActive)
        {
            setActive(false);
            if (mCallbacks.size() >= 1)
                if (mCallbacks[0])
                    mCallbacks[0]();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && mActive)
        {
            gainFocus();
        }
        if ((event.type == sf::Event::MouseButtonPressed && !mActive)
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
        || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return))
        {
            lostFocus();
        }
        if (mFocused)
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
            {
                std::string str = mText.getString();
                std::size_t pos = str.find('|');
                if(pos > 0 && pos != std::string::npos)
                {
                    str.erase(pos, 1);
                    pos--;
                    str.insert(pos, "|");
                    mText.setString(str);
                }
                updateText();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
            {
                std::string str = mText.getString();
                std::size_t pos = str.find('|');
                if((pos+1) < str.size() && pos != std::string::npos)
                {
                    str.erase(pos, 1);
                    pos++;
                    str.insert(pos, "|");
                    mText.setString(str);
                }
                updateText();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == '\e'
                || event.text.unicode == 13
                || event.text.unicode == '\t')
				{
					lostFocus();
				}
				else if(event.text.unicode == '\b')
				{
					std::string str = mText.getString();
                    std::size_t pos = str.find('|');
                    if(pos > 0 && pos != std::string::npos)
                    {
                        str.erase(pos-1, 1);
                        mText.setString(str);
                    }
				}
				else
				{
					if (getString().size() < mMaxSize)
                    {
                        std::string str = mText.getString();
                        std::size_t pos = str.find('|');
                        if (pos != std::string::npos)
                        {
                            str.insert(pos, 1, (char)event.text.unicode);
                        }
                        mText.setString(str);
                    }
				}
				updateText();
            }
        }
    }
}

void TextField::setString(std::string const& string)
{
    std::string str = string;
    if(mEnabled && mVisible && mFocused)
    {
        str += '|';
    }
    mText.setString(str);
}

std::string TextField::getString()
{
    std::string str = mText.getString();
    std::size_t pos = str.find('|');
    if (pos != std::string::npos)
    {
        str.erase(pos, 1);
    }
    return str;
}

void TextField::setStringMaxSize(unsigned int maxSize)
{
    mMaxSize = maxSize;
}

void TextField::gainFocus()
{
    if(!mFocused)
    {
        std::string str = mText.getString();
        str.push_back('|');
        mText.setString(str);

        mFocused = true;
    }
}

void TextField::lostFocus()
{
    if(mFocused)
    {
        std::string str = mText.getString();
        size_t pos = str.find('|');
        if (pos != std::string::npos)
        {
            str.erase(pos, 1);
        }
        mText.setString(str);

        mFocused = false;
    }
}

}
