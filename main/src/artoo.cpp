#include "include/artoo.h"

Artoo::Artoo(){
    Serial3.begin(38400);
    pSound = new Sound(&Serial3);
}

Artoo::~Artoo(){
    delete pSound;
}

void Artoo::Run(unsigned long millis){
    
    pSound->run(millis);

    if(pSound->isShortCircuiting()){
        //TODO - servo things once servos implemented here
        // pSound->shortCircuitEnd
    }
}