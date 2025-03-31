//Written by Ben Zeller
#include <Arduino.h>

Encoder::Encoder(uint8_t clk, uint8_t dt, uint8_t sw) {}

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