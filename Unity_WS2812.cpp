#include <FastLED.h>

#define NUM_LEDS 216
#define PIN 2
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, PIN>(leds, NUM_LEDS);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  if ( digitalRead(3) == LOW ){
    blinking();
  }

  // put your main code here, to run repeatedly:
//  Serial.println(Serial.readString());
  if (Serial.available()) {
    int r, g, b;
    r = 0;
    g = 0;
    b = 0;
    String data_test = Serial.readStringUntil("\r");
    Serial.println(data_test);
    sscanf(string2char(data_test), "%d,%d,%d", &r, &g, &b);
    
    for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB( r, g, b);
    FastLED.show();
    }
  }
}

char* string2char(String command) {
  if (command.length() != 0) {
    char* p = const_cast<char*>(command.c_str());
    return p;
  }
}

void blinking(){
  for ( int i = 0; i < NUM_LEDS; i++){
  leds[i] = CRGB::White;
  // Now turn the LED off, then pause
  }
  delay(2000);
  FastLED.show();
  for ( int i = 0; i < NUM_LEDS; i++){
  leds[i] = CRGB::Blue;
  }
  delay(2000);
  FastLED.show();
}
