/*
  NodeMCU_Firebase.cpp - Library for reading values and sending to Firebase. Also getting commands from Firebase.
  Created by Željko Eremić, December 28, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "NodeMCU_Firebase.h"
#include "HC_SR04.h"
#include "Relay.h"
#include <ESP8266WiFi.h>                                            // esp8266 library
#include <FirebaseArduino.h>                                        // firebase library

#define FIREBASE_HOST "vtszr-9e108.firebaseio.com"                  // the project name address from firebase id
#define FIREBASE_AUTH "6caoXvFRNJW0CnCp3PYtAoEWvVq7Qg2NmqusddxG"    // the secret key generated from firebase Service accounts>Database secrets
#define WIFI_SSID     "iPhone"                                      // put your home or public wifi name 
#define WIFI_PASSWORD "antonije"                                    // put your password of wifi ssid

HC_SR04 hc_sr04;      //Object of HC-SR04 sensor
Relay relay_1;        //Object of relay

NodeMCU_Firebase::NodeMCU_Firebase(int relayPin, int trigPin, int echoPin){ 
  relay_1.SetPin(relayPin);
  hc_sr04.SetPins(trigPin, echoPin);

  m_NextNodeMCU_FirebaseState = IDLE_STATE; 
  m_State                 = IDLE_STATE;
  m_timeOfMeasure   = 0;
  m_timeCurrent     = 0;
  m_currentDistance = 0;
 
  pinMode(relayPin, OUTPUT); // Sets the relayPin as an Output
  pinMode(trigPin, OUTPUT);  // Sets the trigPin  as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin  as an Input
};

void NodeMCU_Firebase::Loop()
{
  m_State = m_NextNodeMCU_FirebaseState;
  Distance distance;
  delay(100);
  switch (m_State)
  {
    case IDLE_STATE:
      m_NextNodeMCU_FirebaseState = READCMD_STATE;            
      m_currentDistance = -1;
      break;

    case READCMD_STATE:
      relay = Firebase.getInt("/ultrasonics/relay");
      m_NextNodeMCU_FirebaseState = DOCMD_STATE;
      break;

    case DOCMD_STATE:
      SetRelay(relay);
      m_NextNodeMCU_FirebaseState = MEASURE_STATE;
      break;       

    case MEASURE_STATE:
      m_currentDistance = hc_sr04.ReadDistance();
      if(m_currentDistance > -1)
      {
        m_timeOfMeasure = millis();
        m_NextNodeMCU_FirebaseState = WRITING_STATE;                   
      }
      break;

    case WRITING_STATE:
      Firebase.setInt("/ultrasonics/dist_cm", m_currentDistance);
      m_NextNodeMCU_FirebaseState = IDLE_STATE;
      break;
  }
}

bool NodeMCU_Firebase::IsItTimeToMeasure()
{
  m_timeCurrent = millis();
  if(m_timeCurrent < (m_timeOfMeasure + TIME_TO_WAIT))
  {
    return false;
  }
  else
  {
    return true;
  }
}

void NodeMCU_Firebase::SetupFirebase()
{
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);           //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                 //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase
}

void NodeMCU_Firebase::SetRelay(int relayState)
{
    relay_1.SetState(relayState);  
}
