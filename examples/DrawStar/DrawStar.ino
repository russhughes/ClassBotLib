
//
// Draw a star
//

#include "ClassBot.h"

int side = 20;
int points = 5;

void setup()
{
    ClassBot bot;

    float angle = 180.0 - 180.0 / points;
    int i; 
   
    bot.penDown();
    for (i = 0; i < points; i++) {
        bot.moveForward(side);
        bot.turnLeft(angle);
        bot.moveForward(side);
    }

    bot.done();
}

void loop()
{
}

