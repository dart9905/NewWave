//
//  Management.cpp
//  NewWave
//
//  Created by macbook on 20/04/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "Management.hpp"

#define ASSERT(expression)\
if (!(expression)) \
{\
FILE *files = fopen ("LogFiles.txt", "at");\
\
fprintf(files, "==========ASSERT_Management=========\n\n");\
fprintf(files, "ERROR:\nAssertion failed: %s\n   in file %s;\n   in line %i.\n", #expression, __FILE__, __LINE__);\
fprintf(files, "\n===========================\n\n");\
\
fclose(files);\
assert (expression);\
}

/*
 *
 *          BAROBJ
 *
 */


const float PI          = 3.141592653;   ///< Pi - pizdec

BarOBJ::BarOBJ(sf::RenderWindow& window):
window_(window)
{
}

BarOBJ::~BarOBJ()
{
    
}

int BarOBJ::update()
{
    
    return 0;
}

int BarOBJ::draw()
{
    return 0;
}

int BarOBJ::get()
{
    return name_;
}

/*
 *
 *          BUTTON
 *
 */


Button::Button(sf::RenderWindow& window): BarOBJ(window)
{
    name_ = BUTTON;
}

Button::~Button()
{
    
}

int Button::update()
{
    return 0;
}

int Button::draw(sf::RenderWindow& window)
{
    
    return 0;
}

/*
 *
 *          SLIDER
 *
 */


Slider::Slider(sf::RenderWindow& window): BarOBJ(window)
{
    name_ = SLIDER;
}

Slider::~Slider()
{
    
}

int Slider::update()
{
    return 0;
}

int Slider::draw(sf::RenderWindow& window)
{
    return 0;
}

/*
 *
 *          BAR
 *
 */


Bar::Bar(float width, float height, float x, float y, sf::RenderWindow& window):
width_(width),
height_(height),
x_(x),
y_(y),
window_(window)
{
    rect.setSize(sf::Vector2f(width_, height_));
    rect.setFillColor(sf::Color(20,20,20));
    rect.setPosition(x, y);
    size_ = 5;
    data_ = new BarOBJ* [size_];
}

Bar::Bar(float width, float height, float x, float y, sf::RenderWindow& window, int i):
width_(width),
height_(height),
x_(x),
y_(y),
window_(window),
size_(i)
{
    rect.setSize(sf::Vector2f(width_, height_));
    rect.setFillColor(sf::Color(20,20,20));
    rect.setPosition(x_, y_);
    data_ = new BarOBJ* [size_];
}

Bar::~Bar()
{
    size_ = -1;
    capacity_ = -1;
    delete [] data_;
}

int Bar::add(BarOBJ* obj)
{
    if (capacity_ + 1 == size_)
    {
        BarOBJ** newdata = new BarOBJ* [size_ * 2] {nullptr};
        std::copy(&(data_ [0]), &(data_[size_]), newdata);
        
        size_ = size_ * 2;
        delete data_;
        
        data_ = newdata;
    }
    capacity_++;
    data_ [capacity_] = obj;
    return 0;
}

int Bar::update()
{
    for (int i = 0; i < capacity_ + 1; i++) {
        data_ [i]->update();
    }
    return 0;
}

int Bar::draw()
{
    
    window_.pushGLStates();
    window_.draw(rect);
    window_.popGLStates();
    for (int i = 0; i < capacity_ + 1; i++) {
        data_ [i]->draw();
    }
    return 0;
}


void Bar::setdrawparam(float width, float height, float x, float y)
{
    width_ = width;
    height_ = height;
    rect.setSize(sf::Vector2f(width_, height_));
    x_ = x;
    y_ = y;
    rect.setPosition(x_, y_);
    return;
}

void Bar::setwidth(float width)
{
    width_ = width;
    rect.setSize(sf::Vector2f(width_, height_));
    return;
}

void Bar::setheight(float height)
{
    height_ = height;
    rect.setSize(sf::Vector2f(width_, height_));
    return;
}

void Bar::setx(float x)
{
    x_ = x;
    rect.setPosition(x_, y_);
    return;
}

void Bar::sety(float y)
{
    y_ = y;
    rect.setPosition(x_, y_);
    return;
}


float Bar::getwidth()
{
    return width_;
}
float Bar::getheight()
{
    return height_;
}
float Bar::getx()
{
    return x_;
}
float Bar::gety()
{
    return y_;
}

int Bar::getsize()
{
    return size_;
}

int Bar::getcapacity()
{
    return capacity_;
}

BarOBJ* Bar::operator [] (int i)
{
    ASSERT(i < 0 || i > size_);
    return data_[i];
}
