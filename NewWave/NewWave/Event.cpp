//
//  Event.cpp
//  NewWave
//
//  Created by macbook on 30/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#include "Event.hpp"


int EVENT (sf::RenderWindow& window, mouse_t& mouse) {
    mouse.dx_ /= 10;
    mouse.dy_ /= 10;
    mouse.dz_ /= 10;
    if (mouse.dx_ * mouse.dx_ < mouse.dx_) {
        mouse.dx_ = 0;
    }
    if (mouse.dy_ * mouse.dy_ < mouse.dy_) {
        mouse.dy_ = 0;
    }
    if (mouse.dz_ * mouse.dz_ < mouse.dz_) {
        mouse.dz_ = 0;
    }
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                
                break;
            case sf::Event::LostFocus:
                
                break;
            case sf::Event::GainedFocus:
                
                break;
            case sf::Event::TextEntered:
                
                break;
            case sf::Event::KeyPressed:
                // Escape pressed: exit
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
            case sf::Event::KeyReleased:
                
                break;
            case sf::Event::MouseWheelMoved:
                //*
                if(event.mouseWheel.delta==1) {
                    mouse.dx_ = -sin (mouse.angleX_ / 180 * PI) * mouse.speed_;
                    mouse.dy_ =  tan (mouse.angleY_ / 180 * PI) * mouse.speed_;
                    mouse.dz_ = -cos (mouse.angleX_ / 180 * PI) * mouse.speed_;
                }
                else if(event.mouseWheel.delta==-1) {
                    mouse.dx_ =  sin (mouse.angleX_ / 180 * PI) * mouse.speed_;
                    mouse.dy_ = -tan (mouse.angleY_ / 180 * PI) * mouse.speed_;
                    mouse.dz_ =  cos (mouse.angleX_ / 180 * PI) * mouse.speed_;
                }
                //*/
                break;
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button==sf::Mouse::Left)
                {
                    mouse.checkbut_ = true;
                    mouse.posold_ = sf::Mouse::getPosition(window);
                }
                break;
            case sf::Event::MouseButtonReleased:
                mouse.checkbut_ = false;
                break;
            case sf::Event::MouseMoved:
                if (mouse.checkbut_) {
                    mouse.posnew_ = sf::Mouse::getPosition(window);
                    //*
                    mouse.angleX_ -= (mouse.posnew_.x - mouse.posold_.x) / 4;
                    mouse.angleY_ -= (mouse.posnew_.y - mouse.posold_.y) / 4;
                    //*/
                    
                    if (mouse.angleX_ > 180) {
                        mouse.angleX_ -= 360;
                    }
                    
                    if (mouse.angleX_ < -180) {
                        mouse.angleX_ += 360;
                    }
                    
                    if (mouse.angleY_ > 89) {
                        mouse.angleY_ = 89;
                    }
                    
                    if (mouse.angleY_ < -89) {
                        mouse.angleY_ = -89;
                    }
                    
                    
                    mouse.x_=  mouse.R_ * sin(mouse.angleX_ / 180 * PI) * cos(mouse.angleY_ / 180 * PI);
                    
                    mouse.y_= -mouse.R_ * sin(mouse.angleY_ / 180 * PI);
                    
                    float D = mouse.RR_ - mouse.x_ * mouse.x_ - mouse.y_ * mouse.y_;
                    if (D < 0) {
                        D = 0;
                    }
                    
                    if ((mouse.angleX_ < 90) && (mouse.angleX_ > -90)) {
                        mouse.z_ = sqrt(D);
                    } else {
                        mouse.z_ = -sqrt(D);
                    }
                    mouse.posold_ = mouse.posnew_;
                    
                }
                break;
            case sf::Event::MouseEntered:
                
                break;
            case sf::Event::MouseLeft:
                
                break;
            case sf::Event::JoystickButtonPressed:
                
                break;
            case sf::Event::JoystickButtonReleased:
                
                break;
            case sf::Event::JoystickMoved:
                
                break;
            case sf::Event::JoystickConnected:
                
                break;
            case sf::Event::JoystickDisconnected:
                
                break;
            case sf::Event::TouchBegan:
                
                break;
            case sf::Event::TouchMoved:
                
                break;
            case sf::Event::TouchEnded:
                
                break;
            case sf::Event::SensorChanged:
                
                break;
            case sf::Event::Count:
                
                break;
        }
        if ((mouse.x_ + mouse.dx_) * (mouse.x_ + mouse.dx_) + (mouse.y_ + mouse.dy_) * (mouse.y_ + mouse.dy_) + (mouse.z_ + mouse.dz_) * (mouse.z_ + mouse.dz_) < 10) {
            mouse.dx_ = 0;
            mouse.dy_ = 0;
            mouse.dz_ = 0;
        }
        
        if ((mouse.x_ + mouse.dx_) * (mouse.x_ + mouse.dx_) + (mouse.y_ + mouse.dy_) * (mouse.y_ + mouse.dy_) + (mouse.z_ + mouse.dz_) * (mouse.z_ + mouse.dz_) > 1000000) {
            mouse.dx_ = 0;
            mouse.dy_ = 0;
            mouse.dz_ = 0;
        }
        
        if (mouse.dx_ != 0 || mouse.dy_ != 0 || mouse.dz_ != 0) {
            mouse.x_ += mouse.dx_;
            mouse.y_ += mouse.dy_;
            mouse.z_ += mouse.dz_;
            
            mouse.RR_ = mouse.x_ * mouse.x_ + mouse.z_ * mouse.z_ + mouse.y_ * mouse.y_;
            mouse.R_ = sqrt(mouse.RR_);
        }
    }
    
    return 0;
}
