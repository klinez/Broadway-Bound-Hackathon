
class LocalSensor
{
public:
    int tempSet = 25; //set by scrolling rotary
    int pickedTemp; //confirm tempSet with button press
    int aState; //pin1
    int bState; //pin2
    int prevAState; //save pin1
    int buttonState; 
    bool raise; //what direction rotary was spun in last
};

#endif // LOCAL_SENSOR_H