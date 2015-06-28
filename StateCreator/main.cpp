#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "State.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Aharos - StateCreator");
    sf::View view = window.getView();

    sf::Font font;
    if (!font.loadFromFile("coolveticca.ttf"))
        return 0;

    std::vector<State> states;
    states.push_back(State("EntryPoint",font,sf::Vector2f(),1));
    states.push_back(State("EndPoint",font,sf::Vector2f(600,0),2));

    std::vector<sf::VertexArray> lines;

    int idSelectedMove;
    int idSelectedGoTo;
    sf::Vector2f deltaPosition;
    sf::Vector2f gotoPos1;

    bool save = false;
    bool captured = false;

    sf::Image capture;

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Vector2f mPos = window.mapPixelToCoords(sf::Mouse::getPosition(window),view);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta < 1)
                {
                    view.zoom(1.2f);
                }
                else
                {
                    view.zoom(0.8f);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                idSelectedMove = -1;
                for (unsigned int i = 0; i < states.size(); i++)
                {
                    if (states[i].contains(mPos))
                    {
                        idSelectedMove = i;
                        deltaPosition = mPos - states[i].getPosition();
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                idSelectedMove = -1;
                deltaPosition = sf::Vector2f();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle)
            {
                std::string name;
                std::cout << "Enter the name of the state you want to create : " << std::endl;
                std::cin >> name;
                std::cout << std::endl << std::endl;
                states.push_back(State(name,font,view.getCenter()));
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                idSelectedGoTo = -1;
                for (unsigned int i = 0; i < states.size(); i++)
                {
                    if (states[i].contains(mPos))
                    {
                        idSelectedGoTo = i;
                        gotoPos1 = mPos;
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
            {
                if (idSelectedGoTo >= 0 && idSelectedGoTo < (int)states.size())
                {
                    for (unsigned int i = 0; i < states.size(); i++)
                    {
                        if (states[i].contains(mPos) && i != idSelectedGoTo)
                        {
                            bool passed = false;

                            if (states[idSelectedGoTo].getSpecial() == 0 && states[i].getSpecial() == 0)
                            {
                                states[idSelectedGoTo].addGoTo(states[i].getName());
                                passed = true;
                            }
                            if (states[idSelectedGoTo].getSpecial() == 0 && states[i].getSpecial() == 2)
                            {
                                states[idSelectedGoTo].goToEnd(true);
                                passed = true;
                            }
                            if (states[idSelectedGoTo].getSpecial() == 1 && states[i].getSpecial() == 0)
                            {
                                passed = true;
                            }

                            if (passed)
                            {
                                sf::VertexArray line(sf::Lines,2);
                                line[0].position = gotoPos1;
                                line[1].position = mPos;
                                lines.push_back(line);
                            }
                        }
                    }
                }
                idSelectedGoTo = -1;
                gotoPos1 = sf::Vector2f();
            }


            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
            {
                window.close();
                save = true;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1)
            {
                capture = window.capture();
                captured = true;
                std::cout << std::endl << "Screenshot taken" << std::endl;
            }
        }

        if (idSelectedMove >= 0 && idSelectedMove < (int)states.size())
        {
            states[idSelectedMove].setPosition(mPos - deltaPosition);
        }

        sf::Vector2f mvt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            mvt.y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            mvt.x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            mvt.y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            mvt.x++;
        view.move(mvt * clock.restart().asSeconds() * 400.f);

        window.clear();
        window.setView(view);
        for (unsigned int i = 0; i < states.size(); i++)
        {
            window.draw(states[i]);
        }
        for (unsigned int i = 0; i < lines.size(); i++)
        {
            window.draw(lines[i]);
        }
        window.setView(window.getDefaultView());

        window.display();
    }

    if (save)
    {
        std::string temp;
        getline(std::cin,temp);
        std::cout << std::endl << "Enter the path where you want the files to be created : " << std::endl;
        std::string path;
        getline(std::cin,path);
        if (path.back() != '\'')
        {
            path += "\\";
        }

        for (unsigned int i = 0; i < states.size(); i++)
        {
            states[i].save(path);
        }

        if (captured)
        {
            if (capture.saveToFile(path + "capture.png"))
            {
                std::cout << " --- Capture Saved ---" << std::endl;
            }
        }

        getchar();
    }

    return 0;
}
