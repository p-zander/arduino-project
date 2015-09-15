// This program implements snake with the input through four switches and the display of the game on a 8x8 led matrix
#define NO_PORTC_PINCHANGES
#define NO_PORTD_PINCHANGES
#include <PinChangeInt.h>

#define GRIDLENGTH 8  // quadratic led matrix

// pin connections
#define CLOCKPIN 2
#define XDATAPIN 3
#define YDATAPIN 5
#define LATCHPIN 6

#define INPUTDOWNPIN 9
#define INPUTUPPIN 8
#define INPUTLEFTPIN 11
#define INPUTRIGHTPIN 12

const unsigned long LOOPTIME = 750;  // in order to achieve a const FPS

enum directions { DOWN, UP, LEFT, RIGHT };
enum fieldTypes { WALL = -2, FOOD = -1, FREE = 0, TAIL = 1 };  // all values > 0 are body of the snake

short MAP[GRIDLENGTH][GRIDLENGTH];

volatile bool INPUTDOWN(false);
volatile bool INPUTUP(false);
volatile bool INPUTLEFT(false);
volatile bool INPUTRIGHT(false);

unsigned short DIRECTION(0);
unsigned short HEADPOSX(0);
unsigned short HEADPOSY(0);
unsigned short LENGTH(0);

void latch() {
    digitalWrite(LATCHPIN, HIGH);
    digitalWrite(LATCHPIN, LOW);
}

void clock() {
    digitalWrite(CLOCKPIN, HIGH);
    digitalWrite(CLOCKPIN, LOW);
}

void clock(short ticks) {
    for (int i = 0; i < ticks; ++i) clock();
}

void print0() {
    digitalWrite(XDATAPIN, HIGH);
    digitalWrite(YDATAPIN, LOW);
    clock(2 * GRIDLENGTH);

    latch();
}

void print1at(short i, short j) {
    digitalWrite(XDATAPIN, HIGH);
    digitalWrite(YDATAPIN, LOW);

    if (i == j) {
        clock(GRIDLENGTH - i - 1);

        digitalWrite(XDATAPIN, LOW);
        digitalWrite(YDATAPIN, HIGH);
        clock();
        digitalWrite(XDATAPIN, HIGH);
        digitalWrite(YDATAPIN, LOW);

        clock(i);
    } else {
        if (i > j) {
            clock(GRIDLENGTH - i - 1);
            digitalWrite(XDATAPIN, LOW);
            clock();
            digitalWrite(XDATAPIN, HIGH);

            clock(i - j - 1);
            digitalWrite(YDATAPIN, HIGH);
            clock();
            digitalWrite(YDATAPIN, LOW);

            clock(j);
        } else {
            clock(GRIDLENGTH - j - 1);
            digitalWrite(YDATAPIN, HIGH);
            clock();
            digitalWrite(YDATAPIN, LOW);

            clock(j - i - 1);
            digitalWrite(XDATAPIN, LOW);
            clock();
            digitalWrite(XDATAPIN, HIGH);

            clock(i);
        }
    }

    latch();
}

void updateDisplay(unsigned long displayTimeMS) {
    unsigned long time = millis();
    while (millis() < time + displayTimeMS) {
        for (short i = 0; i < GRIDLENGTH; ++i) {
            for (short j = 0; j < GRIDLENGTH; ++j) {
                if (MAP[i][j] != FREE) {
                    print1at(i, j);
                }
            }
        }
    }
    print0();
}

void readInput() {  // debouncing may be required
    if (((INPUTLEFT ^ INPUTRIGHT) + (INPUTUP ^ INPUTDOWN)) == 1) {
        if (INPUTRIGHT ^ INPUTLEFT) { DIRECTION = (INPUTLEFT) ? LEFT : RIGHT; } else {
            DIRECTION = (INPUTUP) ? UP : DOWN;
        }
    }
}

void resetInput() {
    INPUTLEFT = false;
    INPUTRIGHT = false;
    INPUTUP = false;
    INPUTDOWN = false;
}

void updateMap() {
    for (short i = 0; i < GRIDLENGTH; ++i) {
        for (short j = 0; j < GRIDLENGTH; ++j) {
            if (MAP[i][j] > FREE) --MAP[i][j];
        }
    }
}

void placeFood() {
    while (true) {
        unsigned int foodPosX = random(GRIDLENGTH);
        unsigned int foodPosY = random(GRIDLENGTH);

        if (MAP[foodPosX][foodPosY] == FREE) {
            MAP[foodPosX][foodPosY] = FOOD;
            return;
        }
    }
}

void reset() {
    for (short i = 0; i < GRIDLENGTH; ++i) {
        for (short j = 0; j < GRIDLENGTH; ++j) MAP[i][j] = FREE;
    }

    randomSeed(analogRead(A0));
    HEADPOSX = random(GRIDLENGTH);
    HEADPOSY = random(GRIDLENGTH);

    MAP[HEADPOSX][HEADPOSY] = 3;
    MAP[(HEADPOSX + 1) % GRIDLENGTH][HEADPOSY] = 2;
    MAP[(HEADPOSX + 2) % GRIDLENGTH][HEADPOSY] = 1;

    DIRECTION = LEFT;
    LENGTH = 3;

    placeFood();
}

void blinkDisplay(unsigned long blinkTimeMS) {
    for (int i = 0; i < 8; ++i) {
        updateDisplay(blinkTimeMS / 8);
        delay(blinkTimeMS / 8);
    }
}

void snakeStep() {
    unsigned int newHeadPosX, newHeadPosY;

    switch (DIRECTION) {
    case RIGHT:
        newHeadPosX = (HEADPOSX + 1) % GRIDLENGTH;
        newHeadPosY = HEADPOSY;
        break;
    case LEFT:
        newHeadPosX = (HEADPOSX - 1) % GRIDLENGTH;
        newHeadPosY = HEADPOSY;
        break;
    case UP:
        newHeadPosY = (HEADPOSY + 1) % GRIDLENGTH;
        newHeadPosX = HEADPOSX;
        break;
    case DOWN:
        newHeadPosY = (HEADPOSY - 1) % GRIDLENGTH;
        newHeadPosX = HEADPOSX;
        break;
    }

    switch (MAP[newHeadPosX][newHeadPosY]) {
    case FOOD:
        ++LENGTH;
        placeFood();
    case FREE:
    case TAIL:
        HEADPOSX = newHeadPosX;
        HEADPOSY = newHeadPosY;
        MAP[HEADPOSX][HEADPOSY] = LENGTH + 1;
        break;
    case WALL:
    default:  // snake!
        blinkDisplay(800);
        reset();
        break;
    }
}

void interruptOnDown() { INPUTDOWN = true; }
void interruptOnUp() { INPUTUP = true; }
void interruptOnLeft() { INPUTLEFT = true; }
void interruptOnRight() { INPUTRIGHT = true; }

void setup() {
    Serial.begin(9600);

    // set pins as output
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(XDATAPIN, OUTPUT);
    pinMode(YDATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);

    // attach software interrupts for inputs
    PCintPort::attachInterrupt(INPUTDOWNPIN, interruptOnDown, RISING);
    PCintPort::attachInterrupt(INPUTUPPIN, interruptOnUp, RISING);
    PCintPort::attachInterrupt(INPUTLEFTPIN, interruptOnLeft, RISING);
    PCintPort::attachInterrupt(INPUTRIGHTPIN, interruptOnRight, RISING);

    reset();
    updateDisplay(LOOPTIME);
}

void loop() {
    unsigned long starttime = millis();
    readInput();
    resetInput();
    snakeStep();
    updateMap();
    updateDisplay(LOOPTIME - millis() + starttime);
}
