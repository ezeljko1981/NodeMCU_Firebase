/*
  NodeMCU_Firebase.h - Library for reading values and sending to Firebase. Also getting commands from Firebase.
  Created by Željko Eremić, December 28, 2019.
  Released into the public domain.
*/

#ifndef NodeMCU_Firebase_h
#define NodeMCU_Firebase_h

#include "Arduino.h"

class NodeMCU_Firebase
{
  public:
    NodeMCU_Firebase(int relayPin, int trigPin, int echoPin);
    void Loop();
    void SetupFirebase();
    void SetRelay(int relayState);
  private:  
    #define IDLE_STATE                0
    #define READCMD_STATE             1
    #define DOCMD_STATE               2    
    #define MEASURE_STATE             3
    #define WRITING_STATE             4
    #define TIME_TO_WAIT              2000

    uint8_t m_NextNodeMCU_FirebaseState;
    uint8_t m_State;
    unsigned long m_timeOfMeasure;
    unsigned long m_timeCurrent; 
    int m_currentDistance; 
    int relay;
    int relayPin; 

    bool IsItTimeToMeasure();      
};

#endif
