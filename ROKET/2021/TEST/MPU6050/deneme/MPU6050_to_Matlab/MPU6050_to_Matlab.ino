#include <Servo.h> 

const int x = 350; 

Servo servo1;
Servo servo2;



void setup() 
{ 
//Starting the serial monitor
Serial.begin(9600); 

//Configuring servo pins
servo2.attach(4); // pinky

} 


void loop() 
{ 
//Printing the EMG data
Serial.println(analogRead(0)); 

//If the EMG data is greater than x the hand closes
  if(analogRead(0) > x) {
    servo2.write(180);
   
  }

//If the EMG data is lower than x the hand opens
  else if (analogRead(0) < x) {
    servo2.write(38);
  
  }

//A delay to slow down the process
  delay(50);
}
