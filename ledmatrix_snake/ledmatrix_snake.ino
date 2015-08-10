// This program tries to implement snake with the input through four switches and the display of the game on a 4x4 led
// matrix

#define GRIDLENGTH 4  // quadratic led matrix

// pin connections- the #define tag will replace all instances of "LATCHPIN" in your code with A1 (and so on)
#define CLOCKPIN 2
#define DATAPIN 3
#define LATCHPIN 4

#define INPUTLEFTPIN 8
#define INPUTRIGHTPIN 9
#define INPUTUPPIN 10
#define INPUTDOWNPIN 11

const unsigned long LOOPTIME = 1000;  // in order to achieve a const FPS

enum directions { LEFT, RIGHT, UP, DOWN };
enum fieldTypes { WALL = -2, FOOD = -1, FREE = 0, TAIL = 1 };  // all values > 0 are body of the snake

char MAP[GRIDLENGTH][GRIDLENGTH] = {
    {FREE, FREE, FREE, FREE}, {FREE, FREE, FREE, FREE}, {FREE, FREE, FREE, FREE}, {FREE, FREE, FREE, FREE}};

unsigned short DIRECTION(0);
unsigned int HEADPOSX(0);
unsigned int HEADPOSY(0);
unsigned int LENGTH(0);

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
    digitalWrite(DATAPIN, LOW);
    clock(2 * GRIDLENGTH);

    latch();
}

void print1at(short i, short j) {
    // write y axis
    digitalWrite(DATAPIN, HIGH);
    clock(GRIDLENGTH - j - 1);
    digitalWrite(DATAPIN, LOW);
    clock();
    digitalWrite(DATAPIN, HIGH);
    clock(j);

    // write x axis
    digitalWrite(DATAPIN, LOW);
    clock(i);
    digitalWrite(DATAPIN, HIGH);
    clock();
    digitalWrite(DATAPIN, LOW);
    clock(GRIDLENGTH - i - 1);

    latch();
}

void updateDisplay(unsigned long displayTimeMS) {
    unsigned long time = millis();
    while (millis() < time + displayTimeMS) {
        for (short i = 0; i < GRIDLENGTH; ++i) {
            for (short j = 0; j < GRIDLENGTH; ++j) {
                if (MAP[i][j] == FREE) { print0(); } else {
                    print1at(i, j);
                }
            }
        }
    }
    print0();
}

void readInput() {  // debouncing may be required
    int inputLeft = digitalRead(INPUTLEFTPIN);
    int inputRight = digitalRead(INPUTRIGHTPIN);
    int inputUp = digitalRead(INPUTUPPIN);
    int inputDown = digitalRead(INPUTDOWNPIN);

    if (inputLeft == HIGH && inputRight == LOW && DIRECTION != RIGHT) DIRECTION = LEFT;
    if (inputRight == HIGH && inputLeft == LOW && DIRECTION != LEFT) DIRECTION = RIGHT;
    if (inputUp == HIGH && inputDown == LOW && DIRECTION != DOWN) DIRECTION = UP;
    if (inputDown == HIGH && inputUp == LOW && DIRECTION != UP) DIRECTION = DOWN;
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

    randomSeed(1337);
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
        delay(1000 * blinkTimeMS / 8);
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
        blinkDisplay(80);
        reset();
        break;
    }
}

void setup() {
    Serial.begin(9600);

    // set pins as output
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);

    // set pin as input
    pinMode(INPUTLEFTPIN, INPUT);
    pinMode(INPUTRIGHTPIN, INPUT);
    pinMode(INPUTUPPIN, INPUT);
    pinMode(INPUTDOWNPIN, INPUT);

    reset();
    updateDisplay(LOOPTIME);
}

void loop() {
    unsigned long starttime = millis();
    readInput();
    snakeStep();
    updateMap();
    updateDisplay(LOOPTIME - millis() + starttime);
}
