#ifndef SG_CHECKBOX_HPP
#define SG_CHECKBOX_HPP

#include "Box.hpp"

namespace sg
{

class CheckBox : public Box
{
    public:
        typedef std::shared_ptr<CheckBox> Ptr;

        CheckBox();
        CheckBox(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);
};

}

#endif // SG_CHECKBOX_HPP
