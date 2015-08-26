#ifndef SG_CONTAINER_HPP
#define SG_CONTAINER_HPP

#include <vector>

#include "Widget.hpp"
#include "Timer.hpp"

namespace sg
{

class Container : public sf::Drawable
{
    public:
        Container();

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void update();

        template <typename T>
        std::shared_ptr<T> create();

        bool isVisible() const;
        void setVisible(bool visible);

    protected:

    protected:
        std::vector<Widget::Ptr> mWidgets;
        std::vector<Widget::Ptr> mDynamics;
        bool mVisible;
};

template<class T>
struct TypeIsDynamic
{
    static const bool value = false;
};

template<>
struct TypeIsDynamic<sg::Timer>
{
    static const bool value = true;
};

template <typename T>
std::shared_ptr<T> Container::create()
{
    std::shared_ptr<T> w = std::make_shared<T>();
    mWidgets.push_back(w);
    if (TypeIsDynamic<T>::value)
    {
        mDynamics.push_back(w);
    }
    return w;
}

}

#endif // SG_CONTAINER_HPP
