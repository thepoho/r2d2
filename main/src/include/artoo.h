#ifndef artoo_h
#define artoo_h

#include "input.h"
#include "servo_controller.h"
#include "sound.h"

#define SHORT_CIRCUIT_SOUND_INDEX 5 //needs to match the sound played and position on the TX for SC
#define SHORT_CIRCUIT_DURATION    3500 //about a 3.5 second file
#define SHORT_CIRCUIT_SERVO_DELAY 250 
#define EYE_MOVEMENT_SERVO_INTERVAL 2000 

class Artoo {
  public:
    Artoo();
    ~Artoo();
    void run(unsigned long millis);

  private:
    void checkStartShortCircuit();
    void runShortCircuit();
    bool isShortCircuiting();
    void updateEyeMovement();

    Input*            pInput;
    ServoController*  pServoController;
    Sound*            pSound;

    unsigned long currentMillis;
    
    
    unsigned long shortCircuitEnd        = 0;
    unsigned long nextShortCircuitAction = 0;

    unsigned long nextEyeMovement = 0;

};
#endif
