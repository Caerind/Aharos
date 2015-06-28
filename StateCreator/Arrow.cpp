#include "Arrow.hpp"

Arrow::Arrow(State* state1, sf::Vector2f d1, State* state2, sf::Vector2f d2)
{
    mState1 = state1;
    mDelta1 = d1;
    mState2 = state2;
    mDelta2 = d2;

    mLine.setSize(sf::Vector2f(0.f,2.f));
    mLine.setOrigin(sf::Vector2f(0.f,1.f));
    mLine.setFillColor(sf::Color::White);

    mLeft.setSize(sf::Vector2f(10.f,2.f));
    mLeft.setOrigin(sf::Vector2f(0.f,1.f));
    mLeft.setFillColor(sf::Color::White);

    mRight.setSize(sf::Vector2f(10.f,2.f));
    mRight.setOrigin(sf::Vector2f(0.f,1.f));
    mRight.setFillColor(sf::Color::White);
}

void Arrow::update()
{
    if (mState1 == nullptr || mState2 == nullptr)
    {
        return;
    }

    sf::Vector2f pos1 = mState1->getPosition() + mDelta1;
    sf::Vector2f pos2 = mState2->getPosition() + mDelta2;
    sf::Vector2f diff = pos2 - pos1;

    float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float angle = 180.f / 3.14152f * std::atan2(diff.y, diff.x);

    mLine.setSize(sf::Vector2f(length, mLine.getSize().y));
    mLine.setRotation(angle);
    mLine.setPosition(pos1);

    mLeft.setPosition(pos2);
    mLeft.setRotation(angle + 180 - 15);

    mRight.setPosition(pos2);
    mRight.setRotation(angle + 180 + 15);
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mLine);
    target.draw(mLeft);
    target.draw(mRight);
}
