#include "include/sound.h"
#include <Arduino.h>

Sound::Sound(HardwareSerial* _serial){
  soundSerial = _serial;
}

Sound::Sound(){
}

Sound::~Sound(){
}

void Sound::run(unsigned long _millis, int soundInputValue){
  currentMillis = _millis;
  Sound::checkForChangeSound(soundInputValue);
  Sound::checkForSentienceSound();
}

void Sound::checkForChangeSound(int soundInputValue){
  if(soundInputValue != playingSound){
    changeSound(soundInputValue);
  }
}

void Sound::checkForSentienceSound(){
  if(playingSound != SOUND_SENTIENCE)
    return;
  
  if(currentMillis > (lastSentiencePlayed + SENTIENCE_WAIT)){
    int num =  rand() % (SENTIENCE_UPPER - SENTIENCE_LOWER) + SENTIENCE_LOWER;
    playSound(num);
    lastSentiencePlayed = currentMillis;
  }
}


void Sound::changeSound(int req){
  requestedSound = playingSound = req;
  
  Serial.print("PlayingSound has changed: ");
  Serial.println(playingSound);
  
  if(playingSound== SOUND_OFF){  //1 on controller
    playSound(0);
  }else if(playingSound== SOUND_THEME){ //3 on controller
    playSound(9);
  }else if(playingSound== SOUND_IMPERIAL_MARCH){ //4 on controller
    playSound(11);
  }else if(playingSound== SOUND_DISCO){ //5 on controller
    playSound(54);
  }else if(playingSound== SOUND_SHORT_CIRCUIT){ //6 on controller
    playSound(6);
  }
}

void Sound::playSound(int num){
  // Serial.print("Playing Sound: ");
  // Serial.println(uint8_t(num));
  
  soundSerial->write(char('t'));
  soundSerial->write(uint8_t(num));
}
