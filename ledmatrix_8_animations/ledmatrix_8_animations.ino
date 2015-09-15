// This program controls a 4x4 led matrix through a 74AHC595N shift register (8bit - controls both - vertical and
// horizontal - lines) and displays a few nice animations

#define GRIDLENGTH 8  // quadratic led matrix

// pin connections
#define CLOCKPIN 2
#define XDATAPIN 3
#define YDATAPIN 5
#define LATCHPIN 6

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

void idle(unsigned long displayTimeMUS) {
    static char data[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0}};
    shiftOut2D(data, displayTimeMUS);
}

void blinkInsideOut() {
    static char data[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                                {1, 0, 0, 0, 0, 0, 0, 1},
                                                {1, 0, 1, 1, 1, 1, 0, 1},
                                                {1, 0, 1, 0, 0, 1, 0, 1},
                                                {1, 0, 1, 0, 0, 1, 0, 1},
                                                {1, 0, 1, 1, 1, 1, 0, 1},
                                                {1, 0, 0, 0, 0, 0, 0, 1},
                                                {1, 1, 1, 1, 1, 1, 1, 1}};

    for (int i = 0; i < 4; ++i) {
        shiftOut2D(data, DISPLAYTIME);
        for (short i = 0; i < GRIDLENGTH; ++i) {
            for (short j = 0; j < GRIDLENGTH; ++j) data[i][j] = !data[i][j];
        }
        shiftOut2D(data, DISPLAYTIME);
    }
}

void blinkCross() {
    static char data[GRIDLENGTH][GRIDLENGTH] = {{1, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 1, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 1, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 1, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 1, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 1, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 1, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 1}};

    for (int i = 0; i < 6; ++i) {
        shiftOut2D(data, DISPLAYTIME);
        for (short i = 0; i < GRIDLENGTH; ++i) {
            data[i][i] = !data[i][i];
            data[GRIDLENGTH - i - 1][i] = !data[GRIDLENGTH - i - 1][i];
        }
    }
}

void warpToTheMiddle() {
    char data1[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                          {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 0, 0, 0, 0, 0, 0, 1},
                                          {1, 1, 1, 1, 1, 1, 1, 1}};
    char data2[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 1, 1, 1, 1, 1, 1, 0},
                                          {0, 1, 0, 0, 0, 0, 1, 0},
                                          {0, 1, 0, 0, 0, 0, 1, 0},
                                          {0, 1, 0, 0, 0, 0, 1, 0},
                                          {0, 1, 0, 0, 0, 0, 1, 0},
                                          {0, 1, 1, 1, 1, 1, 1, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0}};
    char data3[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 1, 1, 1, 1, 0, 0},
                                          {0, 0, 1, 0, 0, 1, 0, 0},
                                          {0, 0, 1, 0, 0, 1, 0, 0},
                                          {0, 0, 1, 1, 1, 1, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0}};
    char data4[GRIDLENGTH][GRIDLENGTH] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 1, 1, 0, 0, 0},
                                          {0, 0, 0, 1, 1, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0},
                                          {0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < 6; ++i) {
        shiftOut2D(data1, DISPLAYTIME);
        shiftOut2D(data2, DISPLAYTIME);
        shiftOut2D(data3, DISPLAYTIME);
        shiftOut2D(data4, DISPLAYTIME);
    }
}

void fadeLeftRight() {
    char data[GRIDLENGTH][GRIDLENGTH] = {{1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0},
                                         {1, 0, 0, 0, 0, 0, 0, 0}};

    for (int j = 0; j < GRIDLENGTH - 1; ++j) {
        shiftOut2D(data, DISPLAYTIME);
        for (int i = 0; i < GRIDLENGTH; ++i) {
            data[i][j] = !data[i][j];
            data[i][j + 1] = !data[i][j + 1];
        }
    }
    shiftOut2D(data, DISPLAYTIME);
}

void fadeTopBottom() {
    char data[GRIDLENGTH][GRIDLENGTH] = {{1, 1, 1, 1, 1, 1, 1, 1},
                                         {0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0},
                                         {0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < GRIDLENGTH - 1; ++i) {
        shiftOut2D(data, DISPLAYTIME);
        for (int j = 0; j < GRIDLENGTH; ++j) {
            data[i][j] = !data[i][j];
            data[i + 1][j] = !data[i + 1][j];
        }
    }
    shiftOut2D(data, DISPLAYTIME);
}

void shiftOut2D(char DATA[GRIDLENGTH][GRIDLENGTH], unsigned long displayTimeMUS) {
    unsigned long time = micros();
    while (micros() < time + displayTimeMUS) {
        for (short i = 0; i < GRIDLENGTH; ++i) {
            for (short j = 0; j < GRIDLENGTH; ++j) {
                if (DATA[i][j] == 1) { print1at(j, i); }
            }
        }
    }
}

void setup() {
    // set pins as output
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(XDATAPIN, OUTPUT);
    pinMode(YDATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
}

void loop() {
    // blinkInsideOut();
    // idle(DISPLAYTIME);
    fadeLeftRight();
    // idle(DISPLAYTIME);
    fadeTopBottom();
    // idle(DISPLAYTIME);
    blinkCross();
    // idle(DISPLAYTIME);
    warpToTheMiddle();
    // idle(DISPLAYTIME);
    // all(DISPLAYTIME);
    // idle(DISPLAYTIME);
    // all(DISPLAYTIME);
    // idle(DISPLAYTIME);
}
