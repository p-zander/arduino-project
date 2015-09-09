// This program extends the led matrix with four input switches l,r,u,d and displays the given input direction as an
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

// volatile unsigned long interruptDelayTime = 200;
// volatile unsigned long lastInterruptTime = 0;
// volatile unsigned long interruptTime = lastInterruptTime + interruptDelayTime;

// int readInput() {
//     volatile int direction = IDLE;

//     volatile int inputLeft = digitalRead(INPUTLEFTPIN);
//     volatile int inputRight = digitalRead(INPUTRIGHTPIN);
//     volatile int inputUp = digitalRead(INPUTUPPIN);
//     volatile int inputDown = digitalRead(INPUTDOWNPIN);

//     // should me more like a lookup table
//     // l   r   u   d  |  value
//     // –––––––––––––––|––––––––––––––––––
//     // 0   0   0   0  |  0   IDLE
//     // 1   0   0   0  |  1   LEFT
//     // 0   1   0   0  |  2   RIGHT
//     // 0   0   1   0  |  3   UP
//     // 0   0   0   1  |  4   DOWN
//     // 1   0   1   0  |  5   UPLEFT
//     // 0   1   1   0  |  6   UPRIGHT
//     // 1   0   0   1  |  7   DOWNLEFT
//     // 0   1   0   1  |  8   DOWNRIGHT
//     //      else      |  0   IDLE

//     if (inputLeft == HIGH && inputRight == LOW) {
//         if (inputUp == HIGH && inputDown == LOW)
//             direction = UPLEFT;
//         else if (inputDown == HIGH && inputUp == LOW)
//             direction = DOWNLEFT;
//         else
//             direction = LEFT;
//     }
//     if (inputRight == HIGH && inputLeft == LOW) {
//         if (inputUp == HIGH && inputDown == LOW)
//             direction = UPRIGHT;
//         else if (inputDown == HIGH && inputUp == LOW)
//             direction = DOWNRIGHT;
//         else
//             direction = RIGHT;
//     }
//     if (direction == IDLE && inputUp == HIGH && inputDown == LOW) { direction = UP; }
//     if (direction == IDLE && inputDown == HIGH && inputUp == LOW) { direction = DOWN; }

//     return direction;
// }

void interruptOnDown() { Serial.println("DOWN"); }

void interruptOnUp() { Serial.println("UP"); }

void interruptOnLeft() { Serial.println("LEFT"); }

void interruptOnRight() { Serial.println("RIGHT"); }

void setup() {
    Serial.begin(9600);

    // set pin as input
    pinMode(INPUTLEFTPIN, INPUT);
    pinMode(INPUTRIGHTPIN, INPUT);
    pinMode(INPUTUPPIN, INPUT);
    pinMode(INPUTDOWNPIN, INPUT);

    // attach software interrupts for inputs
    PCintPort::attachInterrupt(INPUTDOWNPIN, interruptOnDown, RISING);
    PCintPort::attachInterrupt(INPUTUPPIN, interruptOnUp, RISING);
    PCintPort::attachInterrupt(INPUTLEFTPIN, interruptOnLeft, RISING);
    PCintPort::attachInterrupt(INPUTRIGHTPIN, interruptOnRight, RISING);
}

void loop() {
    Serial.println("something");
    delay(10000);
}
