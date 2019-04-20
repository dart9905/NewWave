/*!
 \file MAIN
 \authors LordDifine -- Khromov Alexey
 \version A1.3mac
 \date 30.03.2019
 \bug no
 
 */
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

//#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <time.h>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"


//Connecting our libraries
//#include "GraphFile.hpp"
//#include "Management.hpp"
#include "Event.hpp"
#include "Test.hpp"

//      =============================================
//      ==                                         ==
//      ==   ==       ==   =====   ==   ==    ==   ==
//      ==   ===     ===   ==  =   ==   ===   ==   ==
//      ==   == == == ==   =====   ==   == == ==   ==
//      ==   ==  ===  ==   ==  =   ==   ==   ===   ==
//      ==                                         ==
//      =============================================


int main(int, char const**)
{
    
    //
    //              Create the main window
    //
    sf::ContextSettings settings;
    settings.depthBits = 32;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    sf::RenderWindow window(sf::VideoMode(window_width / 2, window_height / 2), "NewWave", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png"))
    {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //
    SkinBox_t box;
    SkinBox_t arrayBox [1] = {box};
    MakeTextures (arrayBox);
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg"))
    {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    sf::Clock clock;
    sf::View view;
    view.reset(sf::FloatRect(0, 0, window_width, window_height));
    
    mouse_t Mouse(-45, -45, 200);
    Bar Bar(500, window_height / 2, 0, 0, window);
    
    
    

    // Start the game loop
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        window.clear(sf::Color::Black);
        
        //float time = clock.getElapsedTime().asMilliseconds() / 2;
        
        // Process events
        EVENT(window, Mouse, Bar, view);
        
        // Draw the sprite
        /*
        //sprite.setScale((window.getSize()).x / (texture.getSize()).x, (window.getSize()).y / (texture.getSize()).y);
        window.pushGLStates();
        window.draw(sprite);
        window.popGLStates();
        //*/
        if ((window.getSize()).x >= 2 * Bar.getwidth())
        {
            glViewport ( (window.getSize()).x / 2 - window_width / 2 + (int)(Bar.getwidth() / 2), (window.getSize()).y / 2 - window_height / 2 , window_width, window_height);
        } else {
            glViewport ( (window.getSize()).x / 2 - window_width / 2, (window.getSize()).y / 2 - window_height / 2 , window_width, window_height);
        }
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(Mouse.x_, Mouse.y_, Mouse.z_, 0, 0, 0, 0, 1, 0);
        
        
        linepole();
        xyz();
        
        drawhouse(arrayBox, 5, 1, 3, 0);
        drawhouse(arrayBox, -1, 1, 3, 30);
        drawhouse(arrayBox, -3, 1, -5, 0);
        
        if ((window.getSize()).x >= 2 * Bar.getwidth())
        {
            Bar.draw();
        }
        
        //*/
        // Update the window
        window.display();
    }
    
    system("say \"мяу\"");
    return EXIT_SUCCESS;
}
