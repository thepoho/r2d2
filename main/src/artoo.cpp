#include "include/artoo.h"

Artoo::Artoo(){
    Serial3.begin(38400);
    pSound = new Sound(&Serial3);
}

void Artoo::Run(unsigned long millis){
    pSound->run(millis);
}