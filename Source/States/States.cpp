#include "States.hpp"

void registerStates()
{
    ah::Application::getStates().registerState<IntroState>();
    ah::Application::getStates().registerState<MenuState>();
    ah::Application::getStates().registerState<GameState>();
    ah::Application::getStates().registerState<SettingsState>();
}
