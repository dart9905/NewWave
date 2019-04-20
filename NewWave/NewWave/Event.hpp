//
//  Event.hpp
//  NewWave
//
//  Created by macbook on 30/03/2019.
//  Copyright © 2019 macbook. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include "GraphFile.hpp"
#include "Management.hpp"
#include <math.h>
#include <stdio.h>
#include <unistd.h>


/*!
 \brief the function of processing all events (keystrokes, mouse buttons, etc).
 \param window the reference to the current window
 \param mouse reference to the current mouse object
 \return 0
 */
int EVENT (sf::RenderWindow& window, mouse_t& mouse);

#endif /* Event_hpp */
