#include <Servo.h>

Servo myservo;

int posDim = 0;
int posBright = 180;

const int analogInPin = A0;
int sensorValue = 0;
int currentServoPosition = 0;

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(3, INPUT);

  myservo.attach(9);

  resetServo();
}

void loop() {
  sensorValue = analogRead(analogInPin);

  int button = digitalRead(3);

  if (sensorValue < 250) {
    digitalWrite(6, HIGH);
  } else {
    digitalWrite(6, LOW);
  }

  if (sensorValue < 250 && button == 1) {
    digitalWrite(6, LOW);
    if (currentServoPosition < posBright) {
      for (int pos = posBright; pos >= posDim; pos -= 1) // goes from 0 degrees to 180 degrees
      { // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      currentServoPosition = posBright;
    }
  } else {
    digitalWrite(6, HIGH);
    if (currentServoPosition > posDim) {
      for (int pos = posDim; pos <= posBright; pos += 1) // goes from 0 degrees to 180 degrees
      { // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
    }
    currentServoPosition = posDim;
  }
}

void resetServo() {
  myservo.write(posDim);
  delay(15);
  myservo.write(posDim);
  currentServoPosition = posDim;
}
