
//
// Approximate a circle or ellipse using a polygon
//

#include "ClassBot.h"

int radiusX = 30;
int radiusY = 30;       
int sides = 20;         // polygon number of sides

void setup()
{
    ClassBot bot;

    float step = 2 * PI / sides;
    float theta;

    int x, y, xx, yy;
    
    int startX = bot.getX();
    int startY = bot.getY();
    int startH = bot.getH();
        
    for (theta = 0;  theta < 2 * PI;  theta += step) {
        x = radiusX * cos(theta);
        y = radiusY * sin(theta);
        if (theta == 0) {
            xx = x;
            yy = y;
            bot.moveTo(x, y, true);
        } else {
            bot.moveTo(x, y, false);
        }
    }
    
    bot.moveTo(xx, yy, false);
    bot.moveTo(startX, startY, true);
    bot.turnTo(startH);

    bot.done();
}

void loop()
{
}

