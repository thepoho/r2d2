#ifndef input_h
#define input_h

#include <Arduino.h>

//Sound input is a 6 position input, values below as soundInputs array.
//Need to debounce it a little bit as it can fluctuate, especially when plugged into
//the pc via usb.

#define SOUND_INPUT_PIN 57 //A3
#define SELECTOR_INPUT_PIN 58 //A4

#define SOUND_GRACE 15 //used when reading the value from the pw m. val +/- grace
#define DEBOUNCE_COUNT_REQUIRED 3

#define SELECTOR_GRACE 100 //used when reading values from the selector +/- this value


class Input {
  public:
    Input();
    ~Input();
    void run(unsigned long millis);

    int getSoundIndex();
    bool soundIndexWasChanged();

    int getSelectorIndex();

  private:
    void checkSoundInput();
    void checkSelectorInput();
    unsigned long currentMillis = 0;

    const int soundInputs[6] = {975,1177,1380,1576,1780,1982};

    int playingSoundIndex   = 0;
    int requestedSoundIndex = 0;
    bool soundIndexWasChangedValue = false;
    int soundDebounceCount  = 0;
    int debouncingSound     = -1;

    bool soundChanged = false;

    const int selectorInputs[3] = {975, 1478, 1982};
    int currentSelectorIndex = 0;


};
#endif
