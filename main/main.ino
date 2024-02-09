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

int playingSound    = -1;
int lastSound       = -1;
int requestedSound  = -1;
int debouncingSound = -1;

#define DEBOUNCE_COUNT_REQUIRED 3
int soundDebounceCount = 0;


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
  if(playingSound!= SOUND_SENTIENCE)
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
      requestedSound = i;
      break;
    }
  }
  
  if(playingSound == requestedSound){
    //do nothing - reset the debounce
    soundDebounceCount = 0;
  }else{
    //requesting a different sound.
    if(soundDebounceCount >= DEBOUNCE_COUNT_REQUIRED){
      soundDebounceCount = 0;
      changeSound(requestedSound);
    }else{
      
      //working out if need to debounce
      if(debouncingSound == requestedSound){
        soundDebounceCount += 1;
      }else{
        soundDebounceCount = 0;
        debouncingSound = requestedSound;
      }

      Serial.print("Debounce Count: ");
      Serial.print(soundDebounceCount);
      Serial.print(", CurrentSound: ");
      Serial.print(playingSound);
      Serial.print(", RequestedSound: ");
      Serial.println(requestedSound);
    }
  }
}

void changeSound(int req){
  requestedSound = playingSound = req;
  
  Serial.print("PlayingSound has changed: ");
  Serial.println(playingSound);
  
  if(playingSound== SOUND_OFF){  //1 on controller
    playSound(0);
  }else if(playingSound== SOUND_THEME){ //3 on controller
    playSound(9);
  }else if(playingSound== SOUND_IMPERIAL_MARCH){ //4 on controller
    playSound(11);
  }else if(playingSound== SOUND_DISCO){ //5 on controller
    playSound(54);
  }else if(playingSound== SOUND_SHORT_CIRCUIT){ //6 on controller
    playSound(6);
  }
}

void playSound(int num){
  Serial.print("Playing Sound: ");
  Serial.println(byte(num));
  
  Serial3.write(char('t'));
  Serial3.write(byte(num));
}
