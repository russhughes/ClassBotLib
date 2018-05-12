# ClassBotLib

This is an arduino library to control a [small 3D printed drawing robot](https://www.thingiverse.com/thing:1104889) based on [MakersBox's](https://www.thingiverse.com/MakersBox) [Arduino Chassis for Drawing Robot](https://www.thingiverse.com/thing:1091401) and a [custom Arduino Shield](https://easyeda.com/EZG0bble/ClassBot_copy_copy-b2797f6d387242cd86f59364dd86db91) to drive a pair of 28BYJ-48 stepper motors using two ULN2003 driver IC's. The shield also has room for a SPI Serial Ram Chip and a I2C Serial EEPROM but they are not used in this library.  Take a look at the [TinyBasic Plus ClassBot Edition Github repo](https://github.com/russhughes/TinyBasicPlus) for another way to run the bot.

Requires these Arduino Libraries:
- http://www.airspayce.com/mikem/arduino/AccelStepper/

# Library Functions


## ClassBot
`ClassBot::ClassBot(int l1 = 9, int l2 = 7, int l3 = 8, int l4 = 6, int r1 = 2, int r2 = 4, int r3 = 3, int r4 = 5, int ServoPin = A0);`

Constructor. Creates and configures the ClassBot library.

#### Parameters
l1 | left motor pin 1 | default 9
l2 | left motor pin 2 | default 7
l3 | left motor pin 3 | default 8
l4 | left motor pin 4 | default 6
r1 | right motor pin 1 | default 2
r2 | right motor pin 2 | default 4
r3 | right motor pin 3 | default 3
r4 | right motor pin 4 | default 5
ServoPin | Pen servo pin | default A0

## penDown
`void penDown();`

Lower the pen to the paper.

## penUp
`void penUp();`

Raise the pen off the paper

## moveForard
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

Turn to `heading` compass heading

## moveTo
`void moveTo(long x, long y, boolean penUp=true, float scale = 1);`

Move to cartesian coordinates `x,y` with the pen up or down as given by `penUp`. `scale` sets the coordinate size in milimeters.

## drawChar       
`void drawChar(char ch, float scale);`

## writeText
`void writeText(char *str, float scale);`

## done
`void done();`

## setX
`void setX(long x);`

## setY
`void setY(long y);`

## setH
`void setH(float degrees);`

## getPen
`boolean getPen();`

## getX
`long getX();`

## getY
`long getY();`

## getH
`float getH();`
 
## Hershey font idenfiers

* FONT_ASTROLOGY
* FONT_CURSIVE
* FONT_CYRILC_1
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
