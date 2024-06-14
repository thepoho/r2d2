#ifndef servo_h
#define servo_h

class Servo {
  public:
    Servo(int _index);
    ~Servo();
    // void Run(unsigned long millis);

    bool needsMoving();

    unsigned int index;  //The addressable index. Set on construction
    unsigned int location = 99999;
    unsigned int destination = 0;
    

  private:
    //we put pwm to sleep after moving servos so it doesn't make annoying sounds. Maybe coz i have cheap servos
};
#endif
