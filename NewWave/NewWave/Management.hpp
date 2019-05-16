//
//  Management.hpp
//  NewWave
//
//  Created by macbook on 20/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef Management_hpp
#define Management_hpp

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GLUT/GLUT.h>
#include <math.h>
#include <iostream>
#include <cassert>

enum NameBarOBJ {
    BUTTON = 1,
    SLIDER = 2
};

class BarOBJ
{
protected:
    int name_;
    int sizepoint_ = 28;
    float width_ = 0;
    float height_ = 0;
    sf::RenderWindow& window_;
public:
    BarOBJ(sf::RenderWindow& window);
    virtual ~BarOBJ();
    virtual int update();
    virtual int draw();
    virtual int get();
    
};

class Button: virtual protected BarOBJ
{
public:
    Button(sf::RenderWindow& window);
    ~Button();
    int update();
    int draw(sf::RenderWindow& window);
    
};

class Slider: virtual protected BarOBJ
{
public:
    Slider(sf::RenderWindow& window);
    ~Slider();
    int update();
    int draw(sf::RenderWindow& window);
    
};



class Bar
{
    BarOBJ** data_ = nullptr;
    float width_ = 0;
    float height_ = 0;
    float x_ = 0;
    float y_ = 0;
    int size_ = 0;
    int capacity_ = -1;
    
    sf::RenderWindow& window_;
    sf::RectangleShape rect;
    
public:
    Bar(float width, float height, float x, float y, sf::RenderWindow& window);
    Bar(float width, float height, float x, float y, sf::RenderWindow& window, int i);
    ~Bar();
    
    int add(BarOBJ* obj);
    int update();
    int draw();
    
    void setdrawparam(float width, float height, float x, float y);
    void setwidth(float width);
    void setheight(float height);
    void setx(float x);
    void sety(float y);
    
    
    float getwidth();
    float getheight();
    float getx();
    float gety();
    
    int getsize();
    int getcapacity();
    BarOBJ* operator [] (int i);
};



#endif /* Management_hpp */
