#ifndef AH_ACTIONTARGET_HPP
#define AH_ACTIONTARGET_HPP

#include <Thor/Input/ActionMap.hpp>
#include <Thor/Input/Connection.hpp>
#include <Thor/Input/EventSystem.hpp>

#include <functional>
#include <utility>
#include <map>

namespace ah
{

class ActionTarget
{
	public:
	    typedef const thor::ActionContext<std::string>& Context;
	    typedef std::function<void(Context context)> Callback;
	    typedef std::shared_ptr<thor::ActionMap<std::string>> ActionMapPtr;

		ActionTarget(ActionMapPtr map = nullptr);

		void handleEvent(sf::Event const& event);
		void update();

		void setAction(std::string const& key, thor::Action const& action);
		const thor::Action& getAction(std::string const& key);
		bool isActive(std::string const& key);

		void bind(std::string const& key, Callback const& callback);
		void unbind(std::string const& key);

	protected:
	    ActionMapPtr mMap;
	    thor::ActionMap<std::string>::CallbackSystem mSystem;
	    std::map<std::string,thor::Connection> mConnections;
};

} // namespace ah

#endif // AH_ACTIONTARGET_HPP
