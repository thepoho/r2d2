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

#define SOUND_GRACE 15 //used when reading the value from the pw m. val +/- grace

#define DEBOUNCE_COUNT_REQUIRED 3

#define SENTIENCE_WAIT 10000 //10 seconds
#define SENTIENCE_LOWER 32
#define SENTIENCE_UPPER 51

#define SHORT_CIRCUIT_DURATION 3500 //about a 3.5 second file


class Sound {
  public:
    Sound();
    Sound(HardwareSerial* _serial);
    void run(unsigned long millis);
    bool isShortCircuiting();
    unsigned long shortCircuitEnd = 0;

  private:
    void checkSoundInput(int pwm);
    void checkForSentienceSound();
    void changeSound(int req);
    void playSound(int num);
    void startShortCircuit();


    // int soundInputs[6];

    int playingSound    = -1;
    int lastSound       = -1;
    int requestedSound  = -1;
    int debouncingSound = -1;
    int soundDebounceCount = 0;

    unsigned long currentMillis = 0;

    unsigned long lastSentiencePlayed = 0;

    HardwareSerial* soundSerial;

    const int soundInputs[6] = {975,1177,1380,1576,1780,1982};
};
#endif
