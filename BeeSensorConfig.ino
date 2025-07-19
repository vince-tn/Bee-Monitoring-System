int sensorPin1 = 34;  //In
int sensorPin2 = 32;  //In
int sensorPin3 = 30;  //Out
int sensorPin4 = 36;  //Out
int sensorPin5 = 24;  //In
int sensorPin6 = 26;  //In
int sensorPin7 = 28;  //Out
int sensorPin8 = 22;  //Out

int val1, val2, val3, val4, val5, val6, val7, val8;

int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
int count5 = 0, count6 = 0, count7 = 0, count8 = 0;

bool lastState1 = LOW, lastState2 = LOW, lastState3 = LOW, lastState4 = LOW;
bool lastState5 = LOW, lastState6 = LOW, lastState7 = LOW, lastState8 = LOW;

void setup() {
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);
  pinMode(sensorPin6, INPUT);
  pinMode(sensorPin7, INPUT);
  pinMode(sensorPin8, INPUT);

  Serial.begin(9600);
}

void loop() {
  val1 = digitalRead(sensorPin1);
  val2 = digitalRead(sensorPin2);
  val3 = digitalRead(sensorPin3);
  val4 = digitalRead(sensorPin4);
  val5 = digitalRead(sensorPin5);
  val6 = digitalRead(sensorPin6);
  val7 = digitalRead(sensorPin7);
  val8 = digitalRead(sensorPin8);

  if (val1 == HIGH && lastState1 == LOW) {
    Serial.println("Sensor 1 - Type 1 - In");
    count1++;
  }
  lastState1 = val1;

  if (val2 == HIGH && lastState2 == LOW) {
    Serial.println("Sensor 2 - Type 1 - In");
    count2++;
  }
  lastState2 = val2;

  if (val3 == HIGH && lastState3 == LOW) {
    Serial.println("Sensor 3 - Type 1 - Out");
    count3++;
  }
  lastState3 = val3;

  if (val4 == HIGH && lastState4 == LOW) {
    Serial.println("Sensor 4 - Type 1 - Out");
    count4++;
  }
  lastState4 = val4;

  if (val5 == HIGH && lastState5 == LOW) {
    Serial.println("Sensor 5 - Type 2 - In");
    count5++;
  }
  lastState5 = val5;

  if (val6 == HIGH && lastState6 == LOW) {
    Serial.println("Sensor 6 - Type 2 - In");
    count6++;
  }
  lastState6 = val6;

  if (val7 == HIGH && lastState7 == LOW) {
    Serial.println("Sensor 7 - Type 2 - Out");
    count7++;
  }
  lastState7 = val7;

  if (val8 == HIGH && lastState8 == LOW) {
    Serial.println("Sensor 8 - Type 2 - Out");
    count8++;
  }
  lastState8 = val8;

  delay(50);
}
