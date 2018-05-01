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

// #include "fonts/astrology.h"
#include "fonts/cursive.h"
// #include "fonts/cyrilc_1.h"
// #include "fonts/cyrillic.h"
// #include "fonts/futural.h"
// #include "fonts/futuram.h"
// #include "fonts/gothgbt.h"
// #include "fonts/gothgrt.h"
// #include "fonts/gothiceng.h"
// #include "fonts/gothicger.h"
// #include "fonts/gothicita.h"
// #include "fonts/gothitt.h"
// #include "fonts/greek.h"
// #include "fonts/greekc.h"
// #include "fonts/greeks.h"
// #include "fonts/japanese.h"
// #include "fonts/markers.h"
// #include "fonts/mathlow.h"
// #include "fonts/mathupp.h"
// #include "fonts/meteorology.h"
// #include "fonts/music.h"
// #include "fonts/rowmand.h"
// #include "fonts/rowmans.h"
// #include "fonts/rowmant.h"
// #include "fonts/scriptc.h"
// #include "fonts/scripts.h"
// #include "fonts/symbolic.h"
// #include "fonts/timesg.h"
// #include "fonts/timesi.h"
// #include "fonts/timesib.h"
// #include "fonts/timesr.h"
// #include "fonts/timesrb.h"

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
        void moveTo(long x, long y, float scale, boolean penUp);
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