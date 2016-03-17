#include <aJSON.h>
#include <Servo.h> 

aJsonStream serial_stream(&Serial);
Servo myservo;

int pos = 0; 

void setup(void) {
 Serial.begin(9600);
 myservo.attach(9);  
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
    
    if (i == 1) {
      //stepper motor
      moveServo();
    }
    
  }
 
}

void moveServo() {
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }   
}
