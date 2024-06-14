#ifndef artoo_h
#define artoo_h

#include "sound.h"
#include "servo_controller.h"

class Artoo {
  public:
    Artoo();
    ~Artoo();
    void run(unsigned long millis);

  private:

    Sound* pSound;
    ServoController* pServoController;

};
#endif
