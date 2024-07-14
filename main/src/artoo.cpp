#include "include/artoo.h"

Artoo::Artoo(){
  Serial3.begin(38400);  //the output to the sound controller board
  pSound           = new Sound(&Serial3);
  pServoController = new ServoController();
  pInput           = new Input();
}

Artoo::~Artoo(){
  delete pInput;
  delete pServoController;
  delete pSound;
}

void Artoo::run(unsigned long millis){
  //debug stuff.
  // if(pInput->getSelectorIndex() == 0){
  //   pServoController->setBodyServoDestination(0,  map(0,   0, 180, SERVOMIN, SERVOMAX));
  //   pServoController->setBodyServoDestination(1,  map(0,   0, 180, SERVOMIN, SERVOMAX));
  // }else if(pInput->getSelectorIndex() == 1){
  //   pServoController->setBodyServoDestination(0,  map(75 ,   0, 180, SERVOMIN, SERVOMAX));
  //   pServoController->setBodyServoDestination(1,  map(75 ,   0, 180, SERVOMIN, SERVOMAX));
  // }else{
  //   pServoController->setBodyServoDestination(0,  map(150 ,   0, 180, SERVOMIN, SERVOMAX));
  //   pServoController->setBodyServoDestination(1,  map(150 ,   0, 180, SERVOMIN, SERVOMAX));
  // }

  currentMillis = millis;
  
  pInput->run(millis);

  if(pInput->getSelectorIndex() == AUDIO_SELECTOR_INDEX){
    pSound->run(millis, pInput->getSoundIndex());
    checkStartShortCircuit();
  }else{
    pSound->run(millis);
  }

  if(pInput->getSelectorIndex() == ARM_SELECTOR_INDEX){
    updateArmPositions();
  }

  pServoController->run(millis);

  //currently the dome panels are either short circuiting or reset.
  runShortCircuit();

  updateEyeMovement();

  delay(100);
}

void Artoo::updateArmPositions(){
  if(pInput->getSelectorIndex() != ARM_SELECTOR_INDEX){
    return;
  }

  if(pInput->getSoundIndex() == 0){
    pServoController->setBodyServoDestination(0,  pServoController->servoZero);
    pServoController->setBodyServoDestination(1,  pServoController->servoZero);
  }else if(pInput->getSoundIndex() == 1){
    pServoController->setBodyServoDestination(0,  pServoController->servoSeventyFive);
    pServoController->setBodyServoDestination(1,  pServoController->servoZero);
  }else if(pInput->getSoundIndex() == 2){
    pServoController->setBodyServoDestination(0,  pServoController->servoZero);
    pServoController->setBodyServoDestination(1,  pServoController->servoSeventyFive);
  }else if(pInput->getSoundIndex() == 3){
    pServoController->setBodyServoDestination(0,  pServoController->servoZero);
    pServoController->setBodyServoDestination(1,  pServoController->servoOneFifty);
  }else if(pInput->getSoundIndex() == 4){  
    pServoController->setBodyServoDestination(0,  pServoController->servoOneFifty);
    pServoController->setBodyServoDestination(1,  pServoController->servoZero);
  }else if(pInput->getSoundIndex() == 5){
    pServoController->setBodyServoDestination(0,  pServoController->servoOneFifty);
    pServoController->setBodyServoDestination(1,  pServoController->servoOneFifty);
  }
}

void Artoo::updateEyeMovement(){
  if(currentMillis >= nextEyeMovement){
    pServoController->randomiseEye();
    nextEyeMovement = currentMillis + EYE_MOVEMENT_SERVO_INTERVAL;
  }
}

void Artoo::runShortCircuit(){
  if(isShortCircuiting()){
    if(currentMillis >= nextShortCircuitAction){
      pServoController->randomiseDomePanels();
      pServoController->randomiseBodyPanels();
      nextShortCircuitAction = currentMillis + SHORT_CIRCUIT_SERVO_DELAY;
    }
  }else{
    pServoController->closeDomePanels();
    pServoController->closeBodyPanels();
  }
}

bool Artoo::isShortCircuiting(){
  return (shortCircuitEnd > currentMillis);
}

void Artoo::checkStartShortCircuit(){
  //Set short circuit timer if need be
  if(isShortCircuiting())
    return;
  if(pInput->soundIndexWasChanged() && pInput->getSelectorIndex() == AUDIO_SELECTOR_INDEX){
    if(pInput->getSoundIndex() == SHORT_CIRCUIT_SOUND_INDEX){
      //Correct sound is set
      shortCircuitEnd = currentMillis + SHORT_CIRCUIT_DURATION;  //about a 3 second file.
    }
  }
}