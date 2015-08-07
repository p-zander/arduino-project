// This program extends the led matrix with four input switches l,r,u,d and displays the given input direction as an
// arrow on the matrix

#define GRIDLENGTH 4  // quadratic led matrix

// pin connections
#define CLOCKPIN 2
#define DATAPIN 3
#define LATCHPIN 4

#define INPUTLEFTPIN 8
#define INPUTRIGHTPIN 9
#define INPUTUPPIN 10
#define INPUTDOWNPIN 11

enum directions { IDLE, LEFT, RIGHT, UP, DOWN, UPLEFT, UPRIGHT, DOWNLEFT, DOWNRIGHT };

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
    clock(GRIDLENGTH - j);
    digitalWrite(DATAPIN, LOW);
    clock();
    digitalWrite(DATAPIN, HIGH);
    clock(j - 1);

    // write x axis
    digitalWrite(DATAPIN, LOW);
    clock(i - 1);
    digitalWrite(DATAPIN, HIGH);
    clock();
    digitalWrite(DATAPIN, LOW);
    clock(GRIDLENGTH - i);

    latch();
}

void idle(unsigned long displayTimeMUS) {
    static char data[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    shiftOut2D(data, displayTimeMUS);
}

void all(unsigned long displayTimeMUS) {
    static char data[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    shiftOut2D(data, displayTimeMUS);
}

void shiftOut2D(char DATA[GRIDLENGTH][GRIDLENGTH], unsigned long displayTimeMUS) {
    unsigned long time = micros();
    while (micros() < time + displayTimeMUS) {
        for (short i = 0; i < GRIDLENGTH; ++i) {
            for (short j = 0; j < GRIDLENGTH; ++j) {
                if (DATA[i][j] == 0) { print0(); } else {
                    print1at(i + 1, j + 1);
                }
                print0();
            }
        }
    }
}

int readInput() {
    int direction = IDLE;

    int inputLeft = digitalRead(INPUTLEFTPIN);
    int inputRight = digitalRead(INPUTRIGHTPIN);
    int inputUp = digitalRead(INPUTUPPIN);
    int inputDown = digitalRead(INPUTDOWNPIN);

    if (inputLeft == HIGH && inputRight == LOW) {
        if (inputUp == HIGH && inputDown == LOW)
            direction = UPLEFT;
        else if (inputDown == HIGH && inputUp == LOW)
            direction = DOWNLEFT;
        else
            direction = LEFT;
    }
    if (inputRight == HIGH && inputLeft == LOW) {
        if (inputUp == HIGH && inputDown == LOW)
            direction = UPRIGHT;
        else if (inputDown == HIGH && inputUp == LOW)
            direction = DOWNRIGHT;
        else
            direction = RIGHT;
    }
    if (direction == IDLE && inputUp == HIGH && inputDown == LOW) { direction = UP; }
    if (direction == IDLE && inputDown == HIGH && inputUp == LOW) { direction = DOWN; }

    return direction;
}

void printDirection(int direction) {
    static char rightArrow[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 1}, {0, 0, 1, 0}};
    static char leftArrow[GRIDLENGTH][GRIDLENGTH] = {{0, 1, 0, 0}, {1, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}};
    static char upArrow[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 1, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 1, 0}};
    static char downArrow[GRIDLENGTH][GRIDLENGTH] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}};
    static char uprightArrow[GRIDLENGTH][GRIDLENGTH] = {{0, 1, 1, 1}, {0, 0, 1, 1}, {0, 1, 0, 1}, {1, 0, 0, 0}};
    static char upleftArrow[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 0}, {1, 1, 0, 0}, {1, 0, 1, 0}, {0, 0, 0, 1}};
    static char downrightArrow[GRIDLENGTH][GRIDLENGTH] = {{1, 0, 0, 0}, {0, 1, 0, 1}, {0, 0, 1, 1}, {0, 1, 1, 1}};
    static char downleftArrow[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 1}, {1, 0, 1, 0}, {1, 1, 0, 0}, {1, 1, 1, 0}};

    switch (direction) {
    default:
    case IDLE:
        idle(1000);
        break;
    case LEFT:
        shiftOut2D(leftArrow, 100000);
        break;
    case RIGHT:
        shiftOut2D(rightArrow, 100000);
        break;
    case UP:
        shiftOut2D(upArrow, 100000);
        break;
    case DOWN:
        shiftOut2D(downArrow, 100000);
        break;
    case UPLEFT:
        shiftOut2D(upleftArrow, 100000);
        break;
    case UPRIGHT:
        shiftOut2D(uprightArrow, 100000);
        break;
    case DOWNLEFT:
        shiftOut2D(downleftArrow, 100000);
        break;
    case DOWNRIGHT:
        shiftOut2D(downrightArrow, 100000);
        break;
    }
}

void setup() {
    // Serial.begin(9600);

    // set pins as output
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);

    // set pin as input
    pinMode(INPUTLEFTPIN, INPUT);
    pinMode(INPUTRIGHTPIN, INPUT);
    pinMode(INPUTUPPIN, INPUT);
    pinMode(INPUTDOWNPIN, INPUT);
}

void loop() {
    printDirection(readInput());
    delay(1);
}
