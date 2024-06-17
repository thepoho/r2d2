#ifndef artoo_h
#define artoo_h

#include "input.h"
#include "servo_controller.h"
#include "sound.h"

class Artoo {
  public:
    Artoo();
    ~Artoo();
    void run(unsigned long millis);

  private:

    Input*            pInput;
    ServoController*  pServoController;
    Sound*            pSound;

};
#endif
