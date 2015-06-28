#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "../Aharos/State.hpp"

class IntroState : public ah::State
{
    public:
        IntroState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();

        void ToMenu();

};

#endif // INTROSTATE_HPP
