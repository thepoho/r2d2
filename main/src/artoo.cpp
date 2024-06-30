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
  // if(pInput->getSoundIndex() == 0){
  //   pServoController->setDomeServoDestination(5,  map(0,   0, 180, SERVOMIN, SERVOMAX));
  //   pServoController->setDomeServoDestination(6,  map(0,   0, 180, SERVOMIN, SERVOMAX));
  // }else{
  //   // pServoController->setDomeServoDestination(5,  map(150,   0, 180, SERVOMIN, SERVOMAX));
  //   pServoController->setDomeServoDestination(6,  map(150,   0, 180, SERVOMIN, SERVOMAX));
  // }

  currentMillis = millis;
  
  pInput->run(millis);

  pSound->run(millis, pInput->getSoundIndex());
  pServoController->run(millis);

  //currently the dome panels are either short circuiting or reset.
  checkStartShortCircuit();
  runShortCircuit();

  updateEyeMovement();
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
      nextShortCircuitAction = currentMillis + SHORT_CIRCUIT_SERVO_DELAY;
    }
  }else{
    pServoController->closeDomePanels();
  }
}

bool Artoo::isShortCircuiting(){
  return (shortCircuitEnd > currentMillis);
}

void Artoo::checkStartShortCircuit(){
  //Set short circuit timer if need be
  if(isShortCircuiting())
    return;
  if(pInput->soundIndexWasChanged()){
    if(pInput->getSoundIndex() == SHORT_CIRCUIT_SOUND_INDEX){
      //Correct sound is set
      shortCircuitEnd = currentMillis + SHORT_CIRCUIT_DURATION;  //about a 3 second file.
    }
  }
}