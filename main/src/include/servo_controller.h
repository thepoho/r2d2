#ifndef servo_controller_h
#define servo_controller_h

// #include <HardwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include "servo.h"

#define PWM_SLEEP_GRACE_PERIOD 500

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

class ServoController {
  public:
    ServoController();
    ~ServoController();
    void run(unsigned long _millis);
    void checkSleepPwm();
    void wakeupPwms();
    void printServos();

private:
    void moveDomeServos();
    unsigned long currentMillis = 0;
    // HardwareSerial* soundSerial;

    bool pwmAsleep = false;
    unsigned long putPwmToSleepTime = 0;

    Adafruit_PWMServoDriver domePwm;
    Servo *domeServos[7];

    Adafruit_PWMServoDriver bodyPwm;
};
#endif