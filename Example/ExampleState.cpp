#include "ExampleState.hpp"
#include "../Source/Application.hpp"

ExampleState::ExampleState(ah::StateManager& manager)
: State(manager)
{
    mType = ExampleState::getID();
    mSprite.setTexture(getApplication().getTexture("Example/cb.bmp"));
	mExploded = false;
    getApplication().setAction("quit",thor::Action(sf::Event::Closed));
	getApplication().playMusic("Example/jingleAtmog.wav");
	getApplication() << ah::Log::Info << getApplication().getLang("launched");
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
    if (getApplication().isActionActive("quit") || mSprite.getPosition().x >= 800.f)
    {
        getApplication().close();
    }

	mSprite.move(getApplication().getData<float>("speed-x") * dt.asSeconds(), 20.f * dt.asSeconds());

	if (mSprite.getPosition().x >= 300.f && !mExploded)
    {
        if (!getApplication().playSound(getApplication().getData<std::string>("sound-name")))
        {
            getApplication() << ah::Log::Error << "Error with sound";
        }
        mExploded = true;
    }

    return true;
}

void ExampleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite,states);
}
