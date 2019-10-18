/*
  This program is to calculate the average of the sensor, after a 2 second delay,
  the program will start picking up the data from the sensor, until the result is lower
  than expected minimum value. */

unsigned int currentMillis = 0;
unsigned int startMillis = 0;
unsigned int data_sum = 0;
unsigned int data_count = 0;
unsigned int average_1s = 0;
int new_data = 0;
int old_data = 0;
int final_data = 0;
unsigned int result = 0;
int index_ = 0;
int min_range = 10;

#define sensorPin 0
#define buttonPin 2
int buttonState = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startMillis = millis();
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  //Connect button pin to GND since INPUT_PULLUP
  if (buttonState == HIGH) {
    sensor();
  } else {
    currentMillis = 0;
    startMillis = 0;
    data_sum = 0;
    data_count = 0;
    average_1s = 0;
    new_data = 0;
    old_data = 0;
    final_data = 0;
    result = 0;
    index_ = 0;
  }
}

void sensor() {
  currentMillis = millis();
  //Filter the first 2 second
  if ( currentMillis >= 2000 ) {

    //Picking up data for 10 times every second
    if ( currentMillis - startMillis <= 1000 ) {

      if ( data_count < 10 ) {
        data_sum += analogRead(sensorPin);
        data_count++;
        average_1s = 0;
      }
      //Calculating the average of the data
    } else {
      average_1s = data_sum / data_count;
      new_data = average_1s;
      if (new_data - old_data < min_range) {
        index_++;
        new_data = old_data;
        if ( index_ == 3 ) {
          final_data = new_data;
          Serial.println(final_data);
          delay(15000);
        }
      }
    }

  } else {
    if ( data_count < 10 ) {
      data_sum += analogRead(sensorPin);
      data_count++;
    } else {
      old_data = data_sum / data_count;
      data_sum = 0;
      data_count = 0;
    }
  }
}

// Further improvement: taking out the max and min between 10 times
/*
  #define SAMPLECOUNT 10
  unsigned int max, min, avg, adcValue;
  adcValue=adc();
  max=adcValue;
  min=adcValue;
  avg=adcValue;

  for(int i=1;i<SAMPLECOUNT;i++){
  adcValue=adc();
  if (max<adcValue)
   max=adcValue;
  if (min>adcValue)
   min=adcValue;
  avg+=adcValue;
  }
  avg-=(max+min);
  avg/=(SAMPLECOUNT-2);
*/
