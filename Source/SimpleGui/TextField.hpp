#ifndef SG_TEXTFIELD_HPP
#define SG_TEXTFIELD_HPP

#include "Box.hpp"

namespace sg
{

class TextField : public Box
{
    public:
        typedef std::shared_ptr<TextField> Ptr;

        TextField();
        TextField(Widget* parent);

        virtual void update(sf::Event const& event, sf::Vector2f mousePosition);

        void setString(std::string const& string);

        std::string getString();

        void setStringMaxSize(unsigned int maxSize);

        void gainFocus();
        void lostFocus();

    protected:
        bool mFocused;

        unsigned int mMaxSize;
};

}

#endif // SG_TEXTFIELD_HPP
