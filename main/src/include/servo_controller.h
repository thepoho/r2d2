#ifndef servo_controller_h
#define servo_controller_h

// #include <HardwareSerial.h>
#include <Adafruit_PWMServoDriver.h>
#include "servo.h"

#define PWM_SLEEP_GRACE_PERIOD 100 //was 500

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
    
    void printServos();

    void setDomeServoDestination(int servo, int destination);
    void setBodyServoDestination(int servo, int destination);
    void randomiseEye();
    void randomiseDomePanels();
    void closeDomePanels();

    void randomiseBodyPanels();
    void closeBodyPanels();

    int servoZero        = map(0,   0, 180, SERVOMIN, SERVOMAX);
    int servoSeventyFive = map(75,  0, 180, SERVOMIN, SERVOMAX);
    int servoOneFifty    = map(150, 0, 180, SERVOMIN, SERVOMAX);

private:
    void moveServos();
    void wakeupDomePwm();
    void wakeupBodyPwm();

    unsigned long currentMillis = 0;

    Adafruit_PWMServoDriver domePwm;
    Servo *domeServos[7];
    bool domePwmAsleep = false;
    unsigned long putDomePwmToSleepTime = 0;

    const int domeServoIndexes[5] = {0,1,2,3,4};
    const int eyeXServoIndex = 5;
    const int eyeYServoIndex = 6;


    Adafruit_PWMServoDriver bodyPwm;
    Servo *bodyServos[2];
    bool bodyPwmAsleep = false;
    unsigned long putBodyPwmToSleepTime = 0;

    //handy assignments
    Servo *topArmServo;
    Servo *bottomArmServo;
};
#endif
