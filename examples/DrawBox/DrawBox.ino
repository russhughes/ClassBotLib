
//
// Draw a box
//

#include "ClassBot.h"

int side = 20;

void setup()
{
    ClassBot bot;

    bot.penDown();
    for (int i=1; i <5; i++) {
        bot.moveForward(side);
        bot.turnLeft(90);
    }
 
    bot.done();
}

void loop()
{
}

