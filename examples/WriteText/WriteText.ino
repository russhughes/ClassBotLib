
//
// Simple text drawing example
//

#include "ClassBot.h"

// Stepper wiring set in ClassBot.cpp
//	left is connected to pins 9, 7, 8, 6
//  right is connected to pins 2, 4, 3 ,5
//  Pen servo is connected to pin A0
//

void setup()
{
    ClassBot bot;

    bot.writeText((char *)"Hello!", 2);
    bot.done();
}

void loop()
{
}

