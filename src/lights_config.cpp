#include "light_config.h"

void setup() {
  Serial.begin(9600); // Starts the serial communication
  for (int i = 0; i < sizeof(lightList); i++){
     pinMode(lightList[i].pin, INPUT_PULLUP);
  }
}

String interp_input(const char* input){
  for (int i = 0; i < sizeof(lightList); i++){
    for (int j = 0; j < sizeof(input); j++) {
       if (input[j] == lightList[i].letter){
          digitalWrite(lightList[1].pin , HIGH); // Turn the LED 
          delay(500); //Sketch is simple, using delay even if it's a bad practice :)
       }
    }
  }
  delay(1000); //Same as above comment
}

void loop() {
   interp_input("RIGHT HERE");
   interp_input("RUN");
   interp_input("HAPPY HALLOWEEN");
}
