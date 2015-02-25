//
//  Button.cpp
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#include "Button.h"


Button::Button(double x1, double y1, double x2, double y2, char *title, bool active, double red, double green,double blue, bool solid)
: Rectangle(x1, y1, x2, y2, red, green, blue, solid)
{
    mTitle = title;
    mActive = active;
}

bool Button::clicked(double x, double y)
{
    if(x > points[0] && x < points[2] && y > points[1] && y < points[3])
    {
        return true;
    }
    
    return false;
}

bool Button::getActive()
{
    return this->mActive;
}

bool Button::setActive()
{
    return this->mActive = true;
}
 bool Button::setInactive()
{
    return this->mActive = false;
}
