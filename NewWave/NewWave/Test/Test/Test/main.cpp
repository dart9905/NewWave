
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include <iostream>

int main(int argc,char **argv)
{
    sf::RenderWindow window(sf::VideoMode(800,800),"Game");
    
    // Игровой Цикл
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                    // Событие мыши Mouse Event
                case sf::Event::MouseEntered:
                    std::cout << "mouse Entered" << std::endl;
                    break;
                    
                case sf::Event::MouseLeft:
                    std::cout << "mouse not Entered" << std::endl;
                    break;
                    
                case sf::Event::MouseMoved:
                    // std::cout << “mouse Coord x: " << event.mouseMove.x << " y: " << event.mouseMove.y << std::endl;
                    break;
                    
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button==sf::Mouse::Left)
                    {
                        std::cout << "mouse Left button Press" << std::endl;
                        std::cout << "mouse Button Press coord x: " << event.mouseButton.x << " y: " << event.mouseButton.y << std::endl;
                    }
                    else if(event.mouseButton.button==sf::Mouse::Right)
                        std::cout << "mouse Right button Press" << std::endl;
                    else if(event.mouseButton.button==sf::Mouse::Middle)
                        std::cout << "mouse Middle button Press" << std::endl;
                    
                    break;
                    
                    // Вращение средней кнопки – колеса мыши
                case sf::Event::MouseWheelMoved:
                    // delta – значение в какую сторону вращаем колесо ( 1 up , -1 down )
                    std::cout << "mouse wheel delta: " << event.mouseWheel.delta << std::endl;
                    if(event.mouseWheel.delta==1)
                        std::cout << "up wheel mouse!" << std::endl;
                    else if(event.mouseWheel.delta==-1)
                        std::cout << "down wheel mouse!" << std::endl;
                    
                    break;
                    
            }
        }
        
        // Обновление
        
        window.clear(sf::Color::Yellow);
        
        window.display();
        
    }
    return 0;
}
