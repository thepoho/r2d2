#include "include/sound.h"

Sound::Sound(HardwareSerial* _serial){
  soundSerial = _serial;
}

Sound::Sound(){
  int poho = 5;
  const int soundInputs[] = {
    975,
    1177,
    1380,
    1576,
    1780,
    1982
  };
}

void Sound::run(unsigned long millis){
   int soundPwm = 5; //pulseIn(SOUND_INPUT_PIN, HIGH, 30000);
  Sound::checkSoundInput(soundPwm);
  Sound::checkForSentienceSound(millis);
}

void Sound::checkSoundInput(int pwm){
 
  for(int i = 0; i < (sizeof(soundInputs)/ sizeof(soundInputs[0])); i++){
    if(pwm > soundInputs[i] - SOUND_GRACE && pwm < soundInputs[i] + SOUND_GRACE){
      requestedSound = i;
      break;
    }
  }
  
  if(playingSound == requestedSound){
    //do nothing - reset the debounce
    soundDebounceCount = 0;
  }else{
    //requesting a different sound.
    if(soundDebounceCount >= DEBOUNCE_COUNT_REQUIRED){
      soundDebounceCount = 0;
      changeSound(requestedSound);
    }else{
      
      //working out if need to debounce
      if(debouncingSound == requestedSound){
        soundDebounceCount += 1;
      }else{
        soundDebounceCount = 0;
        debouncingSound = requestedSound;
      }

      // Serial.print("Debounce Count: ");
      // Serial.print(soundDebounceCount);
      // Serial.print(", CurrentSound: ");
      // Serial.print(playingSound);
      // Serial.print(", RequestedSound: ");
      // Serial.println(requestedSound);
    }
  }
}


void Sound::checkForSentienceSound(unsigned long millis){
  if(playingSound!= SOUND_SENTIENCE)
    return;
  
  if(millis > (lastSentiencePlayed + SENTIENCE_WAIT)){
    playSound(SENTIENCE_LOWER + random(SENTIENCE_UPPER - SENTIENCE_LOWER ));
    lastSentiencePlayed = millis;
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
    startShortCircuit();
  }

  void playSound(int num){
    Serial.print("Playing Sound: ");
    Serial.println(byte(num));
    
    soundSerial.write(char('t'));
    soundSerial.write(byte(num));
  }
}
