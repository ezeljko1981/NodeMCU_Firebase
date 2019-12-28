/*
  relay.cpp - Library for controlling relay state.
  Created by Željko Eremić, December 27, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Relay.h"

Relay::Relay(){}
 
void Relay::SetPin(int relayPin)
{
  m_relayPin = relayPin;
}

void Relay::SetState(int relayState)
{
  m_relayState = relayState;
  if(m_relayState == 0) 
  { 
    digitalWrite(m_relayPin, LOW);
  }
  else 
  { 
    digitalWrite(m_relayPin, HIGH);
  }
}
