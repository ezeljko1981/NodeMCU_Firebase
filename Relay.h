/*
  relay.h - Library for controlling relay state.
  Created by Željko Eremić, December 27, 2019.
  Released into the public domain.
*/

#ifndef Relay_h
#define Relay_h

class Relay
{
  public:
    Relay();
    void SetPin(int relayPin);
    void SetState(int relayState);
  private:
    int m_relayState;
    int m_relayPin;
};

#endif
