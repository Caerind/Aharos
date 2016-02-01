#ifndef SES_PLAYERINPUTSYSTEM_HPP
#define SES_PLAYERINPUTSYSTEM_HPP

#include "../System.hpp"
#include "../../Helper/ActionTarget.hpp"
#include "../../Application/Application.hpp"
#include "../Components.hpp"

namespace ses
{

class PlayerInputSystem : public System, public lp::ActionTarget
{
    public:
        PlayerInputSystem();

        void setFunction(std::string const& id, std::function<void()> f);
        void removeFunction(std::string const& id);

        void update();

    protected:
        std::map<std::string,std::function<void()>> mFunctions;
};

} // namespace ses

#endif // SES_PLAYERINPUTSYSTEM_HPP
