#include "State.hpp"

State::State(std::string const& name, sf::Font& font, sf::Vector2f const& position, int special)
{
    setPosition(position);
    mName = name;
    mSpecial = special;
    mGotoEnd = false;

    mText.setFont(font);
    mText.setCharacterSize(30);
    mText.setColor(sf::Color::White);
    mText.setString(name);

    mShape.setSize(sf::Vector2f(30.f + mText.getGlobalBounds().width + 30.f, 15.f + mText.getGlobalBounds().height + 15.f));
    mShape.setOutlineThickness(1.2f);
    if (mSpecial == 0)
    {
        mShape.setFillColor(sf::Color::Red);
        mShape.setOutlineColor(sf::Color::Blue);
    }
    if (mSpecial == 1)
    {
        mShape.setFillColor(sf::Color::Green);
        mShape.setOutlineColor(sf::Color::Red);
    }
    if (mSpecial == 2)
    {
        mShape.setFillColor(sf::Color::Blue);
        mShape.setOutlineColor(sf::Color::Green);
    }

    mText.setOrigin(mText.getGlobalBounds().width/2,mText.getGlobalBounds().height/2);
    mText.setPosition(mShape.getSize().x * 0.5f,15.f);

    setPosition(position);
}

bool State::contains(sf::Vector2f const& point) const
{
    return sf::FloatRect(getPosition(),mShape.getSize()).contains(point);
}

std::string State::getName() const
{
    return mName;
}

void State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mShape,states);
    target.draw(mText,states);
}

int State::getSpecial() const
{
    return mSpecial;
}

void State::addGoTo(std::string const& name)
{
    mGotos.push_back(name);
}

void State::goToEnd(bool gotoEnd)
{
    mGotoEnd = true;
}

void State::write(std::ofstream& o, std::string const& str)
{
    o << str << std::endl;
    std::cout << str << std::endl;
}

void State::save(std::string const& path)
{
    if (mSpecial != 0)
        return;

    if (mName.find("State") == std::string::npos)
    {
        mName += "State";
    }
    std::string nameMaj = mName;
    std::transform(nameMaj.begin(), nameMaj.end(), nameMaj.begin(), my_toupper());

    std::cout << std::endl << std::endl;
    std::cout << " --- Writing Header ---" << std::endl;
    std::cout << std::endl << std::endl;

    std::ofstream header(path + mName + ".hpp");
    if (header)
    {
        write(header,"#ifndef " + nameMaj + "_HPP");
        write(header,"#define " + nameMaj + "_HPP");
        write(header,"");
        write(header,"#include \"../Aharos/State.hpp\"");
        write(header,"");
        write(header,"class " + mName + " : public ah::State");
        write(header,"{");
        write(header,"    public:");
        write(header,"        " + mName + "(ah::StateManager& manager);");
        write(header,"");
        write(header,"        static std::string getID();");
        write(header,"");
        write(header,"        bool handleEvent(sf::Event const& event);");
        write(header,"        bool update(sf::Time dt);");
        write(header,"        void draw(sf::RenderTarget& target, sf::RenderStates states) const;");
		write(header,"");
        write(header,"        void onActivate();");
        write(header,"        void onDeactivate();");
        if (mGotos.size() > 0 || mGotoEnd)
        {
            write(header,"");
        }
        for (unsigned int i = 0; i < mGotos.size(); i++)
        {
            write(header,"        void To" + mGotos[i] + "();");
        }
        if (mGotoEnd)
        {
            write(header,"        void ToEnd();");
        }
        write(header,"};");
        write(header,"");
        write(header,"#endif // " + nameMaj + "_HPP");
        header.close();
    }

    std::cout << std::endl << std::endl;
    std::cout << " --- Header Done ---" << std::endl;
    std::cout << std::endl << std::endl;
    std::cout << " --- Writing Implementation ---" << std::endl;
    std::cout << std::endl << std::endl;

    std::ofstream impl(path + mName + ".cpp");
    if (impl)
    {
        write(impl,"#include \"" + mName + ".hpp\"");
        write(impl,"");
        write(impl,mName + "::" + mName + "(ah::StateManager& manager) : ah::State(manager)");
        write(impl,"{");
        write(impl,"    mType = " + mName + "::getID();");
        write(impl,"}");
        write(impl,"");
        write(impl,"std::string " + mName + "::getID()");
        write(impl,"{");
        write(impl,"    return \"" + mName + "\";");
        write(impl,"}");
        write(impl,"");
        write(impl,"bool " + mName + "::handleEvent(sf::Event const& event)");
        write(impl,"{");
        write(impl,"    return true;");
        write(impl,"}");
        write(impl,"");
        write(impl,"bool " + mName + "::update(sf::Time dt)");
        write(impl,"{");
        write(impl,"    return true;");
        write(impl,"}");
        write(impl,"");
        write(impl,"void " + mName + "::draw(sf::RenderTarget& target, sf::RenderStates states) const");
        write(impl,"{");
        write(impl,"    states.transform *= getTransform();");
        write(impl,"}");
        write(impl,"");
		write(impl,"void " + mName + "::onActivate()");
        write(impl,"{");
        write(impl,"");
        write(impl,"}");
        write(impl,"");
		write(impl,"void " + mName + "::onDeactivate()");
        write(impl,"{");
        write(impl,"");
        write(impl,"}");
        if (mGotos.size() > 0)
        {
            write(impl,"");
        }
        for (unsigned int i = 0; i < mGotos.size(); i++)
        {
            write(impl,"void " + mName + "::To" + mGotos[i] + "()");
            write(impl,"{");
            write(impl,"");
            write(impl,"}");
            if (i < mGotos.size()-1 || (mGotoEnd && i == mGotos.size()-1))
            {
                write(impl,"");
            }
        }
        if (mGotoEnd)
        {
            write(impl,"void " + mName + "::ToEnd()");
            write(impl,"{");
            write(impl,"");
            write(impl,"}");
        }
        impl.close();
    }

    std::cout << std::endl << std::endl;
    std::cout << " --- Implementation Done ---" << std::endl;
    std::cout << std::endl << std::endl;
}
