/*
 NodeMCU_Firebase Library for :
 - Measuring distance by Ultrasonic sensor HC-SR04 by NodeMCU, and sending value to Firebase. 
 - Receiving commands for relay from Firebase.

 The circuit:
  Node MCU                     HC-SR04
  D3              ———->      Echo
  D4              ———->      Trig
  5V              ———->      VCC
  GND             ———->      GND

  Node MCU                     Relay
  D0              ———->      IN
  3.3V            ———->      VCC
  GND             ———->      GND
  

 Library originally added 16 November 2019
 by Željko Eremić

 This example code is in the public domain.

*/

#include "NodeMCU_Firebase.h"

NodeMCU_Firebase nodeMCU_Firebase(D0, D4, D3);

void setup(void)
{
  Serial.begin(9600);
  nodeMCU_Firebase.SetupFirebase();
  while(1)
  {
    nodeMCU_Firebase.Loop();  
  } 
}
void loop(void) { }
