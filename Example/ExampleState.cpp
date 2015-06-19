#include "ExampleState.hpp"
#include "../Source/Application.hpp"

ExampleState::ExampleState(ah::StateManager& manager)
: State(manager)
{
    mType = ExampleState::getID();
    mSprite.setTexture(getApplication().getTexture("cb"));
	mExploded = false;
    //getApplication().setAction("quit",thor::Action(sf::Event::Closed));
	getApplication() << ah::Log::Info << "launched";
}

std::string ExampleState::getID()
{
    return "ExampleState";
}

bool ExampleState::handleEvent(sf::Event const& event)
{
    /*
    Events can be handled via the thor::ActionMap in the Application
    But an interface is still provided if you prefer not using thor::ActionMap
    */

    return true;
}

bool ExampleState::update(sf::Time dt)
{
    if (mSprite.getPosition().x >= 800.f)
    {
        getApplication().close();
    }

	mSprite.move(75.f * dt.asSeconds(), 20.f * dt.asSeconds());
    return true;
}

void ExampleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
