
#include <Servo.h>
Servo servo;
int angle = 10;

void servoSetup() {
  servo.attach(8);
  servo.write(angle);  
}

void servoLoop() {
   // scan from 0 to 90 degrees
  for(angle = 0; angle < 90; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 90 to 0 degrees
  while (check(distance) == true) {
      HR_SR04Loop();
  } 
  if (check(distance) == false) {
    delay(1000);       
    for(angle = 90; angle > 0; angle--)    
    {                                
      servo.write(angle);           
      delay(15);       
    } 
  }
}

/*
int angle = 10;
void setup() {
  servo.attach(8);
  servo.write(angle);
}

void loop() 
{ 
 // scan from 0 to 180 degrees
  for(angle = 10; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 

} 
*/
