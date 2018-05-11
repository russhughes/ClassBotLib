//
// ClassBot.h
//
//
// dependencies:
//		AccelStepper
//		MultiStepper
//

#ifndef ClassBot_h
#define ClassBot_h

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>
#include <math.h>

static const double TWOPI = 6.2831853071795865;
static const double RAD2DEG = 57.2957795130823209;

// Choose one of the fonts from the fonts directory to use
// for drawing text, only one fits in memory at a time. I 
// havn't tested all of these but they should work if they
// fit in memory.

#ifdef FONT_ASTROLOGY
#include "fonts/astrology.h"
#endif

#ifdef FONT_CURSIVE
#include "fonts/cursive.h"
#endif

#ifdef FONT_CYRILC_1
#include "fonts/cyrilc_1.h"
#endif

#ifdef FONT_CYRILLIC
#include "fonts/cyrillic.h"
#endif

#ifdef FONT_FUTURAL
#include "fonts/futural.h"
#endif

#ifdef FONT_FUTURAM
#include "fonts/futuram.h"
#endif

#ifdef FONT_GOTHGBT
#include "fonts/gothgbt.h"
#endif

#ifdef FONT_GOTHGRT
#include "fonts/gothgrt.h"
#endif

#ifdef FONT_GOTHICENG
#include "fonts/gothiceng.h"
#endif

#ifdef FONT_GOTHICGER
#include "fonts/gothicger.h"
#endif

#ifdef FONT_GOTHICITA
#include "fonts/gothicita.h"
#endif

#ifdef FONT_GOTHITT
#include "fonts/gothitt.h"
#endif

#ifdef FONT_GREEKC
#include "fonts/greekc.h"
#endif

#ifdef FONT_GREEK
#include "fonts/greek.h"
#endif

#ifdef FONT_GREEKS
#include "fonts/greeks.h"
#endif

#ifdef FONT_JAPANESE
#include "fonts/japanese.h"
#endif

#ifdef FONT_MARKERS
#include "fonts/markers.h"
#endif

#ifdef FONT_MATHLOW
#include "fonts/mathlow.h"
#endif

#ifdef FONT_MATHUPP
#include "fonts/mathupp.h"
#endif

#ifdef FONT_METEOROLOGY
#include "fonts/meteorology.h"
#endif

#ifdef FONT_MUSIC
#include "fonts/music.h"
#endif

#ifdef FONT_ROWMAND
#include "fonts/rowmand.h"
#endif

#ifdef FONT_ROWMANS
#include "fonts/rowmans.h"
#endif

#ifdef FONT_ROWMANT
#include "fonts/rowmant.h"
#endif

#ifdef FONT_SCRIPTC
#include "fonts/scriptc.h"
#endif

#ifdef FONT_SCRIPTS
#include "fonts/scripts.h"
#endif

#ifdef FONT_SYMBOLIC
#include "fonts/symbolic.h"
#endif

#ifdef FONT_TIMESG
#include "fonts/timesg.h"
#endif

#ifdef FONT_TIMESIB
#include "fonts/timesib.h"
#endif

#ifdef FONT_TIMESI
#include "fonts/timesi.h"
#endif

#ifdef FONT_TIMESRB
#include "fonts/timesrb.h"
#endif

#ifdef FONT_TIMESR
#include "fonts/timesr.h"
#endif

// if no font was selected default to rowmans

#ifndef FONT_INCLUDED
#include "fonts/rowmans.h"
#endif

#define MAX_SPEED 1000
#define LEFT 0
#define RIGHT 1

// set for your bot's pen servo

#define PEN_UP_ANGLE 150
#define PEN_DOWN_ANGLE 150 - 90

static int stepsPerRev = 4076;                      // stepper steps per revloution
static const int backlashComp = 12;                 // compensation for gear lash 
static float wheelDiameter =  65;				    // mm (increase = spiral out)
static int wheelBase = 112; 					    // mm (increase = spiral in)

static float wheelBPI = wheelBase * PI;
static float stepsDist = stepsPerRev / (wheelDiameter *PI);

class ClassBot
{
    public:
        ClassBot(int l1 = 9, int l2 = 7, int l3 = 8, int l4 = 6, int r1 = 2, int r2 = 4, int r3 = 3, int r4 = 5, int servoPin = A0);

        void penDown();
        void penUp();
        void moveForward(float distance);
        void moveBackward(float distance);
        void turnLeft(float degrees);
        void turnRight(float degrees);
        void turnTo(float heading);
        void moveTo(long x, long y, boolean penUp=true, float scale = 1);
               
        void drawChar(char ch, float scale);
        void writeText(char *str, float scale);
        void done();

        void setX(long x);
        void setY(long y);
        void setH(float degrees);

        boolean getPen();
        long getX();
        long getY();
        float getH();

    private:
        long botX = 0;			// at origin
        long botY = 0;
        float botH = 0;			// facing north

        boolean penIsUp;

        AccelStepper *leftMotor;
        AccelStepper *rightMotor;
        MultiStepper motors;

        long steps[2] = { 0, 0 };
        int lastPos[2] = { -1, -1 };
        Servo penServo;

        void setStep(int which, float dist);
        double bearing(double a1, double a2, double b1, double b2);
};

#endif

//
// EOF
//