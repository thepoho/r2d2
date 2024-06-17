#ifndef input_h
#define input_h

#include <Arduino.h>

//Sound input is a 6 position input, values below as soundInputs array.
//Need to debounce it a little bit as it can fluctuate, especially when plugged into
//the pc via usb.

#define SOUND_INPUT_PIN 57 //A3
#define SOUND_GRACE 15 //used when reading the value from the pw m. val +/- grace
#define DEBOUNCE_COUNT_REQUIRED 3


class Input {
  public:
    Input();
    ~Input();
    void run(unsigned long millis);

    int getSoundIndex();

  private:
    void checkSoundInput();
    unsigned long currentMillis = 0;

    const int soundInputs[6] = {975,1177,1380,1576,1780,1982};

    int playingSoundIndex   = 0;
    int requestedSoundIndex = 0;
    int soundDebounceCount  = 0;
    int debouncingSound     = -1;

    bool soundChanged = false;

};
#endif
