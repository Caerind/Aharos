#ifndef SG_WINDOW_HPP
#define SG_WINDOW_HPP

#include "Box.hpp"

namespace sg
{

class Window : public Box
{
    public:
        typedef std::shared_ptr<Window> Ptr;

        Window();
        Window(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        template <typename T>
        std::shared_ptr<T> create();

    protected:
        virtual void updateText();

    protected:
        std::vector<Widget::Ptr> mWidgets;
};

template <typename T>
std::shared_ptr<T> Window::create()
{
    std::shared_ptr<T> w = std::make_shared<T>(this);
    mWidgets.push_back(w);
    return w;
}

}

#endif // SG_WINDOW_HPP
