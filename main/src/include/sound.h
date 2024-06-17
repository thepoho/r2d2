#ifndef Sound_h
#define Sound_h

#include <HardwareSerial.h>

#define SENTIENCE_WAIT 10000 //10 seconds
#define SENTIENCE_LOWER 32
#define SENTIENCE_UPPER 51

#define SHORT_CIRCUIT_DURATION 3500 //about a 3.5 second file

#define SOUND_OFF 0
#define SOUND_SENTIENCE 1
#define SOUND_THEME 2
#define SOUND_IMPERIAL_MARCH 3
#define SOUND_DISCO 4
#define SOUND_SHORT_CIRCUIT 5


class Sound {
  public:
    Sound();
    Sound(HardwareSerial* _serial);
    ~Sound();
    void run(unsigned long millis, int soundInputValue);
    bool isShortCircuiting();
    unsigned long shortCircuitEnd = 0;

  private:
    // void checkSoundInput(int pwm);
    void checkForSentienceSound();
    void checkForChangeSound(int soundInputValue);
    void changeSound(int req);
    void playSound(int num);
    void startShortCircuit();

    int playingSound    = -1;
    int lastSound       = -1;
    int requestedSound  = -1;
    
    unsigned long currentMillis = 0;

    unsigned long lastSentiencePlayed = 0;

    HardwareSerial* soundSerial;

};
#endif
