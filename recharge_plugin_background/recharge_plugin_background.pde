import processing.serial.*;
import oscP5.*;
import netP5.*;

OscP5 oscP5;

int serialTimerEnd;
int serialTimerInterval = 250;
Serial proSerial;
String serialName = "/dev/cu.usbmodem1421"; // put the name of your serial port
int baudRate = 9600; // set your baud rate
OscSerial oscSerial;

// two color 
int i;
////////////////////////////////////////

void setup() {
  // You'll find your serial device in this list 
  println(Serial.list());
  //start serial 
  proSerial = new Serial(this, serialName, baudRate);
  oscSerial = new OscSerial(this, proSerial);
  oscSerial.plug(this, "setTree", "/setTree");
}

////////////////////////////////////////
void draw() {

  if (i == 0) {
    background(#715505); //green = 0  
  } else {
    background(#0E8B1D); // brown = 1 #0E8B1D 
  }
}
/////////////////////////////////////////
// Listen for ALL OSC messages
void oscEvent(OscMessage incoming) {
  // all the received messages come here
  println(incoming);
 
}


void setTree(int val0) {
  println("setTree: " + val0); 
  
  i = val0; 
}