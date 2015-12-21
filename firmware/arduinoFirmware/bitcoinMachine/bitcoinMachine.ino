#include <aJSON.h>
aJsonStream serial_stream(&Serial);

void setup(void) {
 Serial.begin(9600);
 pinMode(13, OUTPUT); //dir1
 pinMode(12, OUTPUT); //step1
 pinMode(7, OUTPUT); //enable1
 pinMode(11, OUTPUT); //dir2
 pinMode(10, OUTPUT); //step2
 pinMode(6, OUTPUT); //enable1
}

void loop(void) {
  //powerdown motors
  digitalWrite(7, 1);   
  digitalWrite(6, 1); 
  
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

 {"led": "0.1"} 
 {"led": "1.0"}
*/

void processMessage(aJsonObject *msg)
{

  aJsonObject *led = aJson.getObjectItem(msg, "led");
  if (led) {
    char* ledvaluestring = led->valuestring;
    float ledvaluefloat = atof(ledvaluestring); 
    int ledvalueint = ledvaluefloat;
    digitalWrite(13, ledvalueint);
  }
 
  aJsonObject *c = aJson.getObjectItem(msg, "buy");
  if (c) 
  {
    char* d = c->valuestring;
    float b = atof(d); 
    int i = b;
    
    if (i == 1) {
      //stepper motor
      for (int n = 0; n < 10000; n++) {
        digitalWrite(7, 0);   //enable motor
        digitalWrite(12, 0);
        delayMicroseconds(100);
        digitalWrite(12, 1);
        delayMicroseconds(100);  
      }
    }
    
    if (i == 2) {
      //stepper motor
      for (int n = 0; n < 10000; n++) {
        digitalWrite(6, 0); //enable motor
        digitalWrite(10, 0);
        delayMicroseconds(100);
        digitalWrite(10, 1);
        delayMicroseconds(100);  
      }
    }   
    
    if (i == 3) {
      digitalWrite(11, 1);
      delay(5000);
      digitalWrite(11, 0);
    }    
  }
 
}
