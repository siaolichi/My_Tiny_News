
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int posS = 0; 
 
 char val;

 #define echoPin 4 // Echo Pin
 #define trigPin 3 // Trigger Pin
 #define LEDPin 13 // Onboard LED

 int maximumRange = 20; // Maximum range needed
 int minimumRange = 0; // Minimum range needed
 long duration, distance; // Duration used to calculate distance

int randNumber = 0;
 
 void setup() {
     Serial.begin(9600); // Start serial communication at 9600 bps
     myservo.attach(8);
     pinMode(trigPin, OUTPUT);
     pinMode(echoPin, INPUT);
     
     //Setup: Initalization 
     //pin 10 left foreward
     pinMode(10, OUTPUT);
     //pin 9 left backward
     pinMode(9, OUTPUT);
     //pin 5 right foreward
     pinMode(5, OUTPUT);
     //pin 6 right backward
     pinMode(6, OUTPUT);
    
     //Then set the start value of the signals to zero: 
     analogWrite(9, 0);   
     analogWrite(10, 0);   
     analogWrite(5, 0);   
     analogWrite(6, 0);
     digitalWrite(7,HIGH);  
     //Startup delay:
     delay(2000);
 }
 
 void loop() {
     while (Serial.available()) { // If data is available to read,
        val = Serial.read(); // read it and store it in val
     }
     if (val == 'H') { // If H was received
       if(posS>10){
          for (posS = 110; posS >= 10; posS -= 1) { // goes from 180 degrees to 0 degrees
            myservo.write(posS);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
          }  
        }
         
         digitalWrite(trigPin, LOW); 
         delayMicroseconds(2); 
        
         digitalWrite(trigPin, HIGH);
         delayMicroseconds(10); 
         
         digitalWrite(trigPin, LOW);
         duration = pulseIn(echoPin, HIGH);
         
         //Calculate the distance (in cm) based on the speed of sound.
         distance = duration/58.2;
         randNumber = 0;
        
         if (distance <= maximumRange ){
         /* Send a negative number to computer and Turn LED ON 
         to indicate "out of range" */
//             Serial.println("-1");
//             digitalWrite(LEDPin, HIGH); 
             
             digitalWrite(6,LOW); digitalWrite(5,LOW); //stop motors
             digitalWrite(9,LOW); digitalWrite(10,LOW); //stop motors  
             delay(10);
             digitalWrite(9,LOW); digitalWrite(10,200); // left motor foreward
             digitalWrite(6,LOW); digitalWrite(5,LOW); //make a left turn
             delay(500); 
             digitalWrite(6,LOW); digitalWrite(5,LOW); //stop motors
             digitalWrite(9,LOW); digitalWrite(10,LOW); //stop motors 
         }
        
         else {
//             Serial.write(distance);
             digitalWrite(LEDPin, LOW); 
             
             //forward
             
             digitalWrite(10,LOW); digitalWrite(9,200); //##set pin 10 to ground!## set speed left motor 200 backward 
             digitalWrite(6,LOW); digitalWrite(5,200);  //##set pin 5 to ground!## set speed right motor 200 backward       
             //delay(10);
             
         }
         delay(10);
     } 
     
     if(val == 'L') {
        digitalWrite(6,LOW); digitalWrite(5,LOW); //stop motors
        digitalWrite(9,LOW); digitalWrite(10,LOW); //stop motors 
        if(posS<110){
            for (posS = 10; posS <= 110; posS += 1) { // goes from 0 degrees to 180 degrees
              // in steps of 1 degree
              myservo.write(posS);              // tell servo to go to position in variable 'pos'
              delay(15);                       // waits 15ms for the servo to reach the position
            }
         }
     }
     delay(100); // Wait 100 milliseconds for next reading
} 
