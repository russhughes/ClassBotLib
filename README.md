
![](https://raw.githubusercontent.com/russhughes/ClassBotLib/master/doc/images/hello.jpg)

# ClassBotLib

ClassBotLib is an arduino library to control a small [3D printed drawing robot](https://www.thingiverse.com/thing:1104889) based on [MakersBox's](https://www.thingiverse.com/MakersBox) [Arduino Chassis for Drawing Robot](https://www.thingiverse.com/thing:1091401). In my classes I use a custom [Arduino Shield](https://easyeda.com/EZG0bble/ClassBot_copy_copy-b2797f6d387242cd86f59364dd86db91) to drive a pair of 28BYJ-48 stepper motors using two ULN2003 driver IC's. The shield has room for a SPI Serial Ram Chip and a I2C Serial EEPROM that are not used in this library.  Take a look at the [TinyBasic Plus ClassBot Edition Github repo](https://github.com/russhughes/TinyBasicPlus) for another way to run the bot.

### Requires the AccelStepper Library:
- http://www.airspayce.com/mikem/arduino/AccelStepper/

# Using the Library

A #define statement is used to select which of the [Hershey vector fonts](https://en.wikipedia.org/wiki/Hershey_fonts) to use for drawing text. If you do not select a font (or mispell the name of the font) FONT_ROWMANS will be used by default. This must be done before including the "ClassBot.h" header file.

    #define FONT_SCRIPTS
    #include "ClassBot.h"

#### Available Hershey fonts

* FONT_ASTROLOGY
* FONT_CURSIVE
* FONT_CYRILC\_1
* FONT_CYRILLIC
* FONT_FUTURAL
* FONT_FUTURAM
* FONT_GOTHGBT
* FONT_GOTHGRT
* FONT_GOTHICENG
* FONT_GOTHICGER
* FONT_GOTHICITA
* FONT_GOTHITT
* FONT_GREEKC
* FONT_GREEK
* FONT_GREEKS
* FONT_JAPANESE
* FONT_MARKERS
* FONT_MATHLOW
* FONT_MATHUPP
* FONT_METEOROLOGY
* FONT_MUSIC
* FONT_ROWMAND
* FONT_ROWMANS
* FONT_ROWMANT
* FONT_SCRIPTC
* FONT_SCRIPTS
* FONT_SYMBOLIC
* FONT_TIMESG
* FONT_TIMESIB
* FONT_TIMESI
* FONT_TIMESRB
* FONT_TIMESR


## ClassBot
`ClassBot::ClassBot(int l1 = 9, int l2 = 7, int l3 = 8, int l4 = 6, int r1 = 2, int r2 = 4, int r3 = 3, int r4 = 5, int ServoPin = A0);`

Constructor, create's the ClassBot object and configures the library. Be sure to set your stepper motor pins if your bot is wired differently then the default.

#### Parameters
| Parameter | Description | Default Value |
--- | ----------------- | --------
l1 | left motor pin 1 | D9
l2 | left motor pin 2 | D7
l3 | left motor pin 3 | D8
l4 | left motor pin 4 | D6
r1 | right motor pin 1 | D2
r2 | right motor pin 2 | D4
r3 | right motor pin 3 | D3
r4 | right motor pin 4 | D5
ServoPin | Pen servo pin | A0

## penDown
`void penDown();`

Lower the pen to the paper.

## penUp
`void penUp();`

Raise the pen off the paper

## moveForward
`void moveForward(float distance);`

Move forward `distance` milimeters.

## moveBackward
`void moveBackward(float distance);`

Move backward `distance` milimeters.

## turnLeft
`void turnLeft(float degrees);`

Turn `degrees` to the left.

## turnRight
`void turnRight(float degrees);`

Turn `degrees` to the right.

## turnTo
`void turnTo(float heading);`

Turn to face `heading` compass heading in degrees.

## moveTo
`void moveTo(long x, long y, boolean penUp=true, float scale = 1);`

Move to cartesian coordinates `x,y` with the pen up or down as specified by `penUp`. `scale` sets the coordinate size in milimeters and defaults to 1mm.

## drawChar       
`void drawChar(char ch, float scale = 1);`

Draw the character `ch` at the `scale` size.

## writeText
`void writeText(char *str, float scale = 1);`

Write the string `str` at the `scale` size 

## done
`void done();`

Turn off steppers motors and raise the pen.

## setX
`void setX(long x);`

Set the current cartesian X coordinate to `x`.

## setY
`void setY(long y);`

Set the current cartesian Y coordinate to `y`.


## setH
`void setH(float degrees);`

Set the current heading in degrees

## getPen
`boolean getPen();`

Returns true id the pen is raised.

## getX
`long getX();`

Return the current cartesian X coordinate of the bot.

## getY
`long getY();`

Return the current cartesian Y coordinate of the bot.

## getH
`float getH();`

Return the current heading of the bot.

## Example 1: Draw a box

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

## Example 2: Approximate a circle or ellipse using a polygon 

	#include "ClassBot.h"

	int radiusX = 30;
	int radiusY = 30;
	int sides = 20;			// polygon number of sides
	
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

## Example 3: Draw a star
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

## Example 4: Write Text

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




