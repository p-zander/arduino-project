#define GRIDLENGTH 8

// pin connections
#define CLOCKPIN 2
#define XDATAPIN 3
#define YDATAPIN 5
#define LATCHPIN 6

#define OKTAGON {{0, 0, 0, 1, 1, 0, 0, 0},\
                 {0, 0, 1, 0, 0, 1, 0, 0},\
                 {0, 1, 0, 0, 0, 0, 1, 0},\
                 {1, 0, 0, 0, 0, 0, 0, 1},\
                 {1, 0, 0, 0, 0, 0, 0, 1},\
                 {0, 1, 0, 0, 0, 0, 1, 0},\
                 {0, 0, 1, 0, 0, 1, 0, 0},\
                 {0, 0, 0, 1, 1, 0, 0, 0}}

#define TRIPOLES {{0, 0, 0, 1, 1, 0, 0, 0},\
                  {0, 0, 0, 1, 0, 0, 0, 0},\
                  {0, 0, 0, 0, 1, 0, 1, 0},\
                  {1, 1, 0, 0, 0, 0, 0, 1},\
                  {1, 0, 1, 0, 0, 0, 1, 1},\
                  {0, 0, 0, 0, 0, 0, 0, 0},\
                  {0, 0, 1, 0, 1, 0, 0, 0},\
                  {0, 0, 0, 1, 1, 0, 0, 0}}

#define BIPOLES {{ 0, 0, 0, 0, 1, 1, 0, 0 },\
                 { 0, 0, 0, 0, 1, 0, 0, 0 },\
                 { 0, 0, 0, 0, 0, 0, 0, 1 },\
                 { 0, 0, 0, 0, 0, 0, 1, 1 },\
                 { 1, 1, 0, 0, 0, 0, 0, 0 },\
                 { 1, 0, 0, 0, 0, 0, 0, 0 },\
                 { 0, 0, 0, 1, 0, 0, 0, 0 },\
                 { 0, 0, 1, 1, 0, 0, 0, 0 }}

#define CLOCKS {{ 0, 1, 0, 0, 0, 0, 0, 0 },\
                { 0, 1, 0, 1, 0, 0, 0, 0 },\
                { 1, 0, 1, 0, 0, 0, 0, 0 },\
                { 0, 0, 1, 0, 0, 0, 0, 0 },\
                { 0, 0, 0, 0, 0, 1, 0, 0 },\
                { 0, 0, 0, 0, 0, 1, 0, 1 },\
                { 0, 0, 0, 0, 1, 0, 1, 0 },\
                { 0, 0, 0, 0, 0, 0, 1, 0 }}

#define BLINKER {{ 0, 1, 0, 0, 0, 0, 0, 0 },\
                 { 0, 1, 0, 0, 0, 1, 1, 1 },\
                 { 0, 1, 0, 0, 0, 0, 0, 0 },\
                 { 0, 0, 0, 0, 0, 0, 0, 0 },\
                 { 0, 0, 0, 0, 0, 0, 0, 0 },\
                 { 0, 0, 0, 0, 0, 0, 1, 0 },\
                 { 1, 1, 1, 0, 0, 0, 1, 0 },\
                 { 0, 0, 0, 0, 0, 0, 1, 0 }}

#define TOADS {{0, 0, 0, 0, 0, 0, 0, 0},\
               {0, 1, 1, 1, 0, 0, 0, 0},\
               {1, 1, 1, 0, 0, 0, 0, 0},\
               {0, 0, 0, 0, 0, 0, 0, 0},\
               {0, 0, 0, 0, 0, 0, 0, 0},\
               {0, 0, 0, 0, 0, 1, 1, 1},\
               {0, 0, 0, 0, 1, 1, 1, 0},\
               {0, 0, 0, 0, 0, 0, 0, 0}}

#define GLIDER {{0, 1, 0, 0, 0, 0, 0, 0},\
                {0, 0, 1, 0, 0, 0, 0, 0},\
                {1, 1, 1, 0, 0, 0, 0, 0},\
                {0, 0, 0, 0, 0, 0, 0, 0},\
                {0, 0, 0, 0, 0, 0, 0, 0},\
                {0, 0, 0, 0, 0, 0, 0, 0},\
                {0, 0, 0, 0, 0, 0, 0, 0},\
                {0, 0, 0, 0, 0, 0, 0, 0}}

#define MONOGRAM {{0, 0, 0, 0, 0, 0, 0, 0},\
                  {1, 1, 0, 0, 0, 1, 1, 0},\
                  {0, 1, 0, 1, 0, 1, 0, 0},\
                  {0, 1, 1, 0, 1, 1, 0, 0},\
                  {0, 1, 0, 1, 0, 1, 0, 0},\
                  {1, 1, 0, 0, 0, 1, 1, 0},\
                  {0, 0, 0, 0, 0, 0, 0, 0},\
                  {0, 0, 0, 0, 0, 0, 0, 0}} 

#define PENTAPOLE {{1, 1, 0, 0, 0, 0, 0, 0},\
                   {1, 0, 0, 0, 0, 0, 0, 0},\
                   {0, 1, 0, 1, 0, 0, 0, 0},\
                   {0, 0, 0, 0, 0, 0, 0, 0},\
                   {0, 0, 0, 1, 0, 1, 0, 0},\
                   {0, 0, 0, 0, 0, 0, 0, 0},\
                   {0, 0, 0, 0, 0, 1, 0, 1},\
                   {0, 0, 0, 0, 0, 0, 1, 1}}

#define PHOENIX {{0, 0, 0, 1, 0, 0, 0, 0},\
                 {0, 0, 0, 1, 0, 1, 0, 0},\
                 {0, 1, 0, 0, 0, 0, 0, 0},\
                 {0, 0, 0, 0, 0, 0, 1, 1},\
                 {1, 1, 0, 0, 0, 0, 0, 0},\
                 {0, 0, 0, 0, 0, 0, 1, 0},\
                 {0, 0, 1, 0, 1, 0, 0, 0},\
                 {0, 0, 0, 0, 1, 0, 0, 0}}

#define NICE1 {{ 0, 1, 0, 0, 0, 0, 0, 0 },\
               { 0, 1, 0, 0, 0, 1, 1, 1 },\
               { 0, 1, 0, 0, 0, 0, 0, 0 },\
               { 0, 0, 0, 1, 1, 0, 0, 0 },\
               { 0, 0, 0, 1, 1, 0, 0, 0 },\
               { 0, 0, 0, 0, 0, 0, 1, 0 },\
               { 1, 1, 1, 0, 0, 0, 1, 0 },\
               { 0, 0, 0, 0, 0, 0, 1, 0 }}

#define NICE2 {{0, 0, 0, 1, 1, 0, 0, 0},\
               {0, 0, 1, 0, 0, 1, 0, 0},\
               {0, 1, 0, 0, 0, 0, 1, 0},\
               {1, 0, 0, 1, 1, 0, 0, 1},\
               {1, 0, 0, 1, 1, 0, 0, 1},\
               {0, 1, 0, 0, 0, 0, 1, 0},\
               {0, 0, 1, 0, 0, 1, 0, 0},\
               {0, 0, 0, 1, 1, 0, 0, 0}}

bool NEXT[GRIDLENGTH][GRIDLENGTH];
bool NOW[GRIDLENGTH][GRIDLENGTH];

void clear(bool mat[GRIDLENGTH][GRIDLENGTH]) {  // Sets matrix to all dead
    for (int m = 0; m < GRIDLENGTH; ++m) {
        for (int n = 0; n < GRIDLENGTH; ++n) mat[m][n] = 0;
    }
}

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

void shiftOut2D(bool data[GRIDLENGTH][GRIDLENGTH], unsigned long displayTimeMS) {
    unsigned long time = millis();
    while (millis() < time + displayTimeMS) {
        for (short i = 0; i < GRIDLENGTH; ++i) {
            for (short j = 0; j < GRIDLENGTH; ++j) {
                if (data[i][j] == 1) { print1at(j, i); }
            }
        }
    }
}

void calculate(bool mata[GRIDLENGTH][GRIDLENGTH], bool matb[GRIDLENGTH][GRIDLENGTH]) {
    unsigned int neighbors;
    for (int m = 0; m < GRIDLENGTH; ++m) {
        for (int n = 0; n < GRIDLENGTH; ++n) {
            neighbors = 0;
            // Begin counting number of neighbors:
            if (m != 0 && mata[m - 1][n] == 1) ++neighbors;
            if (n != 0 && mata[m][n - 1] == 1) ++neighbors;
            if (m + 1 != GRIDLENGTH && mata[m + 1][n] == 1) ++neighbors;
            if (n + 1 != GRIDLENGTH && mata[m][n + 1] == 1) ++neighbors;
            if (m + 1 != GRIDLENGTH && n != 0 && mata[m + 1][n - 1] == 1) ++neighbors;
            if (n + 1 != GRIDLENGTH && m != 0 && mata[m - 1][n + 1] == 1) ++neighbors;
            if (n != 0 && m != 0 && mata[m - 1][n - 1] == 1) ++neighbors;
            if (n + 1 != GRIDLENGTH && m + 1 != GRIDLENGTH && mata[m + 1][n + 1] == 1) ++neighbors;

            // Apply rules to the cell:
            if (mata[m][n] == 1 && neighbors < 2)
                matb[m][n] = 0;
            else if (mata[m][n] == 1 && neighbors > 3)
                matb[m][n] = 0;
            else if (mata[m][n] == 1 && (neighbors == 2 || neighbors == 3))
                matb[m][n] = 1;
            else if (mata[m][n] == 0 && neighbors == 3)
                matb[m][n] = 1;
        }
    }
}

void copy(bool mata[GRIDLENGTH][GRIDLENGTH], bool matb[GRIDLENGTH][GRIDLENGTH]) {  // Replaces first matrix with second
    for (int m = 0; m < GRIDLENGTH; ++m) {
        for (int n = 0; n < GRIDLENGTH; ++n) mata[m][n] = matb[m][n];
    }
}

void initRandom() {
    randomSeed(analogRead(A0));
    for (int m = 0; m < GRIDLENGTH; ++m) {
        for (int n = 0; n < GRIDLENGTH; ++n) NOW[m][n] = random(2);
    }
}

void setup() {
    // Serial.begin(9600);

    // set pins as output
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(XDATAPIN, OUTPUT);
    pinMode(YDATAPIN, OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
}

// const unsigned int numPatterns = 9;
// bool start[numPatterns][GRIDLENGTH][GRIDLENGTH] = { TRIPOLES, BIPOLES, CLOCKS, BLINKER, TOADS, PENTAPOLE, PHOENIX, MONOGRAM, OKTAGON };
// short show[numPatterns] = { 4, 4, 4, 4, 4, 4, 4, 5, 12 };

void loop() {
    // // show a few oscillators
    // for (unsigned int i = 0; i < numPatterns; ++i) {
    //     copy(NOW, start[i]);
    //     for (int j = 0; j < show[i]; ++j) {
    //         shiftOut2D(NOW, 500);
    //         clear(NEXT);
    //         calculate(NOW, NEXT);
    //         copy(NOW, NEXT);
    //     }
    // }

    // // show glider
    // {
    //     bool NOW[GRIDLENGTH][GRIDLENGTH] = GLIDER;
    //     for (int j = 0; j < 21; ++j) {
    //         shiftOut2D(NOW, 500);
    //         clear(NEXT);
    //         calculate(NOW, NEXT);
    //         copy(NOW, NEXT);
    //     }
    // }

    // now start with a random initialization
    initRandom();
    for (int j = 0; j < 20; ++j) {
        shiftOut2D(NOW, 500);
        clear(NEXT);
        calculate(NOW, NEXT);
        copy(NOW, NEXT);
    }
}
