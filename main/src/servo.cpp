#include "include/servo.h"

Servo::Servo(int _index){
    index       = _index;
    location    = 9999;
    destination = 0;
}

Servo::~Servo(){

}

bool Servo::needsMoving(){
    return(destination != location);
}

// void Servo::Run(unsigned long millis){
//   currentMillis = _millis;    
// }