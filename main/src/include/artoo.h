#ifndef artoo_h
#define artoo_h

#include "sound.h"

class Artoo {
  public:
    Artoo();
    void Run(unsigned long millis);

  private:

    Sound* pSound;

};
#endif
