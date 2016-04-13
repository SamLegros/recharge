#include <OscSerial.h>

const int analogPin = A0;
const int powerTailPin = 8;

// tile support
#include <EthernetUdp.h>
#include <SPI.h>

int baudRate = 9600;
OscSerial oscSerial;
long serialTimerEnd;
long serialTimerInterval = 100;

int phone;
int button;
 
void setup() {
  Serial.begin(baudRate);
  oscSerial.begin(Serial);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(3, INPUT);
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  
  // check for phone 
  int sensor = analogRead(analogPin); 
 // Serial.println(sensor);
  if (sensor < 650) phone = 1; 
  else phone = 0; 
  
  if (button == 1) {
    digitalWrite(powerTailPin, LOW);
  }
  else {
    digitalWrite(powerTailPin, HIGH);
  }
  
  // debug
  if (button == 1) digitalWrite(10, HIGH);
  else digitalWrite(10, LOW);
  if (phone == 1) digitalWrite(11, HIGH);
  else digitalWrite(11, LOW);  
  
  //  limits sends to every 100 mS
  if (millis()>= serialTimerEnd) {
    serialTimerEnd = millis() + serialTimerInterval;    
    tellAboutThePhone(); 
  }

  // important! this is needed in order to receive messages  
  oscSerial.listen();
}

// incoming messages will arrive here
void oscEvent(OscMessage & msg) {
  // handle data here 
  // OR
  // route messages using the "plug" functionality

  // this example redirects messages called "/incoming" to myFunction (below) 
  msg.plug("/switch", getSwitch);
}

void getSwitch(OscMessage & msg) {
  button = msg.getInt(0);  
}

void tellAboutThePhone() {
  OscMessage msg("/phone");
  msg.add(phone);
  oscSerial.send(msg); 
}



