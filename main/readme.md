## Poho's main R2D2 library

### Prerequisites:
Adafruit PWM Servo Driver Library by Adafruit Version 3.0.2
for VScode you might need to include the library path (C:\Program Files (x86)\Arduino\libraries) or similar in your include path



https://github.com/adafruit/Adafruit_BusIO
https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

x:\Projects\R2D2\Arduino\main\lights.h

We can assume Serial is the main debug serial link.
Serial3 is for sound, but is initialised in main, and passed to sound class.