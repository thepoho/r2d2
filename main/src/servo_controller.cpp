#include "include/servo_controller.h"

ServoController::ServoController(){
  domePwm = Adafruit_PWMServoDriver(0x40);
  domePwm.begin();
  domePwm.setPWMFreq(SERVO_FREQ);  // This is the maximum PWM frequency

  domeServos[0] = new Servo(0);  // Dome Panel 1
  domeServos[1] = new Servo(1);  // Dome Panel 2
  domeServos[2] = new Servo(2);  // Dome Panel 3
  domeServos[3] = new Servo(3);  // Dome Panel 4
  domeServos[4] = new Servo(4);  // Dome Panel 5
  
  domeServos[5] = new Servo(5);  // Eye Servo 1
  domeServos[6] = new Servo(6);  // Eye Servo 2

  bodyPwm = Adafruit_PWMServoDriver(0x41);
  bodyPwm.begin();
  bodyPwm.setPWMFreq(SERVO_FREQ);  // This is the maximum PWM frequency
  topArmServo    = bodyServos[0] = new Servo(0);
  bottomArmServo = bodyServos[1] = new Servo(1);
}

ServoController::~ServoController(){
  for(int i=0; i < sizeof(domeServos)/sizeof(domeServos[0]); i++){
    delete domeServos[i];
  }
  delete topArmServo;
  delete bottomArmServo;
}

void ServoController::run(unsigned long _millis){
  currentMillis = _millis;
  moveServos();
  checkSleepPwm();
}

void ServoController::randomiseEye(){
  int tmp = map((rand() % 150),   0, 180, SERVOMIN, SERVOMAX);
  setDomeServoDestination(eyeXServoIndex, tmp);

  //same for the Y servo
  tmp = map((rand() % 150),   0, 180, SERVOMIN, SERVOMAX);
  setDomeServoDestination(eyeYServoIndex, tmp);
}

void ServoController::randomiseDomePanels(){
  //Magic number 5 here.  I know servos 0-4 are dome panels.
  for(int servonum = 0; servonum<5; servonum++){
    if(rand() % 2){
      setDomeServoDestination(servonum, servoZero);
    }else{
      setDomeServoDestination(servonum, servoOneFifty);
    }
  }
}

void ServoController::closeDomePanels(){
  for(int servonum = 0; servonum<5; servonum++){
    setDomeServoDestination(servonum, servoZero);
  }
}

void ServoController::randomiseBodyPanels(){
  //Magic number 5 here.  I know servos 0-4 are dome panels.
  for(int servonum = 0; servonum<2; servonum++){
    if(rand() % 3 == 0){
      setBodyServoDestination(servonum, servoZero);
    }else if(rand() % 3 == 1){
      setBodyServoDestination(servonum, servoSeventyFive);
    }else{
      setBodyServoDestination(servonum, servoOneFifty);
    }
  }
}

void ServoController::closeBodyPanels(){
  for(int servonum = 0; servonum<2; servonum++){
    setBodyServoDestination(servonum, servoZero);
  }
}

void ServoController::checkSleepPwm(){
  if(domePwmAsleep)
    return;

  if(currentMillis > putDomePwmToSleepTime){
    domePwm.sleep();
    //bodyPwm.sleep();
    domePwmAsleep = true;
  }
}

void ServoController::setDomeServoDestination(int servo, int destination){
  domeServos[servo]->destination = destination;
}

void ServoController::setBodyServoDestination(int servo, int destination){
  bodyServos[servo]->destination = destination;
}

void ServoController::wakeupDomePwm(){
  if(domePwmAsleep){
    domePwmAsleep = false;
    domePwm.wakeup();
    putDomePwmToSleepTime = currentMillis + PWM_SLEEP_GRACE_PERIOD;
  }
}

void ServoController::wakeupBodyPwm(){
  if(bodyPwmAsleep){
    bodyPwmAsleep = false;
    bodyPwm.wakeup();
    putBodyPwmToSleepTime = currentMillis + PWM_SLEEP_GRACE_PERIOD;
  }
}

void ServoController::moveServos(){
  for(int i=0; i < sizeof(domeServos)/sizeof(domeServos[0]); i++){
    if(domeServos[i]->needsMoving()){
      wakeupDomePwm();
      domePwm.setPWM(domeServos[i]->index, 0, domeServos[i]->destination);
      domeServos[i]->location = domeServos[i]->destination;
    }
  }
  for(int i=0; i < sizeof(bodyServos)/sizeof(bodyServos[0]); i++){
    if(bodyServos[i]->needsMoving()){
      wakeupBodyPwm();
      bodyPwm.setPWM(bodyServos[i]->index, 0, bodyServos[i]->destination);
      bodyServos[i]->location = bodyServos[i]->destination;
    }
  }
}


void ServoController::printServos(){
  // for(uint16_t servonum = 0; servonum<DOME_SERVO_COUNT; servonum++){
  //   Serial.print("S: ");
  //   Serial.print(servonum);
  //   Serial.print(", L: ");
  //   Serial.print(domeServoLocation[servonum]);
  //   Serial.print(", D: ");
  //   Serial.println(domeServoDestination[servonum]);
  // }
}
