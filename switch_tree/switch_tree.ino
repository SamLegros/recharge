#include <Servo.h>
#include <OscSerial.h>
#include <EthernetUdp.h>
#include <SPI.h>

Servo myservo;

int posDim = 0;
int posBright = 180;

int sensorValue = 0;
int currentServoPosition = 0;

int baudRate = 9600;
OscSerial oscSerial;
long serialTimerEnd;
long serialTimerInterval = 500;

int button;
int phone = 0;  // 1 means yes, 0 means no

void setup() {
  Serial.begin(baudRate);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(3, INPUT);

  myservo.attach(9);
  resetServo();
  oscSerial.begin(Serial);
}

void loop() {
  button = digitalRead(3);

  if (button == 1) digitalWrite(10, HIGH);   // RED - switch
  else digitalWrite(10, LOW);

  if (phone == 1) digitalWrite(11, HIGH);   // GREEN - phone
  else digitalWrite(11, LOW);


  if (phone == 1 && button == 0) {
      dimTree();
  } else {
    brightenTree();
  }

  // network stuff
  if (millis() >= serialTimerEnd) {
    tellTreeWhatToDo();
    sendSwitch();
    serialTimerEnd = millis() + serialTimerInterval;     
  }

  // important! this is needed in order to receive messages  
  oscSerial.listen();
}

void brightenTree() {
  digitalWrite(6, LOW);
  if (currentServoPosition < posBright) {
    for (int pos = posBright; pos >= posDim; pos -= 1) // goes from 0 degrees to 180 degrees
    { // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    currentServoPosition = posBright;
  }
}

void dimTree() {
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


////////////////////////////////////////
void resetServo() {
  myservo.write(posDim);
  delay(15);
  myservo.write(posDim);
  currentServoPosition = posDim;
}

///////////////////////////////////////
void oscEvent(OscMessage & msg) {
      // handle data here
      // OR
      // route messages using the "plug" functionality
      // this example redirects messages called "/incoming" to myFunction (below)
      msg.plug("/phone", phoneCount);
  //phone = 1;  // debug: see if we get anything at all
}

// plugged function
void phoneCount(OscMessage & msg) {
  // get the data out of the message
  phone = msg.getInt(0);    // give this var a unique name
}


void sendSwitch() {  // intended for the phone arduino
  OscMessage msg("/switch");
  msg.add(button);
  oscSerial.send(msg);
}

// 1 is green, 0 is brown

void tellTreeWhatToDo() {
  OscMessage msg("/setTree");
  if (button == 1 && phone == 1) msg.add(0); //brown
  else msg.add(1); // brown

  //  if (button == 1 && phone == 1) {
  //    msg.add(0); // brown
  //  } else if (button == 0 && phone == 1) {
  //    msg.add(1); // green
  //  } else {
  //    msg.add(1); // green
  //  }

  oscSerial.send(msg);
}




