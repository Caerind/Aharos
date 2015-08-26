#include "Timer.hpp"

namespace sg
{

Timer::Timer() : Box()
{
}

Timer::Timer(Widget* parent) : Box(parent)
{
}

void Timer::update(sf::Event const& event, sf::Vector2f mousePosition)
{
    if (mVisible && mEnabled)
    {
        if (isRunning() && getRemainingTime() < sf::seconds(0.05))
        {
            if (mCallbacks.size() >= 1)
                if (mCallbacks[0])
                    mCallbacks[0]();
            mVisible = false;
        }
        int total = static_cast<int>(getRemainingTime().asSeconds());
        int h = total / 3600;
        int m = (total - h * 3600) / 60;
        int s = total - h * 3600 - m * 60;
        std::string str;
        std::ostringstream oss;
        if (h == 0)
        {
            if (m != 0)
                oss << m << "m " << s << "s";
            else
                oss << s << "s";
        }
        else
        {
            oss << h << "h " << m << "m";
        }
        mText.setString(oss.str());
        updateText();
        if (mTimeLimit != sf::Time::Zero)
        {
            mShapeTop.setSize(sf::Vector2f((1 - (getRemainingTime() / mTimeLimit)) * getSize().x, getSize().y));
        }
    }
}

void Timer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mVisible)
    {
        states.transform *= getTransform();
        target.draw(mShape,states);
        target.draw(mShapeTop,states);
        target.draw(mText,states);
    }
}

void Timer::reset(sf::Time timeLimit)
{
    mTimeLimit = timeLimit;
    thor::Timer::reset(timeLimit);
}

void Timer::restart(sf::Time timeLimit)
{
    mTimeLimit = timeLimit;
    thor::Timer::restart(timeLimit);
}

sf::RectangleShape& Timer::getShapeTop()
{
    return mShapeTop;
}

}
