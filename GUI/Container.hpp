#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Widget.hpp"

#include <SFML/Window/Event.hpp>

class Container : public Widget
{
    public:
        Container();

        void handleEvent(sf::Event const& event);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        template <typename T>
        std::shared_ptr<T> create();

    protected:
        std::vector<Widget::Ptr> mWidgets;
};

template <typename T>
std::shared_ptr<T> Container::create()
{
    std::shared_ptr<T> w = std::make_shared<T>();
    mWidgets.push_back(w);
    return w;
}

#endif // CONTAINER_HPP
