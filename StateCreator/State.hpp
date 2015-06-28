#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cctype>
#include <algorithm>

struct my_toupper
{
    char operator()(char c) const
    {
        return toupper(static_cast<unsigned char>(c));
    }
};

class State : public sf::Drawable, public sf::Transformable
{
    public:
        State(std::string const& name, sf::Font& font, sf::Vector2f const& position, int special = 0);

        bool contains(sf::Vector2f const& point) const;

        std::string getName() const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int getSpecial() const;

        void addGoTo(std::string const& name);
        void goToEnd(bool gotoEnd);


        static void write(std::ofstream& o, std::string const& str);

        void save(std::string const& path);

    private:
        sf::RectangleShape mShape;
        sf::Text mText;

        std::string mName;

        int mSpecial;

        std::vector<std::string> mGotos;
        bool mGotoEnd;
};

#endif // STATE_HPP
