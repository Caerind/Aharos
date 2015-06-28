#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Aharos/State.hpp"

class MenuState : public ah::State
{
    public:
        MenuState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();

        void ToGame();
        void ToEnd();

};

#endif // MENUSTATE_HPP
