#ifndef ENCODER_H
#define ENCODER_H
#include <Arduino.h>

class Encoder
{
public:
    int tempSet = 25; //set by scrolling rotary
    int pickedTemp; //confirm tempSet with button press
    int aState; //pin1 : ASSIGN PIN
    int bState; //pin2 : ASSIGN PIN
    int prevAState; //save pin1
    int buttonState; // ASSIGN PIN
    bool raise; //what direction rotary was spun in last
    Encoder(uint8_t aState, uint8_t bState, uint8_t buttonState);
    int selectTemperature();
};

#endif // ENCODER_H
