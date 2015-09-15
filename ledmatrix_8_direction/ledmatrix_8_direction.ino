// This program extends the led matrix with four input switches l,r,u,d and displays the given input DIRECTION as an
// arrow on the matrix
#define NO_PORTC_PINCHANGES
#define NO_PORTD_PINCHANGES
#include <PinChangeInt.h>

// pin connections
#define INPUTDOWNPIN 8
#define INPUTUPPIN 9
#define INPUTLEFTPIN 11
#define INPUTRIGHTPIN 12

enum directions { IDLE, LEFT, RIGHT, UP, DOWN, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

volatile bool INPUTLEFT(false);
volatile bool INPUTRIGHT(false);
volatile bool INPUTUP(false);
volatile bool INPUTDOWN(false);

unsigned short DIRECTION(IDLE);

void readInput() {
    // should me more like a lookup table
    //  l   r  |  u   d  |  value
    // ––––––––|–––––––––|–––––––––––––––
    //  0   0  |  0   0  |  0   IDLE
    //  1   1  |  1   1  |  0   IDLE
    //  1   1  |  0   0  |  0   IDLE
    //  0   0  |  1   1  |  0   IDLE
    //  1   0  |  0   0  |  1   LEFT
    //  1   0  |  1   1  |  1   LEFT
    //  0   1  |  0   0  |  2   RIGHT
    //  0   1  |  1   1  |  2   RIGHT
    //  0   0  |  1   0  |  3   UP
    //  1   1  |  1   0  |  3   UP
    //  0   0  |  0   1  |  4   DOWN
    //  1   1  |  0   1  |  4   DOWN
    //  1   0  |  1   0  |  5   UPLEFT
    //  0   1  |  1   0  |  6   UPRIGHT
    //  1   0  |  0   1  |  7   DOWNLEFT
    //  0   1  |  0   1  |  8   DOWNRIGHT

    switch ((INPUTLEFT ^ INPUTRIGHT) + (INPUTUP ^ INPUTDOWN)) {
    case 0:
    default:
        DIRECTION = IDLE;
        return;
    case 1:
        if (INPUTRIGHT ^ INPUTLEFT) { DIRECTION = (INPUTLEFT) ? LEFT : RIGHT; } else {
            DIRECTION = (INPUTUP) ? UP : DOWN;
        }
        return;
    case 2:
        if (INPUTLEFT) { DIRECTION = (INPUTUP) ? UPLEFT : DOWNLEFT; } else {
            DIRECTION = (INPUTUP) ? UPRIGHT : DOWNRIGHT;
        }
        return;
    }
}

void resetInput() {
    INPUTLEFT = false;
    INPUTRIGHT = false;
    INPUTUP = false;
    INPUTDOWN = false;
}

void interruptOnLeft() { INPUTLEFT = true; }

void interruptOnRight() { INPUTRIGHT = true; }

void interruptOnUp() { INPUTUP = true; }

void interruptOnDown() { INPUTDOWN = true; }

void setup() {
    Serial.begin(9600);

    // attach software interrupts for inputs
    PCintPort::attachInterrupt(INPUTDOWNPIN, interruptOnDown, RISING);
    PCintPort::attachInterrupt(INPUTUPPIN, interruptOnUp, RISING);
    PCintPort::attachInterrupt(INPUTLEFTPIN, interruptOnLeft, RISING);
    PCintPort::attachInterrupt(INPUTRIGHTPIN, interruptOnRight, RISING);
}

void loop() {
    Serial.println("something");
    readInput();
    Serial.println(DIRECTION);
    resetInput();
    delay(1000);
}
