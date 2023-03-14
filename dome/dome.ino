#include <Servo.h>


#define INPUT_PIN 21 //A3

#define SERVO_MIN 40
#define SERVO_MID 90
#define SERVO_MAX 140

const int PIE_PINS[5] = {3,5,6,9,10};
int RXLED = 17;  // The RX LED has a defined Arduino pin

Servo pieServo[5];  // create servo object to control a servo

int currentPieValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(INPUT_PIN, INPUT);



//pieServo[1].attach(3, 600, 2300);

  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
//
//  Serial.begin(57600);
//  while(!Serial);
//  Serial.println("ProMicro Blink (pin 17)");

//
  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");
}

void updateAllPieServos(int position){
  Serial.println("here0");
  if(currentPieValue != position){
//     Serial.println("here1");
//     pieServo[1].attach(3, 600, 2300);
//     delay(100);
//     pieServo[1].write(position);
//     delay(100);
//     pieServo[1].detach();
//     Serial.println("here2");
    for(int i=0; i < sizeof(PIE_PINS); i++){
      pieServo[i].attach(PIE_PINS[i], 600, 2300);
      delay(50);

      pieServo[i].write(position);
      delay(50);

      pieServo[i].detach();
//      Serial.print(PIE_PINS[i]);
    }
    currentPieValue = position;
  }
}

void loop() {

//    Serial.println("Starting");

    int PWM = pulseIn(INPUT_PIN, HIGH, 25000);
//    Serial.print(PWM);

    if(PWM < 1000){
      updateAllPieServos(SERVO_MIN);
      Serial.println("Closed");
    }
    else if(PWM < 1550){
      updateAllPieServos(SERVO_MID);
      Serial.println("Medium");
    }
    else{
      updateAllPieServos(SERVO_MAX);
      Serial.println("Open");
    }

    
//    delay(5);
//  myservo.write(0);  // tell servo to go to a particular angle
//  delay(1000);
//  
//  myservo.write(90);              
//  delay(500); 
//  
//  myservo.write(135);              
//  delay(500);
//  
//  myservo.write(180);              
//  delay(1500);       

//    Serial.println("end of servo");
//    delay(1000);

  digitalWrite(RXLED, LOW);     // set the RX LED ON
  delay(100);
   digitalWrite(RXLED, HIGH);    // set the RX LED OFF
  delay(100);
}
