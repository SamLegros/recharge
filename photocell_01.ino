const int analogInPin = A0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  int button = digitalRead(3);
  
  if (sensorValue < 250) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }
}
