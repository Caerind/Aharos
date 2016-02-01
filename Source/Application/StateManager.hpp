#ifndef AH_STATEMANAGER_HPP
#define AH_STATEMANAGER_HPP

#include <functional>
#include <map>
#include <vector>

#include "../Helper/TypeToString.hpp"

#include "State.hpp"

namespace ah
{

class StateManager
{
    public:
		StateManager();

		template<typename T>
		void registerState();

        void handleEvent(sf::Event const& event);
		void update(sf::Time dt);
		void render(sf::RenderTarget& target, sf::RenderStates states);

        template <typename T>
		void pushState();
		void pushState(std::string const& id);
		void popState();
		void clearStates();

		bool empty() const;
		std::size_t size() const;
		std::string getActiveStateType() const;
		std::string getLastActiveStateType() const;

	protected:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct PendingChange
		{
			explicit PendingChange(Action action, std::string const& id = "");
			Action action;
			std::string id;
		};

		void applyPendingChanges();
		State::Ptr createState(std::string const& id);

	protected:
        std::string mLastActiveStateType;

		std::vector<State::Ptr> mStates;
		std::vector<PendingChange> mPendingList;

		std::map<std::string, std::function<State::Ptr()>> mFactories;
};

template<typename T>
void StateManager::registerState()
{
    std::string t = lp::type<T>();
	mFactories[t] = [this] ()
	{
		return State::Ptr(new T(*this));
	};
}

template <typename T>
void StateManager::pushState()
{
	mPendingList.push_back(PendingChange(Push, lp::type<T>()));
}

} // namespace ah

#endif // AH_STATEMANAGER_HPP
