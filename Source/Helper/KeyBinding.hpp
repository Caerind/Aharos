#ifndef LP_KEYBINDING_HPP
#define LP_KEYBINDING_HPP

#include <cassert>
#include <string>
#include <fstream>
#include <Thor/Input.hpp>
#include "ActionTarget.hpp"
#include "pugixml.hpp"

namespace lp
{

class KeyBinding
{
    public:
        KeyBinding(ActionMapPtr map = nullptr);
        ~KeyBinding();

        enum ActionType
        {
            Hold = 0,
            PressOnce = 1,
            ReleaseOnce = 2,
        };

        void setKey(std::string const& id, sf::Keyboard::Key key);
        void setType(std::string const& id, KeyBinding::ActionType type);
        sf::Keyboard::Key getKey(std::string const& id);
        KeyBinding::ActionType getType(std::string const& id);

        thor::Action getActionFromId(std::string const& id);

        ActionMapPtr getMap();

        bool load();
        void save();

    protected:
        ActionMapPtr mActionMap;
        std::map<std::string,std::pair<sf::Keyboard::Key,KeyBinding::ActionType>> mKeys;
};

} // namespace lp

#endif // LP_KEYBINDING_HPP
