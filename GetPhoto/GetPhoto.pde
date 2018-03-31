/**
 * Simple Write. 
 * 
 * Check if the mouse is over a rectangle and writes the status to the serial port. 
 * This example works with the Wiring / Arduino program that follows below.
 */

import processing.video.*;
import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port
int timer;
Capture cam;
boolean pic = true;

void setup() 
{
  size(640, 480);
  String[] cameras = Capture.list();
  printArray(Capture.list());
  printArray(Serial.list());
  String portName = Serial.list()[3];
  myPort = new Serial(this, portName, 9600);
  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    
    // The camera can be initialized directly using an 
    // element from the array returned by list():
    cam = new Capture(this, cameras[0]);
    cam.start();     
  }    
  // I know that the first port in the serial list on my mac
  // is always my  FTDI adaptor, so I open Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  
}

void draw() {
  if (cam.available() == true) {
    cam.read();
  }
  image(cam, 0, 0);
  timer = second();
  //println(timer);
  if((timer > 0) && (timer < 20)){
    if(pic == true){
      saveFrame("/Users/Hsiao/Library/Mobile Documents/com~apple~CloudDocs/section1/wynton-magazine/images/news/line-#####.jpg"); 
      println("save");
      pic = false;
    }
    myPort.write('H');
    
  }else{
    myPort.write('L');
    pic = true;
  }
  image(cam, 0, 0);
  //if (mouseOverRect() == true) {  // If mouse is over square,
  //  fill(204);                    // change color and
  //  myPort.write('H');              // send an H to indicate mouse is over square
  //} 
  //else {                        // If mouse is not over square,
  //  fill(0);                      // change color and
  //  myPort.write('L');              // send an L otherwise
  //}
  //rect(50, 50, 100, 100);         // Draw a square
}

//boolean mouseOverRect() { // Test if mouse is over square
//  return ((mouseX >= 50) && (mouseX <= 150) && (mouseY >= 50) && (mouseY <= 150));
//}


/*
  // Wiring/Arduino code:
 // Read data from the serial and turn ON or OFF a light depending on the value
 
 char val; // Data received from the serial port
 int ledPin = 4; // Set the pin to digital I/O 4
 
 void setup() {
 pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
 Serial.begin(9600); // Start serial communication at 9600 bps
 }
 
 void loop() {
 while (Serial.available()) { // If data is available to read,
 val = Serial.read(); // read it and store it in val
 }
 if (val == 'H') { // If H was received
 digitalWrite(ledPin, HIGH); // turn the LED on
 } else {
 digitalWrite(ledPin, LOW); // Otherwise turn it OFF
 }
 delay(100); // Wait 100 milliseconds for next reading
 }
 
 */