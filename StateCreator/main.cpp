#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

using namespace std;

struct my_toupper
{
    char operator()(char c) const
    {
        return toupper(static_cast<unsigned char>(c));
    }
};

void write(ofstream& o, string const& str)
{
    o << str << endl;
    cout << str << endl;
}

int main()
{
    cout << "Enter the name of the State you want to create : " << endl;
    string name;
    cin >> name;
    name += "State";
    string nameMaj = name;
    transform(nameMaj.begin(), nameMaj.end(), nameMaj.begin(), my_toupper());
    cout << nameMaj;

    ofstream header(name + ".hpp");
    if (header)
    {
        write(header,"#ifndef " + nameMaj + "_HPP");
        write(header,"#define " + nameMaj + "_HPP");
        write(header,"");
        write(header,"#include \"../Aharos/State.hpp\"");
        write(header,"");
        write(header,"class " + name + " : public ah::State");
        write(header,"{");
        write(header,"    public:");
        write(header,"        " + name + "(ah::StateManager& manager);");
        write(header,"");
        write(header,"        static std::string getID();");
        write(header,"");
        write(header,"        bool handleEvent(sf::Event const& event);");
        write(header,"        bool update(sf::Time dt);");
        write(header,"        void draw(sf::RenderTarget& target, sf::RenderStates states) const;");
		write(header,"");
        write(header,"        void onActivate();");
        write(header,"        void onDeactivate();");
        write(header,"};");
        write(header,"");
        write(header,"#endif // " + nameMaj + "_HPP");
        header.close();
    }

    ofstream impl(name + ".cpp");
    if (impl)
    {
        write(impl,"#include \"" + name + ".hpp\"");
        write(impl,"#include \"App.hpp\"");
        write(impl,"");
        write(impl,name + "::" + name + "(ah::StateManager& manager) : ah::State(manager)");
        write(impl,"{");
        write(impl,"    mType = " + name + "::getID();");
        write(impl,"}");
        write(impl,"");
        write(impl,"std::string " + name + "::getID()");
        write(impl,"{");
        write(impl,"    return \"" + name + "\";");
        write(impl,"}");
        write(impl,"");
        write(impl,"bool " + name + "::handleEvent(sf::Event const& event)");
        write(impl,"{");
        write(impl,"    return true;");
        write(impl,"}");
        write(impl,"");
        write(impl,"bool " + name + "::update(sf::Time dt)");
        write(impl,"{");
        write(impl,"    return true;");
        write(impl,"}");
        write(impl,"");
        write(impl,"void " + name + "::draw(sf::RenderTarget& target, sf::RenderStates states) const");
        write(impl,"{");
        write(impl,"    states.transform *= getTransform();");
        write(impl,"}");
		write(impl,"void " + name + "::onActivate()");
        write(impl,"{");
        write(impl,"");
        write(impl,"}");
		write(impl,"void " + name + "::onDeactivate()");
        write(impl,"{");
        write(impl,"");
        write(impl,"}");
        impl.close();
    }

    return 0;
}
