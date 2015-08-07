// This program controls a 4x4 led matrix through a 74AHC595N shift register (8bit - controls both - vertical and
// horizontal - lines) and displays a few nice animations

#define GRIDLENGTH 4  // quadratic led matrix

// pin connections
#define CLOCKPIN 2
#define DATAPIN 3
#define LATCHPIN 4

unsigned long DISPLAYTIME(1e5);

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

void blinkInsideOut() {
    static char dataOutside[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
    static char dataInside[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};

    shiftOut2D(dataOutside, DISPLAYTIME);
    shiftOut2D(dataInside, 2 * DISPLAYTIME);
    shiftOut2D(dataOutside, DISPLAYTIME);
    shiftOut2D(dataInside, 2 * DISPLAYTIME);
}

void blinkCross() {
    static char data1[GRIDLENGTH][GRIDLENGTH] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    static char data2[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 1}, {0, 0, 1, 0}, {0, 1, 0, 0}, {1, 0, 0, 0}};

    shiftOut2D(data1, DISPLAYTIME);
    shiftOut2D(data2, DISPLAYTIME);
    shiftOut2D(data1, DISPLAYTIME);
    shiftOut2D(data2, DISPLAYTIME);
    shiftOut2D(data1, DISPLAYTIME);
    shiftOut2D(data2, DISPLAYTIME);
    shiftOut2D(data1, DISPLAYTIME);
    shiftOut2D(data2, DISPLAYTIME);
}

void danceToTheMiddle() {
    static char DATA11[GRIDLENGTH][GRIDLENGTH] = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char DATA12[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char DATA13[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char DATA14[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char DATA15[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char DATA16[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}};
    static char DATA17[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}};
    static char DATA18[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 1, 1}};
    static char DATA19[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 1, 1, 1}};
    static char DATA20[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {1, 1, 1, 1}};
    static char DATA21[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
    static char DATA22[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 0, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
    static char DATA23[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 1, 0, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
    static char DATA24[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 0, 0, 1}, {1, 1, 1, 1}};
    static char DATA25[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 0, 1, 1}, {1, 1, 1, 1}};
    static char DATA26[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};

    shiftOut2D(DATA11, DISPLAYTIME);
    shiftOut2D(DATA12, DISPLAYTIME);
    shiftOut2D(DATA13, DISPLAYTIME);
    shiftOut2D(DATA14, DISPLAYTIME);
    shiftOut2D(DATA15, DISPLAYTIME);
    shiftOut2D(DATA16, DISPLAYTIME);
    shiftOut2D(DATA17, DISPLAYTIME);
    shiftOut2D(DATA18, DISPLAYTIME);
    shiftOut2D(DATA19, DISPLAYTIME);
    shiftOut2D(DATA20, DISPLAYTIME);
    shiftOut2D(DATA21, DISPLAYTIME);
    shiftOut2D(DATA22, DISPLAYTIME);
    shiftOut2D(DATA23, DISPLAYTIME);
    shiftOut2D(DATA24, DISPLAYTIME);
    shiftOut2D(DATA25, DISPLAYTIME);
    shiftOut2D(DATA26, 2 * DISPLAYTIME);
    shiftOut2D(DATA25, DISPLAYTIME);
    shiftOut2D(DATA24, DISPLAYTIME);
    shiftOut2D(DATA23, DISPLAYTIME);
    shiftOut2D(DATA22, DISPLAYTIME);
    shiftOut2D(DATA21, DISPLAYTIME);
    shiftOut2D(DATA20, DISPLAYTIME);
    shiftOut2D(DATA19, DISPLAYTIME);
    shiftOut2D(DATA18, DISPLAYTIME);
    shiftOut2D(DATA17, DISPLAYTIME);
    shiftOut2D(DATA16, DISPLAYTIME);
    shiftOut2D(DATA15, DISPLAYTIME);
    shiftOut2D(DATA14, DISPLAYTIME);
    shiftOut2D(DATA13, DISPLAYTIME);
    shiftOut2D(DATA12, DISPLAYTIME);
    shiftOut2D(DATA11, DISPLAYTIME);
}

void fadeLeftRight() {
    static char data1[GRIDLENGTH][GRIDLENGTH] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
    static char data2[GRIDLENGTH][GRIDLENGTH] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};
    static char data3[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}};
    static char data4[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}};

    shiftOut2D(data1, DISPLAYTIME);
    shiftOut2D(data2, DISPLAYTIME);
    shiftOut2D(data3, DISPLAYTIME);
    shiftOut2D(data4, DISPLAYTIME);
}

void fadeTopBottom() {
    static char data1[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char data2[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    static char data3[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}};
    static char data4[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}};

    shiftOut2D(data1, DISPLAYTIME);
    shiftOut2D(data2, DISPLAYTIME);
    shiftOut2D(data3, DISPLAYTIME);
    shiftOut2D(data4, DISPLAYTIME);
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

void setup() {
    // set pins as output
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
}

void loop() {
    blinkInsideOut();
    idle(DISPLAYTIME);
    fadeLeftRight();
    idle(DISPLAYTIME);
    fadeTopBottom();
    idle(DISPLAYTIME);
    blinkCross();
    idle(DISPLAYTIME);
    danceToTheMiddle();
    idle(DISPLAYTIME);
    all(DISPLAYTIME);
    idle(DISPLAYTIME);
    all(DISPLAYTIME);
    idle(DISPLAYTIME);
}

