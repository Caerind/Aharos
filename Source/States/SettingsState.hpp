#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "../Application/Application.hpp"
#include "../Application/State.hpp"
#include "States.hpp"

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

class SettingsState : public ah::State
{
    public:
        SettingsState(ah::StateManager& manager);
        virtual ~SettingsState();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void render(sf::RenderTarget& target, sf::RenderStates states);

        void onActivate();
        void onDeactivate();

    private:
        sfg::SFGUI mSfgui;
        sfg::Desktop mDesktop;

        sfg::Scale::Ptr mGlobalS;
        sfg::Scale::Ptr mMusicS;
        sfg::Scale::Ptr mSoundS;
        sfg::Label::Ptr mGlobalL;
        sfg::Label::Ptr mMusicL;
        sfg::Label::Ptr mSoundL;
        sfg::ComboBox::Ptr mRes;
        sfg::Window::Ptr mWindow;
        sfg::CheckButton::Ptr mVerticalSync;
        sfg::CheckButton::Ptr mFullscreen;

        int mKeySelected;
        sfg::Button::Ptr mKeyRight;
        sfg::Button::Ptr mKeyLeft;
};

#endif // SETTINGSSTATE_HPP
