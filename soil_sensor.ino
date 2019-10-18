unsigned int data_sum = 0;
int data_count = 0;
int average_1s = 0;
int average_5s = 0;
int result = 0;
int result_checking = 0;
int avg_index = 0;
unsigned int currentMillis = 0;
unsigned int startMillis = 0;

int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  startMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor();
}

void sensor() {
  currentMillis = millis();

  if ( currentMillis - startMillis <= 1000 ) {
    if ( data_count < 10 ) {
      data_sum = analogRead(0);
      data_count++;
      Serial.print("Data sum of 10 adc: ");
      Serial.println(data_sum);
      Serial.print("Data count for 10 times: ");
      Serial.println(data_count);
    }
  } else {
    average_1s = data_sum / data_count;
    Serial.println("-------------------------------");
    Serial.print("Average every 1s: ");
    Serial.println(average_1s);
    Serial.println("-------------------------------");
    average_5s += average_1s;
    avg_index++;
    Serial.print("Index: ");
    Serial.println(avg_index);
    data_sum = 0;
    data_count = 0;
    startMillis = currentMillis;
    if (avg_index == 5) {
      result = average_5s / avg_index;
      result_checking = result;
      Serial.println("_______________________________");
      Serial.print("Result: ");
      Serial.println(result);
      Serial.println("_______________________________");
      logic_checker();
      //  switch_case();
      Serial.println("_______________________________");
      result = 0;
      avg_index = 0;
    }

  }

}

void logic_checker() {
  if ( result_checking >= 500 && result_checking <= 600) {
    Serial.println("It's too dry!");
    value = 1;
  } else if ( result_checking >= 601 && result_checking <= 650 ) {
    Serial.println("It's fine.");
    value = 2;
  } else if ( result_checking >= 651 && result_checking <= 750 ) {
    Serial.println("It's in good condition.");
    value = 3;
  } else {
    Serial.println("Something is wrong with the plant.");
  }
}


void swtich_case() {
  switch (value) {
    case 1:
      Serial.println("It's too dry!");
      break;
    case 2:
      Serial.println("It's fine");
      break;
    case 3:
      Serial.println("It's in good condition.");
      break;
    default:
      Serial.println("Something is wrong with the plant.");
  }
}
