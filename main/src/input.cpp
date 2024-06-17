#include "include/input.h"

Input::Input(){
}

Input::~Input(){
}

void Input::run(unsigned long millis){
  currentMillis = millis;

  checkSoundInput();
  // Serial.print("SoundPWM: ");
  // Serial.println(soundPwm);
}

bool Input::soundIndexWasChanged(){
  return(soundIndexWasChangedValue);
}
int Input::getSoundIndex(){
  return(playingSoundIndex);
}

void Input::checkSoundInput(){

  int soundPwm = pulseIn(SOUND_INPUT_PIN, HIGH, 30000);

  soundIndexWasChangedValue = false;
 
  for(int i = 0; i < (sizeof(soundInputs)/ sizeof(soundInputs[0])); i++){
    if(soundPwm > soundInputs[i] - SOUND_GRACE && soundPwm < soundInputs[i] + SOUND_GRACE){
      requestedSoundIndex = i;
      break;
    }
  }
  
  if(playingSoundIndex == requestedSoundIndex){
    //do nothing - reset the debounce
    soundDebounceCount = 0;
  }else{
    //requesting a different sound.
    if(soundDebounceCount >= DEBOUNCE_COUNT_REQUIRED){
      soundDebounceCount = 0;
      playingSoundIndex = requestedSoundIndex;
      soundIndexWasChangedValue = true;
    }else{
      
      //working out if need to debounce
      if(debouncingSound == requestedSoundIndex){
        soundDebounceCount += 1;
      }else{
        soundDebounceCount = 0;
        debouncingSound = requestedSoundIndex;
      }
    }
  }
}
