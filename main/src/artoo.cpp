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
  // if(soundPwm > 1000){
  //     pServoController->setDomeServoDestination(0,  map(150,   0, 180, SERVOMIN, SERVOMAX));
  // }else{
  //     pServoController->setDomeServoDestination(0,  map(0,   0, 180, SERVOMIN, SERVOMAX));
  // }
  
  pInput->run(millis);

  pSound->run(millis, pInput->getSoundIndex());
  pServoController->run(millis);

  // if(pSound->isShortCircuiting()){
  //     //TODO - servo things once servos implemented here
  //     // pSound->shortCircuitEnd
  // }
}