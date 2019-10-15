#include "FastLED.h"

int timer = 0;
int startMillis = 0;
int currentMillis = 0;
int index_ = 0;
int temp_count = 0;
int temp_sum = 0;
int data_sum = 0;
int count_sum = 0;
int result = 0;

#define NUM_LEDS 4
#define DATA_PIN 2
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startMillis = millis();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(15, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  temperature();
  logicChecker();
}

void temperature() {

  currentMillis = millis();
  if ( currentMillis - startMillis <= 1000) {

    temp_sum += analogRead(0);
    temp_count += 1;

  } else {
    count_sum = temp_sum / temp_count;
    index_ += 1;
    data_sum += count_sum;


    if ( index_ == 5 ) {
      result = data_sum / index_;
      Serial.print("The average data of 5 second: ");
      Serial.println(result);
      data_sum = 0;
      index_ = 0;

    }

    startMillis = currentMillis;
    temp_sum = 0;
    temp_count = 0;

  }
}


void logicChecker() {
  if (result >= 700 && result < 950) {
    for (int i = 0; i < NUM_LEDS / 2; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  } 
  else if ( result >= 950) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if ( result <= 600) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Blue;
      FastLED.show();
    }
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::White;
      FastLED.show();
    }
  }
}

void resetLED() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}
