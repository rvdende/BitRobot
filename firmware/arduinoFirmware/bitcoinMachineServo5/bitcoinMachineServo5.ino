#include <aJSON.h>
#include <Servo.h> 

aJsonStream serial_stream(&Serial);
Servo myservoA;
Servo myservoB;
Servo myservoC;
Servo myservoD;
Servo myservoE;

int pos = 0; 

void setup(void) {
 Serial.begin(9600);
 //might have to change pin numbers to be sure they can do PWM
 myservoA.attach(9);  
 myservoB.attach(8);  
 myservoC.attach(7);  
 myservoD.attach(6);  
 myservoE.attach(5);   
}

void loop(void) {
  //recieve commands
  while (serial_stream.available()) 
  {
    aJsonObject *msg = aJson.parse(&serial_stream);
    processMessage(msg);  //see api.ino
    aJson.deleteItem(msg);  
  } 
 delay(10); //just here to slow down the output so it is easier to read
}


/* ================================================================== 
 Expects something like this over serial:
 {"buy": "1.0"} 
*/

void processMessage(aJsonObject *msg)
{ 
  aJsonObject *c = aJson.getObjectItem(msg, "buy");
  if (c) 
  {
    char* d = c->valuestring;
    float b = atof(d); 
    int i = b;
    
    if (i == 1) { moveServoA(); }
    if (i == 2) { moveServoB(); }    
    if (i == 3) { moveServoC(); }    
    if (i == 4) { moveServoD(); }    
    if (i == 5) { moveServoE(); }    

  }
 
}

void moveServoA() {
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservoA.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservoA.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }   
}

void moveServoB() {
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservoB.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservoB.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }   
}

void moveServoC() {
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservoC.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservoC.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }   
}

void moveServoD() {
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservoD.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservoD.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }   
}

void moveServoE() {
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservoE.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservoE.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }   
}
