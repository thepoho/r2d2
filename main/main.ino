#include <Servo.h>


#define SOUND_INPUT_PIN 57 //A3

int soundInputs[] = {
  975,
  1177,
  1380,
  1576,
  1780,
  1982
};

#define SOUND_OFF 0
#define SOUND_SENTIENCE 1
#define SOUND_THEME 2
#define SOUND_IMPERIAL_MARCH 3
#define SOUND_DISCO 4
#define SOUND_SHORT_CIRCUIT 5

#define SERVO_MIN 40
#define SERVO_MID 90
#define SERVO_MAX 140

#define SOUND_GRACE 15 //used when reading the value from the pwm. val +/- grace

#define SENTIENCE_WAIT 10000 //10 seconds
#define SENTIENCE_LOWER 32
#define SENTIENCE_UPPER 51

int RXLED = 17;  // The RX LED has a defined Arduino pin

int currentSound = -1;
int lastSound = -1;

unsigned long lastSentiencePlayed = 0;

void setup() {
  pinMode(SOUND_INPUT_PIN, INPUT);
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  Serial.begin(9600); //This pipes to the serial monitor
  Serial.println("Initialize Serial Monitor");
  Serial3.begin(38400);
}


void loop() {

  checkSoundInput();
  checkForSentienceSound();
  digitalWrite(RXLED, LOW);     // set the RX LED ON
  delay(100);
  digitalWrite(RXLED, HIGH);    // set the RX LED OFF
  delay(100);
}

void checkForSentienceSound(){
  if(currentSound != SOUND_SENTIENCE)
    return;
  
  unsigned long currentTime = millis();
  if(currentTime > (lastSentiencePlayed + SENTIENCE_WAIT)){
    playSound(random(SENTIENCE_LOWER, SENTIENCE_UPPER));
    lastSentiencePlayed = currentTime;
  }
}

void checkSoundInput(){
  int pwm = pulseIn(SOUND_INPUT_PIN, HIGH, 30000);
  for(int i = 0; i < (sizeof(soundInputs)/ sizeof(soundInputs[0])); i++){
    if(pwm > soundInputs[i] - SOUND_GRACE && pwm < soundInputs[i] + SOUND_GRACE){
      currentSound = i;
      break;
    }
  }
  
  if(currentSound != lastSound){
    lastSound = currentSound;
    soundChanged();
  }
}

void soundChanged(){
  Serial.print("Sound spec has changed ");
  Serial.println(currentSound);
  if(currentSound == SOUND_OFF){  //1 on controller
    playSound(0);
  }else if(currentSound == SOUND_THEME){ //3 on controller
    playSound(9);
  }else if(currentSound == SOUND_IMPERIAL_MARCH){ //4 on controller
    playSound(11);
  }else if(currentSound == SOUND_DISCO){ //5 on controller
    playSound(54);
  }else if(currentSound == SOUND_SHORT_CIRCUIT){ //6 on controller
    playSound(6);
  }
}

void playSound(int num){
  Serial.print("Playing Sound: ");
  Serial.println(num);
  Serial3.write(char('p'));
  Serial3.write(byte(num));
}
