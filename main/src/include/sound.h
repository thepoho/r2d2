#ifndef Sound_h
#define Sound_h

#include <HardwareSerial.h>

#define SOUND_INPUT_PIN 57 //A3

#define SOUND_OFF 0
#define SOUND_SENTIENCE 1
#define SOUND_THEME 2
#define SOUND_IMPERIAL_MARCH 3
#define SOUND_DISCO 4
#define SOUND_SHORT_CIRCUIT 5

#define SOUND_GRACE 15 //used when reading the value from the pwm. val +/- grace

#define DEBOUNCE_COUNT_REQUIRED 3

#define SENTIENCE_WAIT 10000 //10 seconds
#define SENTIENCE_LOWER 32
#define SENTIENCE_UPPER 51


class Sound {
  public:
    Sound();
    Sound(HardwareSerial* _serial);
    void run(unsigned long millis);
  private:
    void checkSoundInput(int pwm);
    void checkForSentienceSound(unsigned long millis);
    void changeSound(int req);

    int soundInputs[6];

    int playingSound    = -1;
    int lastSound       = -1;
    int requestedSound  = -1;
    int debouncingSound = -1;
    int soundDebounceCount = 0;

    unsigned long lastSentiencePlayed = 0;

    HardwareSerial* soundSerial;
};
#endif
