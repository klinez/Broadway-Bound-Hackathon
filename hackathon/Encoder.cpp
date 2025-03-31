//Written by Ben Zeller
#include <Arduino.h>
#include "Encoder.h"

Encoder::Encoder(uint8_t aState, uint8_t bState, uint8_t buttonState) {
    pinMode(aState, INPUT_PULLUP);
    pinMode(bState, INPUT_PULLUP);
    pinMode(buttonState, INPUT_PULLUP);
}

int Encoder::selectTemperature(){
    if(prevAState != aState){
        if(bState != aState){
            tempSet++;
            raise = false;
        }
        else{
            tempSet--;
            raise = true;
        }
    }
    if(buttonState == HIGH){
        pickedTemp = tempSet;
    }
    prevAState = aState;
    return pickedTemp;
}
