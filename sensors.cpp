//************************************
//         sensors.cpp       
//************************************

 // This file contains functions used to read and average
 // the sensors.


#include "sensors.h"
#include "Arduino.h"

// Local definitions
#define encoder1PinA 2
#define encoder1PinB 3
#define encoder2PinA 4
#define encoder2PinB 5

// Read ultrasonic value
void read_ultrasonic(/* Parameters */){
  Serial.println("Ultrasonic value \n");
}

// Read infrared value
void read_infrared(){
  Left_sensor = analogRead(A9);  
  Right_sensor = analogRead(A8); 
}


// Read colour sensor value
void read_colour(/* Parameters */){
  Serial.println("colour value \n");  
}

void read_encoder() {
  
}

// Pass in data and average the lot
void sensor_average(/* Parameters */){
  Serial.println("Averaging the sensors \n");
}
