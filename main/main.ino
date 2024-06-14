#include <Adafruit_PWMServoDriver.h>
#include "src/include/artoo.h"
// #include "src/include/sound.h"
// #include "src/include/servo_controller.h"
// #include <HardwareSerial.h>


// ===============  SERVOS =============== //

//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// #define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
// #define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
// #define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
// #define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
// #define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// ===============  SOUND  =============== //


#define SERVO_MIN 40
#define SERVO_MID 90
#define SERVO_MAX 140

#define DOME_PANEL_SERVO_COUNT 5
#define DOME_SERVO_COUNT 7

int RXLED = 17;  // The RX LED has a defined Arduino pin


Artoo* pArtoo;
Sound* pSound;

// int servoZero        = map(0,   0, 180, SERVOMIN, SERVOMAX);
// int servoSeventyFive = map(75,  0, 180, SERVOMIN, SERVOMAX);
// int servoOneFifty    = map(150, 0, 180, SERVOMIN, SERVOMAX);

// int domeServoLocation[DOME_SERVO_COUNT];
// int domeServoDestination[DOME_SERVO_COUNT];

// unsigned long currentMillis = 0;

// unsigned long shortCircuitEnd  = 0;
// unsigned long nextShortCircuitAction = 0;

// unsigned long nextDomeEyeAction = 5000;


bool servoIsDomeEye(uint16_t num){
  return(num == 5 || num == 6);
}

void setup() {

  pinMode(SOUND_INPUT_PIN, INPUT);
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output


  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");
  
  pArtoo = new Artoo();

  // pSound = new Sound(&Serial3);
  

  // SERVOS
//   pwm.begin();
//   pwm.setOscillatorFrequency(27000000);

//   pwm.setPWMFreq(SERVO_FREQ);  // This is the maximum PWM frequency
  
//   for(uint16_t servonum = 0; servonum<DOME_SERVO_COUNT; servonum++){
//     if(servoIsDomeEye(servonum)){
// //      pwm.setPWM(servonum, 0, servoSeventyFive);
//       domeServoLocation[servonum]    = 9999;
//       domeServoDestination[servonum] = servoSeventyFive;
//     }else{
// //      pwm.setPWM(servonum, 0, servoZero);
//       domeServoLocation[servonum] = 9999;
//       domeServoDestination[servonum] = servoZero;
//     }
//   }

// //  printServos();
// //  delay(100);
//   pwm.sleep();

//   Serial.print("Setting OneFifty : ");
//   Serial.println(servoOneFifty); //441

//     Serial.print("Setting Zero : ");
//   Serial.println(servoZero);  //150


}

void loop() {

  // currentMillis = ;

  pArtoo->run(millis());

  delay(100);

  // checkSoundInput();
  // checkForSentienceSound();

  // if(shortCircuiting()){
  //   runShortCircuit();
  // }else{
  //   //resetDomePanelServos();
  // }

//  runServoEye();

  // checkServoMovement();

  //need to put pwm to sleep well after the servo's stop moving, otherwise they won't complete their move.
  //could set a next pwm sleep time and not have such a big delay in the main loop if it makes sense
  
  // pwm.sleep();

  

//  digitalWrite(RXLED, LOW);     // set the RX LED ON
//  delay(100);
//  digitalWrite(RXLED, HIGH);    // set the RX LED OFF
//  delay(100);
}

// void printServos(){
//   for(uint16_t servonum = 0; servonum<DOME_SERVO_COUNT; servonum++){
//     Serial.print("S: ");
//     Serial.print(servonum);
//     Serial.print(", L: ");
//     Serial.print(domeServoLocation[servonum]);
//     Serial.print(", D: ");
//     Serial.println(domeServoDestination[servonum]);
//   }
// }




// void checkServoMovement(){
//   bool pwmAsleep= true;
  
//   for(uint16_t servonum = 0; servonum<DOME_SERVO_COUNT; servonum++){
//     if(domeServoLocation[servonum] != domeServoDestination[servonum]){
//       if(pwmAsleep){
//         pwmAsleep = false;
//         pwm.wakeup();
//       }
//         Serial.print("S: ");
//         Serial.print(servonum);
//         Serial.print(", L: ");
//         Serial.print(domeServoLocation[servonum]);
//         Serial.print(", D: ");
//         Serial.println(domeServoDestination[servonum]);
        
//       pwm.setPWM(servonum, 0, domeServoDestination[servonum]);
//       domeServoLocation[servonum] = domeServoDestination[servonum];
//     }    
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

void testServo(){
    Serial.println("Test Servo");
//    #define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
//#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)

   int min = 150;
   int max = 500; 


   
//   int twenty= map(20, 0, 180, SERVOMIN, SERVOMAX);
//   int fifty= map(50, 0, 180, SERVOMIN, SERVOMAX);
//   int seventy = map(70, 0, 180, SERVOMIN, SERVOMAX);
//   int ninety= map(90, 0, 180, SERVOMIN, SERVOMAX);
//int onetwenty = map(120, 0, 180, SERVOMIN, SERVOMAX);
//
//   int oneighty = map(180, 0, 180, SERVOMIN, SERVOMAX);
   

//   uint16_t servonum = 6;
//
//for(servonum=0; servonum<5; servonum++){
//
//     Serial.print("servo: ");
//     Serial.println(servonum);
//       pwm.wakeup();  
//       pwm.setPWM(servonum, 0, onefifty);
//       pwm.sleep();  
//       delay(1000);
////
//
//       pwm.wakeup();  
//       pwm.setPWM(servonum, 0, zero);
//       pwm.sleep();  
//       delay(1000);
//}
//     pwm.wakeup();
    
//    Serial.println("Test Servo MIN");
//    for (uint16_t pulselen = min; pulselen < max; pulselen++) {
//      pwm.setPWM(servonum, 0, zero);
////    }
////pwm.sleep();
//    delay(1000);
////    pwm.wakeup();
////    Serial.println("Test Servo MAX");
////    for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
//      pwm.setPWM(servonum, 0, twenty);
////    }
//
////pwm.sleep();
//    delay(1000);
}
