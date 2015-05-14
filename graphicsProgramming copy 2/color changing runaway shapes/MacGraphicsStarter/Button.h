//
//  Button.h
//  MacGraphicsStarter
//
//  Created by Cody Brown on 11/2/14.
//
//

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdio.h>
#include "Rectangle.h"

class Button : public Rectangle
{
    
public:
    Button(double x1, double y1, double x2, double y2, char *title, bool active, double red, double green, double blue, bool solid);
    char * mTitle;
    bool clicked(double x, double y);
    bool setActive();
    bool setInactive();
    bool getActive();
    bool mActive;
    void drawSlider(double red, double green, double blue);
};


#endif /* defined(__MacGraphicsStarter__Button__) */
