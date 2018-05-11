
//
// Simple text drawing example
//

// You can use a #define statement to select which font to use
// if you do not select a font (or mispell the name of the font)
// FONT_ROWMANS will be used by default. This must be done before
// the #include "ClassBot.h" line.

#define FONT_SCRIPTS
#include "ClassBot.h"

void setup()
{
    ClassBot bot;

    bot.writeText((char *)"Hello!", 2);
    bot.done();
}

void loop()
{
}

