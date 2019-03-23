/*!
 \file
 \authors LordDifine -- Khromov Alexey
 \version A1.1mac
 \date 18.03.2019
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
    
    mouse_t Mouse(&window);
    
    float dx = 0;
    float dy = 0;
    float dz = 0;
    float speed = 0.1;

    // Start the game loop
    while (window.isOpen())
    {
        
        // Clear the depth buffer
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        window.clear(sf::Color::White);
        
        float time = clock.getElapsedTime().asMilliseconds() / 2;
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            dx = 0;
            dy = 0;
            dz = 0;
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                dx = -sin (Mouse.angleX_ / 180 * PI) * speed;
                dy =  tan (Mouse.angleY_ / 180 * PI) * speed;
                dz = -cos (Mouse.angleX_ / 180 * PI) * speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                dx =  sin (Mouse.angleX_ / 180 * PI) * speed;
                dy = -tan (Mouse.angleY_ / 180 * PI) * speed;
                dz =  cos (Mouse.angleX_ / 180 * PI) * speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                dx =  sin ((Mouse.angleX_ + 90) / 180 * PI) * speed;
                dz =  cos ((Mouse.angleX_ + 90) / 180 * PI) * speed;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                dx =  sin ((Mouse.angleX_ - 90) / 180 * PI) * speed;
                dz =  cos ((Mouse.angleX_ - 90) / 180 * PI) * speed;
            }
            Mouse.x_+=dx;
            Mouse.y_+=dy;
            Mouse.z_+=dz;
        }
        
        
        // Draw the sprite
        /*
        sprite.setScale((window.getSize()).x / (texture.getSize()).x, (window.getSize()).y / (texture.getSize()).y);
        window.pushGLStates();
        window.draw(sprite);
        window.popGLStates();
        //*/
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(Mouse.x_, Mouse.y_, Mouse.z_, Mouse.x_ - sin(Mouse.angleX_/180*PI), Mouse.y_ + tan(Mouse.angleY_/180*PI), Mouse.z_ - cos(Mouse.angleX_/180*PI), 0, 1, 0);
        Mouse.angle();
        //*
        // Working with the camera
        glTranslatef(0, 0, -100);
        //glRotatef(time, 50, 50, 0);
        // draw box
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                glTranslatef(i * GLOBsize, j * GLOBsize, 0);
                createBox(arrayBox [0], GLOBsize);
                glTranslatef(-i * GLOBsize, -j * GLOBsize, 0);
            }
        }
        //glRotatef(-time, 50, 50, 0);
        //glTranslatef(0, 0, 100);
        //*/

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
