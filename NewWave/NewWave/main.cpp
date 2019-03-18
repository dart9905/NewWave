/*!
 \file
 \authors LordDifine -- Khromov Alexey
 \version A1.0mac
 \date 18.03.2019
 \bug inadequate work with background scale
 
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
#include "GraphFile.hpp"

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
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "NewWave", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //
    SkinBox_t box;
    SkinBox_t arrayBox [1] = {box};
    MakeTextures (arrayBox);
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        float time = clock.getElapsedTime().asMilliseconds() / 2;
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        
        // Draw the sprite
        
        sprite.setScale((window.getSize()).x / (texture.getSize()).x, (window.getSize()).y / (texture.getSize()).y);
        window.pushGLStates();
        window.draw(sprite);
        window.popGLStates();
        
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //*
        // Working with the camera
        glTranslatef(0, 0, -100);
        glRotatef(time, 50, 50, 0);
        // draw box
        createBox(arrayBox [0], GLOBsize);
        glRotatef(-time, 50, 50, 0);
        glTranslatef(0, 0, 100);
        //*/

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
