
#include "ClassBot.h"

//
// initalize ClassBot
//

ClassBot::ClassBot()
{
    leftMotor = new AccelStepper(AccelStepper::HALF4WIRE, 9, 7, 8, 6, true);  // d'oh! -- Classbot 1.0 board is backwards
    rightMotor = new AccelStepper(AccelStepper::HALF4WIRE, 2, 4, 3, 5, true);

    pinMode(A0, OUTPUT);
    penServo.attach(A0);
    penUp();

    leftMotor->setMaxSpeed(MAX_SPEED);
    rightMotor->setMaxSpeed(MAX_SPEED);

    motors.addStepper(*leftMotor);
    motors.addStepper(*rightMotor);
}

//
// Set pen down
//

void ClassBot::penDown()
{
    penServo.write(PEN_DOWN_ANGLE);
    penIsUp = false;
    delay(200);
}

//
// Pick pen up
//

void ClassBot::penUp()
{
    penServo.write(PEN_UP_ANGLE);
    penIsUp = true;
    delay(200);
}

//
// Internal fuction to set steps to move
// left or right stepper motor with simple
// backlash compensation.
// 

void ClassBot::setStep(int which, float dist)
{
    boolean pos = dist > 0;
    steps[which] = dist;

    if (lastPos[which] != -1)
    {
        if (pos & !lastPos[which])
            steps[which] += backlashComp;
        if (!pos & lastPos[which])
            steps[which] -= backlashComp;
    }

    lastPos[which] = pos;
}

//
// Move ClassBot forward "distance" millimeters
//

void ClassBot::moveForward(float distance)
{
    int s = int(distance * stepsDist);

    setStep(LEFT, -s);
    setStep(RIGHT, s);

    motors.moveTo(steps);
    motors.runSpeedToPosition();

    leftMotor->setCurrentPosition(0);
    rightMotor->setCurrentPosition(0);
}

//
// Move ClassBot backward "distance" millimeters
//

void ClassBot::moveBackward(float distance)
{
    int s = int(distance * stepsDist);

    setStep(LEFT, s);
    setStep(RIGHT, -s);

    motors.moveTo(steps);
    motors.runSpeedToPosition();

    leftMotor->setCurrentPosition(0);
    rightMotor->setCurrentPosition(0);
}

//
// Turn ClassBot left degrees
// 

void ClassBot::turnLeft(float degrees)
{
    float distance = wheelBPI * (degrees / 360.0);
    int s = int(distance * stepsDist);

    setStep(LEFT, s);
    setStep(RIGHT, s);

    motors.moveTo(steps);
    motors.runSpeedToPosition();

    leftMotor->setCurrentPosition(0);
    rightMotor->setCurrentPosition(0);
}

//
// Turn ClassBot right degrees
// 

void ClassBot::turnRight(float degrees)
{
    float distance = wheelBPI * (degrees / 360.0);
    int s = int(distance * stepsDist);

    setStep(LEFT, -s);
    setStep(RIGHT, -s);

    motors.moveTo(steps);
    motors.runSpeedToPosition();

    leftMotor->setCurrentPosition(0);
    rightMotor->setCurrentPosition(0);
}

// Calculate the bearing (angle to turn to) from where we are (a1, a2)
// to where we want to go (b1, b2)

double ClassBot::bearing(double a1, double a2, double b1, double b2)
{
    double theta = atan2(b1 - a1, a2 - b2);
    
    if (theta < 0.0)
        theta += TWOPI;

    return theta * RAD2DEG;
}

// We know where we are and we want to go to x, y
// find the direction we need to turn to and then 
// calculate the distance from our location to the 
// destination using the Pythagorean theorem.

void ClassBot::moveTo(long x, long y, float scale, boolean penIsUp)
{
    double b;
    double r;
    long dx, dy, dh;

    penUp();

    if ((x != botX) || (y != botY))         // if we are not already where we want to go
    {
        b = bearing(botX, botY, x, y);      // find the direction to where we want to go

        dx = x - botX;                      // calcucate how far over do we have to go
        dy = y - botY;                      // calculate how far down/up we have to go

        r = sqrt((dx * dx) + (dy * dy));    // find the distance using the Pythagorean theorem

        dh = botH - b;                      // find the difference between the direction we are facing
                                            // and the direction we need to face
        if (dh > 180)
            dh = dh - 360;

        if (dh < -180)
            dh = dh + 360;

        if (dh < 0)                         //  and turn right
            turnRight(abs(dh));

        if (dh > 0)                         // or turn left
            turnLeft(dh);

        if (!penIsUp)                       // if the pen is not supposed to be up, set it down
            penDown();

        moveForward(r * scale);             // move forward the distance * the scale

        botX = x;                           // keep track of our new position
        botY = y;
        botH = b;                           // and our new heading
    }
}

//
// Draw a character starting at the current location
// sized 'scale'
//

void ClassBot::drawChar(char ch, float scale)
{
    char *vectors;
    byte c, length, width, i, pup = true;
    int x = botX, y = botY, vX, vY, xofs, yofs, left, right;

    if ((ch > 31) && (ch < 127))
    {
        c = ch - 32;
        vectors = (char *) pgm_read_word(&font[c]); // Get the address of the data for this glyph
        length  = pgm_read_byte(vectors++);         // First byte contains the number of vectors for this glyph
        left    = pgm_read_byte(vectors++) - 'R';   // Position of the left side of glyph
        right   = pgm_read_byte(vectors++) - 'R';   // Position of the right side of the glyph
        width   = right - left;                     // Calculate the character with
        xofs    = -left;                            // Zero out the left side to midline
        yofs    = 16 - 7;

        while (length--)
        {
            vX = pgm_read_byte(vectors++);       // X coordinate of point
            vY = pgm_read_byte(vectors++);       // Y coordinate of point

            if ((vX == ' ') && (vY == 'R'))      // if the value is " R"
            {
                pup = true;                      //  pick the pen up
                continue;                        //  this is not a move
            }

            vX -= 'R';
            vY -= 'R';

            moveTo(vX + xofs + x, yofs + vY + y, scale, pup);		// otherwise move to the X, Y coordinate
            if (pup)                                      		// if the pen was up, set the flag to down
                pup = false;
        }
    }

    moveTo(x + width, y, scale, true); 			// And move to the position for the next character
}

//
// Write "str" character string starting at the current location
// sized 'scale'

void ClassBot::writeText(char *str, float scale)
{
    char *s = str;

    while (*s)
        drawChar(*s++, scale);
}

//
// Done, pick pen up and turn off steppers
//

void ClassBot::done()
{
    penUp();
    for (int i = 2; i < 10; i++)
        digitalWrite(i, LOW);
}

//
//  Set the current X location
//

void ClassBot::setX(long newX)
{
    botX = newX;
}

//
//  Set the current Y location
//

void ClassBot::setY(long newY)
{
    botY = newY;
}

//
// Set the current heading in degrees
//

void ClassBot::setH(float degrees)
{
    botH = degrees;
}

//
// Returns true if the pen is up
//

boolean ClassBot::getPen()
{
    return penIsUp;
}

//
// Returns the current X location
//

long ClassBot::getX()
{
    return botX;
}

//
// Returns the current Y location
//

long ClassBot::getY()
{
    return botY;
}

//
// Returns the current heading in degrees
//

float ClassBot::getH()
{
    return botH;
}

// 
// EOF
//
