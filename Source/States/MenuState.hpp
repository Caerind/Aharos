#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../Application/Application.hpp"
#include "../Application/State.hpp"
#include "States.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class MenuState : public ah::State
{
    public:
        MenuState(ah::StateManager& manager);
        virtual ~MenuState();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

        void onActivate();
        void onDeactivate();

    private:
        sfg::SFGUI mSfgui;
        sfg::Desktop mDesktop;

        sf::Text mTitleText;
        sf::Text mTitleShadow;
};

#endif // MENUSTATE_HPP
