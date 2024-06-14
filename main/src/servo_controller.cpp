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

  // bodyPwm = Adafruit_PWMServoDriver(0x41);
}

ServoController::~ServoController(){
  for(int i=0; i < sizeof(domeServos)/sizeof(domeServos[0]); i++){
    delete domeServos[i];
  }
}

void ServoController::run(unsigned long _millis){
  currentMillis = _millis;
  moveDomeServos();
  checkSleepPwm();
}

void ServoController::checkSleepPwm(){
  if(pwmAsleep)
    return;

  if(currentMillis > putPwmToSleepTime){
    domePwm.sleep();
    //bodyPwm.sleep();
    pwmAsleep = true;
  }
}

void ServoController::wakeupPwms(){

}

void ServoController::moveDomeServos(){
  for(int i=0; i < sizeof(domeServos)/sizeof(domeServos[0]); i++){
    if(domeServos[i]->needsMoving()){
      if(pwmAsleep){
        pwmAsleep = false;
        domePwm.wakeup();
        putPwmToSleepTime = currentMillis + PWM_SLEEP_GRACE_PERIOD;
      }
      domePwm.setPWM(domeServos[i]->index, 0, domeServos[i]->destination);
      domeServos[i]->location = domeServos[i]->destination;
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

// void resetDomeServos(){
//   bool doneAnything = false;
//  for(uint16_t servonum = 0; servonum<DOME_SERVO_COUNT; servonum++){
//     int tmp = servoZero;
//     if(servoIsDomeEye(servonum)){
//       tmp = servoSeventyFive;
//     }
//     domeServoDestination[servonum] = tmp;
//   }
// }

// void resetDomePanelServos(){
//   bool doneAnything = false;
//   for(uint16_t servonum = 0; servonum<DOME_PANEL_SERVO_COUNT; servonum++){
//     domeServoDestination[servonum] = servoZero;  
//   }
// }

// void runShortCircuit(){
//   // if(shortCircuiting()){
//   if(true){ //TODO - should be shortCircuiting()
//     if(currentMillis >= nextShortCircuitAction){
//       Serial.println("Randomising Servos");
//       for(uint16_t servonum = 0; servonum<DOME_PANEL_SERVO_COUNT; servonum++){
//         if(random(2)){
//           Serial.print("Setting Zero Servo: ");
//           Serial.println(servonum);
//           domeServoDestination[servonum] = servoZero;
//         }else{
//           Serial.print("Setting OneFifty Servo: ");
//           Serial.println(servonum);
//           domeServoDestination[servonum] = servoOneFifty;
//         }
// //         Serial.print("Running Servo: ");
// //         Serial.print(servonum);
// //         Serial.print(" Destination: ");
// //         Serial.println(domeServoDestination[servonum]);
//       }
//       nextShortCircuitAction = currentMillis + 350;
//     }
//   }
// }

// void runServoEye(){
//   if(currentMillis >= nextDomeEyeAction){
//     nextDomeEyeAction = currentMillis + 2000;
//     for(uint16_t servonum = 5; servonum<7; servonum++){
//       int tmp = random(3);
//       if(tmp == 0){
//         domeServoDestination[servonum] = servoZero;  
//       }else if(tmp == 1){
//         domeServoDestination[servonum] = servoSeventyFive;  
//       }else{
//         domeServoDestination[servonum] = servoOneFifty;  
//       }
//          Serial.print("Moving Eye Servo: ");
//          Serial.print(servonum);
//          Serial.print(" Destination: ");
//          Serial.println(domeServoDestination[servonum]);
//     }

//   }
// }