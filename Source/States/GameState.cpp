#include "GameState.hpp"
#include <iostream>
#include "../Entities/Systems.hpp"
#include "../Entities/Components.hpp"
#include <Box2D/Box2D.h>

GameState::GameState(ah::StateManager& manager)
: ah::State(manager,lp::type<GameState>())
, mPressed(false)
{
    // Register Your Components
    ses::registerComponents();

    // Load Your Systems
    mWorld.addSystem<ses::SpriteSystem>();
    mWorld.addSystem<ses::AudioSystem>();
    ses::PlayerInputSystem& is = mWorld.addSystem<ses::PlayerInputSystem>();
    /*is.setFunction("rotate",[&](){
        if (mWorld.isInstantiated("player0"))
        {
            b2Body* b = mWorld.getEntity("player0")->getBody();
            if (b != nullptr)
            {
                float desiredVel = -5 * is.isActive("left") + 5 * is.isActive("right");
                b->ApplyAngularImpulse((desiredVel - b->GetAngularVelocity()) * b->GetMass(),true);
            }
        }
    });*/
    is.setFunction("move",[&]()
    {
        if (mWorld.isInstantiated("player0"))
        {
            b2Body* b = mWorld.getEntity("player0")->getBody();
            if (b != nullptr)
            {
                b2Vec2 impulse, vel = b->GetLinearVelocity();
                if (is.isActive("left") || is.isActive("right"))
                {
                    impulse.x = (-10 * is.isActive("left") + 10 * is.isActive("right")) - vel.x;
                }
                if (is.isActive("up") || is.isActive("down"))
                {
                    impulse.y = (-10 * is.isActive("up") + 10 * is.isActive("down")) - vel.y;
                }
                impulse *= b->GetMass();
                b->ApplyLinearImpulse(impulse, b->GetWorldCenter(), true);
            }
        }
    });
    is.setAction("cLeft",thor::Action(sf::Mouse::Left,thor::Action::PressOnce));
    is.setFunction("spawn",[&]()
    {
        if (is.isActive("cLeft"))
        {
            sf::View view = ah::Application::getWindow().getDefaultView();
            if (mWorld.isInstantiated("player0"))
            {
                ses::Entity::Ptr e = mWorld.getEntity("player0");
                if (e != nullptr)
                {
                    if (e->hasComponent<ses::CameraComponent>())
                    {
                        view = e->getComponent<ses::CameraComponent>().getView();
                    }
                }
            }
            sf::Vector2f mPos = ah::Application::getWindow().getMousePositionView(view);
            ses::Entity::Ptr e = mWorld.execPrefab("test");
            if (e != nullptr)
            {
                e->setPosition(mPos);
            }
        }
    });
    is.setAction("cRight",thor::Action(sf::Mouse::Right,thor::Action::PressOnce));
    is.setFunction("teleport",[&]()
    {
        if (is.isActive("cRight"))
        {
            sf::View view = ah::Application::getWindow().getDefaultView();
            if (mWorld.isInstantiated("player0"))
            {
                ses::Entity::Ptr e = mWorld.getEntity("player0");
                if (e != nullptr)
                {
                    if (e->hasComponent<ses::CameraComponent>())
                    {
                        view = e->getComponent<ses::CameraComponent>().getView();
                    }
                    sf::Vector2f mPos = ah::Application::getWindow().getMousePositionView(view);
                    e->setPosition(mPos);
                }
            }
        }
    });

    // Load Your Prefabs
    mWorld.loadPrefab("prefabs.xml");

    if (true) // You can replace it with : if (!mWorld.load("test.xml"))
    {
        // World Properties
        mWorld.setGravity(b2Vec2(0,10));

        // Create Your Entities
        ses::Entity::Ptr e = mWorld.execPrefab("player");
        ses::Entity::Ptr e1 = mWorld.execPrefab("test");
        ses::Entity::Ptr e2 = mWorld.execPrefab("layer");
        if (e2 != nullptr)
        {
            if (e2->hasComponent<ses::TileLayerComponent>())
            {
                ses::TileLayerComponent& t = e2->getComponent<ses::TileLayerComponent>();
                // TODO : Find how to handle HAS COLLISIONS
            }
        }

        // Save The Initial Creation
        mWorld.save("test.xml");
    }
}

GameState::~GameState()
{
}

bool GameState::handleEvent(sf::Event const& event)
{
    mWorld.getSystem<ses::PlayerInputSystem>().handleEvent(event);

    /*
    sf::Vector2f mPos = ah::Application::getWindow().getMousePosition();
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        ses::Entity::Ptr e = mWorld.getEntity("player1");
        if (event.type == sf::Event::MouseMoved && mPressed)
        {
            sf::Vector2f d1, d2, s;
            d1 = mPosPressed - e->getPosition();
            d2 = mPos - e->getPosition();
            s = sf::Vector2f(d2.x / d1.x, d2.y / d1.y);
            e->getComponent<ses::SpriteComponent>().setScale(s);
            std::cout << s.x << " " << s.y << std::endl;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && e->getComponent<ses::SpriteComponent>().contains(mPos-e->getPosition()))
        {
            mPressed = true;
            mPosPressed = mPos;
        }
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            mPressed = false;
        }
    }
    */
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.getSystem<ses::PlayerInputSystem>().update();

    ah::Application::getWindow().setDebugInfo("entities",std::to_string(mWorld.getEntitiesCount()));

    mWorld.update(dt.asSeconds());
    return true;
}

void GameState::render(sf::RenderTarget& target, sf::RenderStates states)
{
    states.transform *= getTransform();

    sf::View view = ah::Application::getWindow().getDefaultView();
    if (mWorld.isInstantiated("player0"))
    {
        ses::Entity::Ptr e = mWorld.getEntity("player0");
        if (e != nullptr)
        {
            if (e->hasComponent<ses::CameraComponent>())
            {
                view = e->getComponent<ses::CameraComponent>().getView();
            }
        }
    }
    target.setView(view);

    mWorld.render(target);
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        mWorld.getSystem<ses::SpriteSystem>().render(target);
}

void GameState::onActivate()
{
    ah::Application::getWindow().setBackgroundTexture(&ah::Application::getResources().getTexture("bg"));
}

void GameState::onDeactivate()
{
}
